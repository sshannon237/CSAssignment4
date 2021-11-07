#pragma once
#include <vector>
#include <string>
using namespace std;
class HttpRequest {
private:
    int clientsocket;
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
public:
    HttpRequest(int& cs);
    string getMethod() {return method;};
    string getBoundary() {return boundary;};
    vector<char> getBody() {return body;};
};
