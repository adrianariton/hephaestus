#include "Response.h"


Response::Response(long double _ldValue,const char* _error_stack)
{

    long doubleValue = _ldValue;
    strcpy(error_stack, _error_stack);
    stackSize = 1;
}

void Response::appendError(char* err){
    strcat(error_stack,  err);
    stackSize ++;
}

void Response::clearErrors(){
    strcpy(error_stack,  "");

    stackSize = 0;
}

char* Response::getErrorStack(){
    return error_stack;
}

void Response::logErrorStack(){
    printf(error_stack);
}

bool Response::hasError(){
    return strcmp(getErrorStack(), "") != 0;
}

