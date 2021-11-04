//
// Created by chspo on 2021-11-03.
//

#pragma once

class Servlet {
public:
    virtual void doGet(HttpRequest request, HttpResponse response);
    virtual void doPost(HttpRequest request, HttpResponse response);
};
