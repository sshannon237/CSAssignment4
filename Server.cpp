#include <sys/socket.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "ServerThread.cpp"
static void *doit(void *);
main() {

    // set up socket to listen, then create a thread
    int sock, length;
    struct sockaddr_in server;
    int msgsock;
    int i;
    pthread_t tid;

    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("opening stream socket");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 8888;

    if (bind (sock, (struct sockaddr *)&server, sizeof server) < 0)  {    perror ("binding stream socket");
    }
    listen (sock, 5);
    while(1){
        msgsock = accept(sock, (struct sockaddr *)0, (socklen_t *)0);
        if (msgsock == -1) {
            perror("accept");
        }
        printf("before thread create\n");
        // Create thread
        pthread_create(&tid, NULL, run, (void*) msgsock);
        printf("after thread create\n");
    }
}

// This is the run class. I think we can get away with just leaving this in Server.cpp 
// instead of putting it in ServerThread.cpp(We would delete ServerThread.cpp in this case)

// Finsihsed run method will look something like this:
//
// 1. open socket
// 2. create httpresponce/httprequest classes which will take in the socket and have
// methods for reading/writing to socket
// 3. parse the beginning of the request to find out if get or post request
// 4. call doGet or doPost
static void * run(void * arg) {

    // open socket
    DIR * dirp;
    struct direct *d;
    char buf1[80];
    char buf2[102400];

    int rval;
    int clientsock;
    printf("before assignment\n");
    clientsock = (long long) (arg);
    printf("after assignment\n");
    /* pthread_detach(pthread_self());*/
    // Reads socket - will be associated with HttpRequest class
    if ((rval = read(clientsock, buf1, 80)) < 0){
        perror("reading socket");
    }

    // Prints HttpRequest. This will be logic that is in the doGet method.
    printf("%s\n",buf1);


    // This opens a directory for responding to a client (doPost type things)
    dirp = opendir(buf1);
    if (dirp == NULL) {
        perror("openning dir");
        return (NULL);
    }
    buf2[0] = '\0';

    // This writes to the socket. This will associated with HttpResponce class
    while (d = readdir(dirp)) {
        strcpy(buf2,d->d_name);
        if ((rval = write(clientsock, buf2, 1024)) < 0){
            perror("writing socket");
        }
    }

    // close clientsocket
    closedir (dirp);
    close(clientsock);
    return (NULL);
}
