//
// Created by chspo on 2021-11-03.
//

#pragma once

class FileUploadServlet : public Servlet {
public:
    void doGet(HttpRequest request, HttpResponse response) override;
    void doPost(HttpRequest request, HttpResponse response) override;
};
