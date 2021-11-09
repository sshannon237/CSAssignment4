#pragma once

class InvalidRequestException : public std::exception {
public:
    const char * what () const throw () {
        return "Invalid Request Exception. The accepted request types are GET, POST, and CUSTOMCLIENT";
    }
};
