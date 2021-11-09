#include <sys/socket.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <string>
#include <iostream>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "FileUploadServlet.hpp"
#include "InvalidRequestException.hpp"
using namespace std;
static void *run(void *);

/**
 * Main server method.
 * @return exit code int
 */
int main() {
    // set up socket to listen, then create a thread
    int sock;
    struct sockaddr_in server;
    int valread;
    int msgsock;
    pthread_t tid;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("opening stream socket");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sock, (struct sockaddr *)&server, sizeof server) < 0) {
        perror("binding stream socket");
    }
    listen(sock, 5);

    while (1) {
        msgsock = accept(sock, (struct sockaddr *)0, (socklen_t *)0);
        if (msgsock == -1) {
            perror("accept");
        }
        // Create thread
        pthread_create(&tid, NULL, run, (void *)msgsock);
        
    }
    
    return 0;
}

/**
 * Called when thread is created. Handles the thread behaviour.
 */
static void *run(void *arg) {

    int rval;
    int clientsock;
    clientsock = (long long)(arg);

    // Data from socket is parsed when HttpRequest is constructed
    HttpRequest req = HttpRequest(clientsock);
    HttpResponse res = HttpResponse(clientsock);

    // If there is an incoming request makes sure that it is a valid type, else throw an InvalidRequestException
    FileUploadServlet servlet = FileUploadServlet();
    if (!req.getMethod().empty()) {
        try {
            if (req.getMethod() == "GET"){
                servlet.doGet(req, res);
            } else if (req.getMethod() == "POST"){
                servlet.doPost(req, res);
            } else if (req.getMethod() == "CUSTOM") {
                servlet.doCustom(req,res);
            } else {
                throw InvalidRequestException();
            }
        } catch (InvalidRequestException e) {
            cout << e.what() << endl;
        }
    }

    close(clientsock);
    return (NULL);
}
