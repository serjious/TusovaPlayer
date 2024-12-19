#ifndef ERROR_H
#define ERROR_H

#include <string.h>

class Error {
    char *msg;
public:
    Error(const char* comment) { msg = strdup(comment); }
    ~Error() { delete[] msg; }
    const char* What() const { return msg; }
};

class UserError : public Error {
public:
    UserError(const char* comment)
        : Error(comment) {}
};

class ExternalError : public Error {
public:
    ExternalError(const char* comment)
        : Error(comment) {}
};

class Bug : public Error {
public:
    Bug(const char* comment)
        : Error(comment) {}
};

class EmptyListError : public UserError {
public:
    EmptyListError()
        : UserError("AudioPlayer are empty") {}
};

#endif
