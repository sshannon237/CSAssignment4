#pragma once
#include <string>
class HttpRequest {
private:
    int clientsocket;
    int contentLength;
    std::string header;
    std::string method;
    std::string readHeader();
    
public:
    HttpRequest(int& cs);
    std::string getMethod() {return method;};
};
