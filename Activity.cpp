#include <string>
#include <iostream>

#include "Activity.hpp"
#include "socketclient.hpp"
using namespace std;


Activity::Activity(string fileName, string key, string date) {
    filename = fileName;
    keyword = key;
    dateCreated = date;
}

void Activity::onCreate() {
    Socketclient *socketclient = new Socketclient(filename, keyword, dateCreated);
    socketclient->uploadFile();
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

    return 0;
}