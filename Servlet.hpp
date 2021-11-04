//
// Created by chspo on 2021-11-03.
//

#pragma once
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class Servlet {
public:
    virtual void doGet(HttpRequest request, HttpResponse response) = 0;
    virtual void doPost(HttpRequest request, HttpResponse response) = 0;
};
