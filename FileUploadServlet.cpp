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

/**
 * Handles the behaviour on POSTing to server. Renders a list to the browser with the files contained in images folder.
 * @param request the request params
 * @param response response to the request
 */
void FileUploadServlet::doPost(HttpRequest request, HttpResponse response) {

    /*
     * Gets file path to the "images" folder, then write the name of each file into a string of list items
     */
    std::string path = fs::current_path().u8string() + "/images";
    string files {""};
    for (const auto & entry : fs::directory_iterator(path)) {
        string filePath {entry.path().u8string()};
        // Find the images folder, then offset the string by the length of the folder name
        string fileName {filePath.substr(filePath.find("/images/") + 8)};
        files += "<li>" + fileName + "</li>";
    }


    printf("Lets Get this Post\n");
    response.addRes("HTTP/1.1 200 OK\r\n");
    response.addRes("Content-Type: text/html\r\n\r\n");

    string topPart = "<!DOCTYPE html><html><body><ul>";
    string bottomPart = "</ul></body></html>";

    response.addRes(topPart + files + bottomPart);
    response.commitRes();
}