# CSAssignment4

##Run the Application:
1. Run the server
   1. Navigate to the CSAssignment 4 folder in Cygwin terminal
   2. `g++ -o server HttpRequest.hpp HttpRequest.cpp HttpResponse.hpp HttpResponse.cpp Servlet.hpp FileUploadServlet.hpp FileUploadServlet.cpp Server.cpp `
   3. `./server.exe`
2. Run the client app
   4. Navigate to the CSAssignment 4 folder in Cygwin terminal
   5. `g++ -o socketclient socketclient.cpp Activity.cpp`
   6. `./socketclient.exe`
   7. Follow the prompts in the console
3. Access the server through browser
   1. Navigate to localhost:8888 on a web browser
   2. Fill out the form

##Work Distribution
Jimun Jang
1. Native console client.
2. Sending images over native console client to server
3. Fixed major bug with oversized images in buffer
4. Create and handle custom requests to the server

Sam Shannon
1. Browser client
2. Sending images over http to server
3. Create and handle HTTP get and POST request to server
4. Implement multithreading for server to handle multiple requests

Christopher Spooner
1. Created POST request directory logic to display directory info to HTML
2. Fix bug where writing to client console was not working
3. Create custom exception and implement in server
4. Refactor and comment code, create readme.

Bryan Xing
1. Created POST request directory logic to display directory info to client console
2. Fix bug where writing to client console was not working
3. JSON conversion logic
4. Pair programming with Jimun to build client application

Keegan Maundrell
N/A

##Notes
1. Custom exception implemented
2. Multithreading implemented
3. All file type uploads supported