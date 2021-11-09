#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "HttpRequest.hpp"

using namespace std;

/**
 * Constructs HttpRequest
 * @param cs reference to client socket
 */
HttpRequest::HttpRequest(int &cs) : clientsocket(cs){
    string header = readHeader();
    method = findMethod(header);
    // Determines request method and handles appropriately (differentiates client and GUI)
    if(method == "POST") {
        bodyLength = findContentLength(header);
        boundary = findBoundary(header);
        readBody();
    }
    if(method == "CUSTOM") {
        vector<string> multipledata = getData(header);
        filename = multipledata.at(2);
        dateCreated = multipledata.at(3);
        keyword = multipledata.at(4);
    }
}

/**
 * Parses the header from the request.
 * @param header string
 * @return vector of header elements
 */
vector<string> HttpRequest::getData(string header) {
    vector<string> multipledata;
    stringstream ss(header);
    string data;
    while (getline(ss, data)) {
        multipledata.push_back(data);
    }
    return multipledata;
}

/**
 * Reads a single line of the request header. Helper functino to findContentLength.
 * @param target value to read until
 * @param header header file
 * @return empty string when target has been read out of streams
 */
string HttpRequest::findLine(string target, string header) {
    stringstream ss(header);
    string headerLine;
    while (getline(ss, headerLine)) {
        if (headerLine.find(target) != string::npos) {
            return headerLine;
        }
    }
    return "";
}

/**
 * Finds content length of a header.
 * @param header the header file
 * @return the content length as int
 */
int HttpRequest::findContentLength(string header) {
    int cl = 0;
    string contentLengthLine = findLine("Content-Length", header);
    stringstream clss(contentLengthLine);
    string temp;
    while(!clss.eof()) {
        clss >> temp;
        if(stringstream(temp) >> cl) {
            break;
        }

    }
    return cl;
}

/**
 * finds the content boundary between the content and the request.
 * @param header request header
 * @return boundary between content and header
 */
string HttpRequest::findBoundary(string header) {
    string boundaryLine;
    if((boundaryLine = findLine("Content-Type", header)) != "") {
        string boundary = boundaryLine.substr(boundaryLine.find("boundary=") + 9);
        boundary.pop_back();
        return boundary;
    }
    return "";
}

/**
 * Finds the method from the header.
 * @param header string
 * @return http method type
 */
string HttpRequest::findMethod(string header) {
    if (header.find("GET / ") != string::npos) {
        return "GET";
    } else if (header.find("POST") != string::npos) {
        return "POST";
    }else if (header.find("CUSTOM") != string::npos) {
        return "CUSTOM";
    }
    return "";
}

/**
 * Reads the header char by char.
 * @return parsed header
 */
string HttpRequest::readHeader() {
    int rval;
    int bytesRead = 0;
    char byte[1];
    string header;
    while (header.find("\r\n\r\n") == string::npos) {
        if ((rval = read(clientsocket, byte, 1)) < 0) {
            perror("reading socket");
        }
        header += byte[0];
    }
    return header;
}

/**
 * Reads the body char by char
 */
void HttpRequest::readBody() {
    int rval;
    cout << "reading body" << endl;
    char bodyArr[bodyLength];
    int bytesread = 0;
    while (bytesread < bodyLength) {
        cout << bytesread << endl;
        rval = read(clientsocket, bodyArr + bytesread, bodyLength - bytesread);
        bytesread += rval;
    }
    for(char byte : bodyArr) {
        body.push_back(byte);
    }
}
