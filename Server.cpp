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
    int addrlen = sizeof(server);
    int new_socket;
    char *hello = "Hello From Server";
    int valread;
    char buffer[1024] = {0};
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

    if (bind(sock, (struct sockaddr *)&server, sizeof server) < 0) {
        perror("binding stream socket");
    }
    listen(sock, 5);

    if ((new_socket = accept(sock, (struct sockaddr *)&server, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //Read Picture Size
    printf("Reading Picture Size\n");
    int size;
    read(new_socket, &size, sizeof(int));
    
    // Read Picture Byte Array
    printf("Reading Picture Byte Array\n");
    char p_array[size];
    int bytesRead = 0;
    int result;
    while (bytesRead < size) {
        result = read(new_socket, p_array + bytesRead, size - bytesRead);
        bytesRead += result;
    }

    //Convert it Back into Picture
    printf("Converting Byte Array to Picture\n");
    FILE *image;
    image = fopen("images/c1.png", "wb");
    fwrite(p_array, 1, sizeof(p_array), image);
    fclose(image);

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

// This is the run class. I think we can get away with just leaving this in Server.cpp
// instead of putting it in ServerThread.cpp(We would delete ServerThread.cpp in this case)

// Finished run method will look something like this:
//
// 1. open socket
// 2. create httpresponce/httprequest classes which will take in the socket and have
// methods for reading/writing to socket
// 3. parse the beginning of the request to find out if get or post request
// 4. call doGet or doPost
static void *run(void *arg) {

    int rval;
    int clientsock;
    clientsock = (long long)(arg);
    HttpRequest req = HttpRequest(clientsock);
    HttpResponse res = HttpResponse(clientsock);

    FileUploadServlet servlet = FileUploadServlet();

    if (req.getMethod() == "GET"){
        servlet.doGet(req, res);
    } else if (req.getMethod() == "POST"){
        servlet.doPost(req, res);
    } else if (req.getMethod() == "CUSTOM") {
        servlet.doCustom(req,res);
    }

    close(clientsock);
    
    return (NULL);
}
