// #include <sys/socket.h>
// #include <sys/dir.h>
// #include <sys/types.h>
// #include <resolv.h>
#include <unistd.h>
// #include <pthread.h>
#include <stdio.h>
// #include <string.h>
#include <dirent.h>
#include <string>
#include <sstream>
#include <iostream>
#include "HttpRequest.hpp"

using namespace std;
HttpRequest::HttpRequest(int &cs) : clientsocket(cs)
{
    string header = readHeader();
    // cout << header << endl;
    if (header.find("GET / ") != string::npos) {
        method = "GET";
    }
    else if (header.find("POST") != string::npos) {
        method = "POST";
        stringstream ss(header);
        string headerLine;
        while (getline(ss, headerLine)) {
            if (headerLine.find("Content-Length") != string::npos) {
                cout << headerLine << endl;
            }
        }
    }
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