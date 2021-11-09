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

/**
 * Writes response data to the socket.
 */
void HttpResponse::commitRes() {
    int rval;
    int l = responseStr.length();
    char inStr[l + 1];

    strcpy(inStr, responseStr.c_str());
    if (rval = write(clientsocket, inStr, sizeof(inStr)) < 0){
        perror("writing socket\n");
    }
}
