#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Socketclient
{
private:
    string filename;
    string dateCreated;
    string keyword;
public:
    Socketclient(string, string, string);
    int uploadFile();
};
