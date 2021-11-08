#pragma once
#include <vector>
#include <string>
using namespace std;
class HttpRequest {
public:
    int clientsocket;
    string filename;
    string dateCreated;
    string keyword;
private:
    int bodyLength;
    vector<char> body;
    string boundary;
    string method;
    string readHeader();
    void readBody();
    string findLine(string, string);
    string findMethod(string);
    int findContentLength(string);
    string findBoundary(string);
    vector<string> getData(string);
public:
    HttpRequest(int& cs);
    string getMethod() {return method;};
    string getBoundary() {return boundary;};
    vector<char> getBody() {return body;};
};
