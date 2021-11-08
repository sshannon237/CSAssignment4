#pragma once

#include <string>
#include "json.hpp"
using namespace std;
class HttpResponse {

private:
    string responseStr;
    int clientsocket;
public:
    HttpResponse(int& cs):clientsocket(cs){};
    void addRes(string s){responseStr += s;};
    void commitRes();
};

