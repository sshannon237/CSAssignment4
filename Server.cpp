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

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
// #include "Servlet.hpp"
#include "FileUploadServlet.hpp"
using namespace std;
static void *run(void *);
main()
{
    // set up socket to listen, then create a thread
    int sock, length;
    struct sockaddr_in server;
    int msgsock;
    int i;
    pthread_t tid;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("opening stream socket");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sock, (struct sockaddr *)&server, sizeof server) < 0)
    {
        perror("binding stream socket");
    }
    listen(sock, 5);
    while (1)
    {
        msgsock = accept(sock, (struct sockaddr *)0, (socklen_t *)0);
        if (msgsock == -1)
        {
            perror("accept");
        }
        // Create thread
        pthread_create(&tid, NULL, run, (void *)msgsock);
    }
}

// This is the run class. I think we can get away with just leaving this in Server.cpp
// instead of putting it in ServerThread.cpp(We would delete ServerThread.cpp in this case)

// Finished run method will look something like this:
//
// 1. open socket
// 2. create httpresponce/httprequest classes which will take in the socket and have
// methods for reading/writing to socket
// 3. parse the beginning of the request to find out if get or post request
// 4. call doGet or doPost
static void *run(void *arg)
{

    // DIR *dirp;
    // struct direct *d;
    char reqType[1024];
    char buf2[102400];
    // open socket
    int rval;
    int clientsock;
    clientsock = (long long)(arg);
    HttpRequest req = HttpRequest(clientsock);
    HttpResponse res = HttpResponse(clientsock);
    /* pthread_detach(pthread_self());*/
    // Reads socket - will be associated with HttpRequest class
    // if ((rval = read(clientsock, buf1, 80)) < 0){
    //     perror("reading socket");
    // }

    // Read first x bits to figure out if get request or post request

    req.readReq(reqType, 1024);

    string reqTypeStr(reqType);

    FileUploadServlet servlet = FileUploadServlet();

    if (reqTypeStr.find("GET / ") != string::npos)
    {
        servlet.doGet(req, res);
    }
    else if (reqTypeStr.find("POST") != string::npos)
    {
        servlet.doPost(req, res);
    }

    // char res3[] = "";

    // res.writeRes(res1,1024);
    // res.writeRes(res2,1024);
    // res.writeRes(res3,1024);

    //call doGet or doPost

    // Prints HttpRequest. This will be logic that is in the doGet method.

    // This opens a directory for responding to a client (doPost type things)
    // dirp = opendir(buf1);
    // if (dirp == NULL) {
    //     perror("openning dir");
    //     return (NULL);
    // }
    // buf2[0] = '\0';

    // This writes to the socket. This will associated with HttpResponce class
    // while (d = readdir(dirp)) {
    //     strcpy(buf2,d->d_name);
    // res.writeRes(buf2,1024);
    // if ((rval = write(clientsock, res1, 1024)) < 0)
    // {
    //     perror("writing socket");
    // }

    // }

    // close clientsocket
    // closedir(dirp);
    close(clientsock);
    return (NULL);
}
