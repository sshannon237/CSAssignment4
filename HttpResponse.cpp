#include <sys/socket.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "HttpResponse.hpp"
void HttpResponse::writeRes(char * inStr, int size){
    int rval;
    if ((rval = write(clientsocket, inStr, size)) < 0){
        perror("reading socket");
    }
}