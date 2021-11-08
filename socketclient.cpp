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

#include "socketclient.hpp"
using namespace std;

Socketclient::Socketclient(string name, string date, string key) {
    filename = name;
    dateCreated = date;
    keyword = key;
}

int Socketclient::uploadFile() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int rval;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Getting Picture Size\n");
    FILE *picture;
    picture = fopen(filename.c_str(), "rb");
    int size;
    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);

    string requestHeaderTop = "CUSTOM\r\nContent-Length: ";
    string requestHeaderBottom = "\r\n\r\n";
    string requestHeader = requestHeaderTop + to_string(size);
    requestHeader += requestHeaderBottom;
    int headerNumOfBytes = 28 + to_string(size).length();

    //Send Header
    write(sock, requestHeader.c_str(), headerNumOfBytes);
    printf("Picture Size Sent\n");

    //Send Picture as Byte Array
    // printf("Sending Picture as Byte Array\n");
    // char send_buffer[size];
    // while(!feof(picture)) {
    //     fread(send_buffer, 1, sizeof(send_buffer), picture);
    //     write(sock, send_buffer, sizeof(send_buffer));
    //     bzero(send_buffer, sizeof(send_buffer));
    // }
    return 0;
}

