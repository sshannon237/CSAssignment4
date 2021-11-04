#pragma once

class HttpResponse {

private:
    int clientsocket;
public:
    HttpResponse(int& cs):clientsocket(cs){};
    void writeRes(char *, int);
};

