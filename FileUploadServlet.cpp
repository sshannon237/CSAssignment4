#include <string>

#include "FileUploadServlet.hpp"

void FileUploadServlet::doGet(HttpRequest request, HttpResponse response)
{

    response.addRes("HTTP/1.1 200 OK\r\n");
    response.addRes("Content-Type: text/html\r\n\r\n");
    string htmlPage = "<!DOCTYPE html><html><head><title>File Upload Form</title></head><body><h1>Upload file</h1><form method=\"POST\" action=\"upload\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"fileName\"/><br/><br/>Caption: <input type=\"text\" name=\"caption\"<br/><br/><br />Date: <input type=\"date\" name=\"date\"<br/><br/><br /><input type=\"submit\" value=\"Submit\"/></form></body></html>";
    response.addRes(htmlPage);

    response.commitRes();
}

void FileUploadServlet::doPost(HttpRequest request, HttpResponse response)
{

    printf("Lets Get this Post\n");
    response.addRes("HTTP/1.1 200 OK\r\n");
    response.addRes("Content-Type: text/html\r\n\r\n");
    string topPart = "<!DOCTYPE html><html><body><ul>";
    string bottomPart = "</ul></body></html>";
    response.addRes(topPart + "Posted" + bottomPart);

    response.commitRes();
}