#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
    string section = "";
    string sectionHeader = "";
    vector<char> imagePayload;
    string filename;
    string caption;
    string date;
    vector<char> body = request.getBody();
    for(char byte : body) {
        section += byte;
        if (sectionHeader.find("\r\n\r\n") != string::npos) {
            if(section.find("\"fileName\"") != string::npos) {
                imagePayload.push_back(byte);
                if(filename.length() < 1) {
                    filename = findFilename(sectionHeader);
                    cout << filename << endl;
                }
            }
            if(section.find("\"caption\"") != string::npos) {
                caption.push_back(byte);
            }
            if(section.find("\"date\"") != string::npos) {
                date.push_back(byte);
            }
        } else {
            sectionHeader += byte;
        }
        if (section.find(request.getBoundary()) != string::npos ) {
            section.clear();
            sectionHeader.clear();
        }
    }
    processTextPayload(caption);
    processTextPayload(date);
    processImagePayload(date + caption + filename, imagePayload);

    

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
    response.addRes("HTTP/1.1 200 OK\r\n");
    response.addRes("Content-Type: text/html\r\n\r\n");

    string topPart = "<!DOCTYPE html><html><body><ul>";
    string bottomPart = "</ul></body></html>";

    response.addRes(topPart + files + bottomPart);
    response.commitRes();
}

void FileUploadServlet::processTextPayload(string & payload) {
    stringstream ss(payload);
    getline(ss, payload);
    payload.pop_back();
}

void FileUploadServlet::processImagePayload(string filename, vector<char> image) {
    ofstream of("images/" + filename);
    for(char & byte : image) {
        of << byte;
    }
}

string FileUploadServlet::findFilename(string sectionHeader) {
    stringstream ss(sectionHeader);
    string scan;
    char s;
    while(scan.find("filename=\"") == string::npos) {
        ss >> s;
        scan += s;
    }
    scan.clear();
    while(scan.find("\"") == string::npos) {
        ss >> s;
        scan += s;
    }
    scan.pop_back();
    return scan;
}