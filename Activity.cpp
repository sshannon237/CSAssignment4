#include <string>
#include <iostream>
#include "json.hpp"

#include "Activity.hpp"
#include "socketclient.hpp"
using namespace std;

using json = nlohmann::json;
namespace fs = std::filesystem;

Activity::Activity(string fileName, string key, string date) {
    filename = fileName;
    keyword = key;
    dateCreated = date;
}

void Activity::onCreate() {
    Socketclient *socketclient = new Socketclient(filename, keyword, dateCreated);
    socketclient->uploadFile();
}

// displays the directory, incorrect way to do it
// we want this to handle the JSON response from the server and then output.
// ideally this should be in the doCustom method in the FileUploadServlet and
// we parse and print it here.
void Activity::showDirectory() {
    json images{};
    std::string path = fs::current_path().u8string() + "/images";
    for (const auto &entry : fs::directory_iterator(path)) {
        string filePath {entry.path().u8string()};
        string fileName {filePath.substr(filePath.find("/images/") + 8)};
        images.push_back(fileName);
    }
    cout << images << endl;
}

int main() {
    printf("Please enter the file name you want to save:\n");
    string filename;
    getline(cin, filename);

    printf("Please enter the date created: yyyy-mm-dd\n");
    string date;
    getline(cin, date);

    printf("Please enter a keyword:\n");
    string key;
    getline(cin, key);

    Activity *activity = new Activity(filename, date, key);
    activity->onCreate();
    activity->showDirectory();

    return 0;
}