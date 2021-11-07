#pragma once

#include <vector>
#include <string>
#include "Servlet.hpp"

using namespace std;
class FileUploadServlet : public Servlet {
private:
    void processTextPayload(string&);
    void processImagePayload(string, vector<char>);
    string findFilename(string);
public:
    void doGet(HttpRequest request, HttpResponse response) override;
    void doPost(HttpRequest request, HttpResponse response) override;
    void doCustom(HttpRequest request, HttpResponse response);
};
