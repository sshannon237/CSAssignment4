#include <string>
#include <iostream>
#include <filesystem>

#include "FileUploadServlet.hpp"

namespace fs = std::filesystem;

void FileUploadServlet::doGet(HttpRequest request, HttpResponse response) {

    response.addRes("HTTP/1.1 200 OK\r\n");
    response.addRes("Content-Type: text/html\r\n\r\n");
    string htmlPage = "<!DOCTYPE html><html><head><title>File Upload Form</title></head><body><h1>Upload file</h1><form method=\"POST\" action=\"upload\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"fileName\"/><br/><br/>Caption: <input type=\"text\" name=\"caption\"<br/><br/><br />Date: <input type=\"date\" name=\"date\"<br/><br/><br /><input type=\"submit\" value=\"Submit\"/></form></body></html>";
    response.addRes(htmlPage);

    response.commitRes();
}

void FileUploadServlet::doPost(HttpRequest request, HttpResponse response) {

    std::string path = "C:\\cygwin64\\home\\CSAssignment4";
    string files {""};
    for (const auto & entry : fs::directory_iterator(path))
        s += "<li>" + entry.path().u8string() + "</li>";
//        cout << entry.path() << endl;

    printf("Lets Get this Post\n");
    response.addRes("HTTP/1.1 200 OK\r\n");
    response.addRes("Content-Type: text/html\r\n\r\n");

    string topPart = "<!DOCTYPE html><html><body><ul>";
    string bottomPart = "</ul></body></html>";

//    response.addRes(topPart + "<li>Posted</li>" + bottomPart);
    response.addRes(topPart + s + bottomPart);
    response.commitRes();
}