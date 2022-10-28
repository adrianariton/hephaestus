#ifndef RESPONSE_H
#define RESPONSE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
class Response
{
    public:
        int stackSize;
        char* error_stack = (char*) malloc (4*1000);
        long double ldValue;
        Response(long double _ldValue, const char* _error_stack);
        void appendError(char* err);
        void clearErrors();
        char* getErrorStack();
        void logErrorStack();
        bool hasError();
};



#endif // RESPONSE_H