#pragma once

#include <string>
using namespace std;

class Activity
{
private:
    string filename;
    string keyword;
    string dateCreated;
public:
    Activity(string, string, string);
    void onCreate();
    void showDirectory();
};
