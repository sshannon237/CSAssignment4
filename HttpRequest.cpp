#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "HttpRequest.hpp"

using namespace std;
HttpRequest::HttpRequest(int &cs) : clientsocket(cs){
    string header = readHeader();
    method = findMethod(header);
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

vector<string> HttpRequest::getData(string header) {
    vector<string> multipledata;
    stringstream ss(header);
    string data;
    while (getline(ss, data)) {
        multipledata.push_back(data);
    }
    return multipledata;
}

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

string HttpRequest::findBoundary(string header) {
    string boundaryLine;
    if((boundaryLine = findLine("Content-Type", header)) != "") {
        string boundary = boundaryLine.substr(boundaryLine.find("boundary=") + 9);
        boundary.pop_back();
        return boundary;
    }
    return "";
}

string HttpRequest::findMethod(string header) {
    if (header.find("GET / ") != string::npos) {
        return "GET";
    } else if (header.find("POST") != string::npos) {
        return "POST";
    }else if (header.find("CUSTOM") != string::npos) {
        return "CUSTOM";
    }
    return "";
    // 
}
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
