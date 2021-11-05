// #include <sys/socket.h>
// #include <sys/dir.h>
// #include <sys/types.h>
// #include <resolv.h>
#include <unistd.h>
// #include <pthread.h>
#include <stdio.h>
// #include <string.h>
#include <dirent.h>
#include "HttpRequest.hpp"

void HttpRequest::readReq(char * outStr, int size){
    int rval;
    if ((rval = read(clientsocket, outStr, size)) < 0){
        perror("reading socket");
    }
}