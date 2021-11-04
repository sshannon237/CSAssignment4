#pragma once

class HttpRequest {
private:
    int clientsocket;
public:
    HttpRequest(int& cs):clientsocket(cs){};
    void readReq(char *, int);
};
