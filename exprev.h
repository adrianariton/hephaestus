/**
 Copy Right Ariton Adrian!
 © Ariton Adrian!
*/
#ifndef EXPREV_H
#define EXPREV_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Response.h"
#include <iostream>
#include <vector>


#define CONSTANT_E 2.71828182845904523536
#define CONSTANT_PI 3.14159265358979323846


#define SIN "sin"
#define COS "cos"
#define TAN "tan"
#define COT "cot"
#define LN "ln"
#define SQRT "sqrt"
#define ABS "abs"



#define MAX 2000
/**Function pointers to be returned*/
typedef long double (*fptr)(long double);//-
typedef long double (fnc)(long double);//-
typedef long double (*fptrldb)(long double);//-
#define BASIC_FUNC_NR 12
inline const std::string MVE_BASIC_FUNC_NAMES[BASIC_FUNC_NR] = {
    "sin",
    "cos",
    "tan",
    "cot",
    "ln",
    "atan",
    "acot",
    "sinh",
    "cosh",
    "sqrt",
    "abs",
    "sum"
};
inline long double _cot(long double _x){
    return std::cos(_x)/std::sin(_x);
}
inline long double _acot(long double _x){
    return std::atan(1.0/_x);
}
inline long double _filler_function(long double _x){
    return 1.0;
}
inline const fptrldb MVE_BASIC_FUNC_POINTERS[BASIC_FUNC_NR] = {
    std::sin,
    std::cos,
    std::tan,
    _cot,
    std::log,
    std::atan,
    _acot,
    std::sinh,
    std::cosh,
    std::sqrt,
    std::abs,
    _filler_function

};
inline const int MVE_BASIC_FUNC_PARAM_NR[BASIC_FUNC_NR] = {
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    5

};
/**Types that will be used*/
/**
    In obtaining the @outputQueue from the RPN method
    0 - NUMBER
    1 - OPERATOR
    3 - FUNCTION
    4 - PARANTHESIS

    In solving the RPN, to get a result
    0 - NUMBER
    1 - OPERATOR
    2 - FUNCTION (2 VARS - ACTS LIKE OPERATOR)
    3 - FUNCTION (SINGLE - VARRED)
    4 - PARANTHESIS
    9 - DELETED
*/


/**Boolean Functions 0- false, 1- true*/

inline int isDigit(char c){
    if('0' <=c && c<='9'){
        return 1;
    }
    return 0;
}

inline int isDigitOrPoint(char c){
    if(isDigit(c) || c=='.'){
        return 1;
    }
    return 0;
}

inline int isOperator(char c){
    if(c=='*' || c=='+' || c=='-' || c=='/' || c=='^'){
        return 1;
    }
    return 0;
}

inline int isParanthesis(char c) {
    if(c=='(' || c==')'){
        return 1;
    }
    return 0;
}
inline int isLetter(char c){
    if('a' <= c && 'z'>= c || c=='_'){
        return 1;
    }
    return 0;
}




/**Function that checks the identity of a function 'string' (d.b whether it is SIN or COS etc)*/
inline int isSIN(char fct[MAX], int fctlen){
    for(int it=0;it<fctlen;++it){
        if(fct[it] != SIN[it]){
            return 0;
        }
    }
    return 1;
}
inline int isCOS(char fct[MAX], int fctlen){
    for(int it=0;it<fctlen;++it){
        if(fct[it] != COS[it]){
            return 0;
        }
    }
    return 1;
}
inline int isCOT(char fct[MAX], int fctlen){
    for(int it=0;it<fctlen;++it){
        if(fct[it] != COT[it]){
            return 0;
        }
    }
    return 1;
}
inline int isTAN(char fct[MAX], int fctlen){
    for(int it=0;it<fctlen;++it){
        if(fct[it] != TAN[it]){
            return 0;
        }
    }
    return 1;
}
inline int isLN(char fct[MAX], int fctlen){
    for(int it=0;it<fctlen;++it){
        if(fct[it] != LN[it]){
            return 0;
        }
    }
    return 1;
}
inline int isSQRT(char fct[MAX], int fctlen){
    for(int it=0;it<fctlen;++it){
        if(fct[it] != SQRT[it]){
            return 0;
        }
    }
    return 1;
}
inline int isABS(char fct[MAX], int fctlen){
    for(int it=0;it<fctlen;++it){
        if(fct[it] != ABS[it]){
            return 0;
        }
    }
    return 1;
}
inline int isSingleVariabled(char fct[MAX], int fctlen){
    if(isCOS(fct, fctlen) || isTAN(fct, fctlen) || isCOT(fct, fctlen) || isSIN(fct, fctlen) || isLN(fct, fctlen) || isSQRT(fct, fctlen) || isABS(fct, fctlen)){
        return 1;
    }
    return 0;
}

inline int is(char fct[MAX], int fctlen, char what[MAX], int whlen){

    if(whlen-1 != fctlen){
        return 0;
    }
    for(int it=0;it<fctlen;++it){
        if(fct[it] != what[it]){
            return 0;
        }
    }
    return 1;
}






//** Non pointers function -/
/** Solves for operators: * ^ - + / */
inline long double solveFor2V0(char op, long double param1, long double param2){
    switch(op){
        case '+':
            return param1 + param2;
            break;
        case '-':
            return param1 - param2;
            break;
        case '*':
            return param1 * param2;
            break;
        case '/':
            return param1 / param2;
            break;
        case '^':
            return (long double)pow((double)param1, (double)param2);
            break;
    }
}

/** Solves for operators:  Single parametrized functions*/
inline long double solveFor1VF(char fct[MAX], int fctlen, long double param){
    if(!isSingleVariabled(fct, fctlen)){
        printf("\nResult might vary, because the input is incomplete:\n    err: Only one argument passed to two-argument function!");
        return 0.0;
    }

    if(isSIN(fct, fctlen)){
        return (long double)sin((double)param);
    }

    if(isCOS(fct, fctlen)){
        return (long double)cos((double)param);
    }

    if(isTAN(fct, fctlen)){
        return (long double)tan((double)param);
    }

    if(isCOT(fct, fctlen)){
        return 1.0/(long double)tan((double)param);
    }

    if(isLN(fct, fctlen)){
        return (long double)log((double)param);
    }
    if(isSQRT(fct, fctlen)){
        if(param < 0){
            printf("Error NaN Sqrt");

        }
        return (long double)sqrt((double)param);
    }

    if(isABS(fct, fctlen)){
        return param > 0 ? param : (-param);
    }
    printf("\nResult might vary, because a function was not recognised:\n    err: undef");
    return 0.0;
}   



#define MINUS_CH 'm'




/**
 * @brief Calculates expression at given params. Initially written in C hence the use of char* instead of string.
 * Can be used in C if you remove all instances of Response and just return the solution and throw the errors.
 * @deprecated It is buggy
 * @param expr Expression string
 * @param len Expression length
 * @param trace If messages should be written. Set to false for normal run and to true for debugging
 * @param var_nr Number of params (variables)
 * @param vnames Names of the variables 
 * @param varvals Values of the variables
 * @return Response 
 */
inline Response exv_parseExpressionWithVars(char expr[], int len, int trace, int var_nr, char** vnames,  long double* varvals){

    /** the initial response, with result 0 [not found out yet] and 0 errors */
    Response _resp = Response(0.0, "");

    /** Initially [will] parsed */
    char parsed[MAX][MAX/20];
    int lengths[MAX];
    int type[MAX];
    long double numberValue[MAX];


    /**
    Output queue
        @pop - pops front
        @push - pushes back
        @all are hard-coded
    */
    long double outputQueue[MAX];
    int outputQueueIterator = 0;
    int outQ_End = 0, outQ_Begin = 0;
    char outputQueueChar[MAX][MAX/20];
    int outputQueueCharLenghts[MAX];
    int outputQueueCharTypes[MAX];



    /**
    Operator Stack
        @pop - pops back
        @push - pushes back
        @all are hard-coded
    */
    char operatorStack[MAX][MAX/20];
    int opStackLengths[MAX];
    int opertaorStackIterator = 0;
    int opS_End = 0, opS_Begin =0;

    /**Parse expr string*/
    int index = 0, i=0;
    int _sgn = 1;
    while(i<len){

       

        if(isDigit(expr[i])){ /**If digit, store the long double value in @numberValue and assign type @num @0. This will later be stored in @outputQueue. Also store the value in the @parsed char array*/
            long double num = 0.0;
            int p = 0;
            while(isDigit(expr[i])){
                num*=10;
                num+=expr[i] - '0';
                parsed[index][p] = expr[i];
                p++;
                i++;
            }

            if(expr[i] == '.'){
                parsed[index][p] = expr[i];
                p++;
                i++;
                long double po=1.0;
                while(isDigit(expr[i])){
                    po*=10.0;
                    num+=(expr[i] - '0')/po;

                    parsed[index][p] = expr[i];
                    p++;
                    i++;
                }
            }
            lengths[index]  = p;
            type[index] = 0;
            
            if(i>0 && expr[i-p-1] == MINUS_CH){
                _sgn = -1;
                //printf("\n\nSS-S: Num: %d, %d, %d,  %c, t: %c\n\n", num, _sgn, i, expr[i-p-1], expr[i]);
            } 
            //printf("\n\nSSS:Num: %d, %d, %d, %d, %c, t: %c\n\n",num, _sgn, i,p, expr[i-p-1], expr[i]);
            numberValue[index] = _sgn*num;
            index++;
        } else if(isOperator(expr[i]) || isParanthesis(expr[i])){ /**If is operator or parenthesis assign type accordingly: @1 @op, @4 @par. And store the value in the @parsed char array*/
            parsed[index][0] = expr[i];
            lengths[index]  = 1;
            if(isParanthesis(expr[i])){
                type[index] = 4;

            } else {
                type[index] = 1;

            }
            _sgn = 1;

            index++;
            i++;
        } else if(('a' <= expr[i] && 'z'>= expr[i] || expr[i] == '_' ) && !(expr[i] == MINUS_CH && !isLetter(expr[(i > 0) ? (i-1) : (i+1)]) && !isLetter(expr[i+1]) ) ){ /**If it isnt just MINUS_CHAR and if it contains letters, it is a function, assign type @3 @fun. And store the value in the @parsed char array*/
            int q = 0;
            while('a' <= expr[i] && 'z'>= expr[i] || expr[i] == '_'){

                parsed[index][q] = expr[i];
                i++;
                q++;
            }
            lengths[index]  = q;
            type[index] = 3;

            _sgn = 1;


            index++;
        } else { /**If there is sth else there, probably whitespace, ignore it.*/
            i++;
            if(expr[i] == MINUS_CH && !isLetter(expr[(i > 0) ? (i-1) : (i+1)]) && !isLetter(expr[i+1]) ){
                _sgn = -1;
            } else {
                _sgn = 1;

            }

        }





    }

    /**From @parsed to @outputQueue and @outputQueueChar wiTh RPN*/

    /**Define precedence array*/
    int precedence[MAX];

    precedence[(int)'*'] = 2;
    precedence[(int)'/'] = 2;
    precedence[(int)'+'] = 1;
    precedence[(int)'-'] = 1;
    precedence[(int)'^'] = 3;

    if(trace){
        printf("Size: %d, complexity O(size^2) \n\n", len);

    }

    int tokensNumber = index;

    if(trace)
    {
        printf("Parsed:\n");
        for(int i=0;i<tokensNumber;++i){
            for(int j=0;j<lengths[i];++j){
                printf("%c", parsed[i][j]);
            }
            printf("  ");
        }
        printf("\n\n");

    }

    /** @@here CONSTANT AND PARAMS TRACING AND REPLACING */

    /** Every x --> @num @0*/
    if(trace){
        printf("\n\nTYP:\n");

    }
    for(int it=0;it<tokensNumber;++it){
        for(int vit = 0; vit<var_nr;++vit){
            char* vnamehere = vnames[vit];
            int sw = 1;
            if(trace){
                printf("   ");
                printf(vnames[vit]);
                printf(vnamehere);
            }
            
            
            if(lengths[it] != strlen(vnamehere)){
                sw = 0;
            } else {
                for(int li = 0; li < lengths[it]; ++li){
                    if(vnamehere[li] != parsed[it][li]){
                        sw = 0;
                    }
                }
            }
            if(sw == 1){
                //they are equal;
                if(trace){
                    printf(" ~eq  ");

                }
                type[it] = 0;

            }
        }
        
    }
    if(trace){
        printf("\n\n\nTS:\n");

        for(int it = 0;  it<tokensNumber;++it){
            printf("%d  ", type[it]);
        }
        printf("\n\n\n");
    }
    
    /** Every pi --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(is(parsed[it], lengths[it], "pi", sizeof("pi"))){
            type[it] = 0;
        }
    }

    /** Every e --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(is(parsed[it], lengths[it], "e", sizeof("e"))){
            type[it] = 0;
        }


    }
    if(trace){
        printf("\n\nNVS:\n");
        for(int it=0;it<tokensNumber;++it){
            std::cout<<numberValue[it]<<"  ";


        }
        printf("\n");

    }
    


    for(int i=0;i<tokensNumber;++i){

        if(type[i] == 0){
            /**Token @i Is Number, so add it to @outputQueue */
            outputQueue[outputQueueIterator] = numberValue[i];
            for(int j=0;j<lengths[i];++j){
                outputQueueChar[outputQueueIterator][j] = parsed[i][j];
            }
            outputQueueCharLenghts[outputQueueIterator] = lengths[i];
            outputQueueIterator++;
            outQ_End++;
        } else if(type[i] == 3){
            /**Token @i Is a function, so add it to @operatorStack */
            for(int j=0;j<lengths[i];++j){
                operatorStack[opertaorStackIterator][j] = parsed[i][j];
            }
            opStackLengths[opertaorStackIterator] = lengths[i];
            opS_End++;
            opertaorStackIterator++;

        } else if(type[i] == 1){

            /**Token is an operator*/
            char o1 = parsed[i][0];
            while(operatorStack[opS_End - 1][0] != '(' && isOperator(operatorStack[opS_End - 1][0]) && ( precedence[(int)o1] < precedence[(int)operatorStack[opS_End - 1][0]] ||
                                                             (precedence[(int)o1] == precedence[(int)operatorStack[opS_End - 1][0]]) )){
                /**there is an operator o2 other than the left parenthesis at the top
                of the operator stack, and (o2 has greater precedence than o1
                or they have the same precedence and o1 is  [NOT IMPLEMENTED YET] left-associative)*/
                    char o2 = operatorStack[opS_End - 1][0];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to @outputQueue */
                    outputQueueChar[outputQueueIterator][0] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

            }
            /**Push o1 to @operatorStack */
            operatorStack[opertaorStackIterator][0] = o1;
            opStackLengths[opertaorStackIterator] = 1;
            opertaorStackIterator ++;
            opS_End++;

        } else if(type[i] == 4 && parsed[i][0] == '('){
                /**Push ( to @opertaorStack */
                operatorStack[opertaorStackIterator][0] = parsed[i][0];
                opStackLengths[opertaorStackIterator] = 1;
                opertaorStackIterator ++;
                opS_End ++;
        } else if(type[i] == 4 && parsed[i][0] == ')'){
                while(operatorStack[opS_End - 1][0] != '('){
                    if(opS_End <= opS_Begin){
                            /**Expression is incomplete*/
                            _resp.appendError("\nExpression is incomplete!");//at i
                                        return _resp;

                    }

                    char o2 = operatorStack[opS_End - 1][0];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to charQueue*/
                    outputQueueChar[outputQueueIterator][0] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

                }

                /** There must be  a left parenthesis at the top of @operatorStack */

                /** If not, return error!*/
                if(operatorStack[opS_End - 1][0] != '('){
                    _resp.appendError("\nParentheses do not match!");
                    return _resp;

                }

                /**else, all is good, discard it and go on*/
                opS_End --;
                opertaorStackIterator --;

                /**If we have a function token at the top [basically if the first letter is not an operator or parenthesis]*/

                if(!(isOperator(operatorStack[opS_End - 1][0])) && !(isParanthesis(operatorStack[opS_End - 1][0]))){
                    /**Pop the function from the @operatorStack into the outputQueue*/

                    /**Add to @outputQueue */
                    for(int j=0; j<opStackLengths[opS_End - 1]; ++j){
                        outputQueueChar[outputQueueIterator][j] = operatorStack[opS_End - 1][j];
                    }
                    outputQueueCharLenghts[outputQueueIterator] = opStackLengths[opS_End - 1];
                    outputQueueIterator ++;
                    outQ_End++;

                    /**Pop from @opStack*/
                    opS_End --;
                    opertaorStackIterator --;
                }



        }




    }
    /** Transfer the rest of the @operatorStack into the @outputQueue */
    while(opS_Begin < opS_End){
        if(operatorStack[opS_End - 1][0] == '('){
            _resp.appendError("\nExpression is incomplete!\n    err: unclosed '('.");
            return _resp;

        }

        /**Pop the function from the @operatorStack into the outputQueue*/

        /**Add to @outputQueue */
        for(int j=0; j<opStackLengths[opS_End - 1]; ++j){
            outputQueueChar[outputQueueIterator][j] = operatorStack[opS_End - 1][j];
        }
        outputQueueCharLenghts[outputQueueIterator] = opStackLengths[opS_End - 1];
        outputQueueIterator ++;
        outQ_End++;

        /**Pop from @opStack*/
        opS_End --;
        opertaorStackIterator --;


    }

    /** The RPN array is: @outputQueueChar , with it's dual (the one containing the long double correspondents on the corresponding positions -- same as in @outputQueueChar) being @outputQueue */

    /** Rough type assignment (remember that we got rid of the parentheses!) */
    /**
        0 - NUMBER
        1 - OPERATOR
        3 - FUNCTION
        4 - PARANTHESIS
    */
    for(int it = outQ_Begin; it<outQ_End;++it){
        if(outputQueueCharLenghts[it] == 1 && isOperator(outputQueueChar[it][0])){
            /** It's an operator */
            outputQueueCharTypes[it] = 1;

        } else {
            int sw = 0;
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                if(isLetter(outputQueueChar[it][j])){
                    /** It is clearly a function*/
                    outputQueueCharTypes[it] = 3;
                    sw=1;
                    break;
                }
            }
            if(sw == 0) {
               outputQueueCharTypes[it] = 0;

            }
        }



    }


    /** Some checking :)*/
    if(trace){
        for(int it = outQ_Begin; it<outQ_End;++it){
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                printf("%c", outputQueueChar[it][j]);
            }
            printf("  ");
        }
        printf("\n\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            printf("%d", outputQueueCharTypes[it]);
            printf("  ");
        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(outputQueueCharTypes[it] == 3){
                /**It is a function*/
                int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);
                printf("%d", isSinglVar);

            } else {
                printf("nf");
            }
            printf("  ");

        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(isDigit(outputQueueChar[it][0])){
                printf("%f", outputQueue[it]);

            } else {
                printf("op ");
            }

            printf("  ");
        }
    }


    /**Done checking*/


    /**Solve RPN*/

     /**
        0 - NUMBER
        1 - OPERATOR
        NEW: 2 - FUNCTION (2 VARS - ACTS LIKE OPERATOR)
        3 - FUNCTION (SINGLE - VARRED)
        4 - PARANTHESIS
        9 - DELETED
    */
   if(trace){
    printf("\nVARS:");

   }
    /**Replace variable with @xis*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        if(trace){
            printf("\n");

        }
        for(int vit = 0; vit<var_nr;++vit){
            
            char* vnamehere = vnames[vit];
            if(trace){
                printf("   ");
                printf(vnames[vit]);
                printf("~");
                printf(outputQueueChar[it]);
            }
            
            int sw = 1, ind;

            if(outputQueueCharLenghts[it] != strlen(vnamehere)){
                sw= 0;
            } else {
                for(int li = 0; li < outputQueueCharLenghts[it]; ++li){
                    if(vnamehere[li] != outputQueueChar[it][li]){
                        sw = 0;
                    }
                }
            }   
           // printf("A");
            if(sw == 1){
                //they are equal;
                if(trace){
                    printf(":=  ");

                }
                                      //  printf("A");

                outputQueueCharTypes[it] = 0;
                                    //    printf("A");

                outputQueue[it]= varvals[vit];

            }
                        //printf("A");

        }
        
    }


    /**Replace @e with @math@e*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "e", sizeof("e"))){
            /**Treat it as number and replace it with @mathe@e*/
            outputQueueCharTypes[it] = 0;
            outputQueue[it]= CONSTANT_E;

        }
    }

    /**Replace @pi with @math@pi*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "pi", sizeof("pi"))){
            /**Treat it as number and replace it with @mathe@pi*/
            outputQueueCharTypes[it] = 0;
            outputQueue[it]= CONSTANT_PI;

        }
    }

    if(trace){
        printf("\nTR1\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                printf("%c", outputQueueChar[it][j]);
            }
            printf("  ");
        }
        printf("\n\nOU TS:\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            printf("%d", outputQueueCharTypes[it]);
            printf("  ");
        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(outputQueueCharTypes[it] == 3){
                /**It is a function*/
                int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);
                printf("%d", isSinglVar);

            } else {
                printf("nf");
            }
            printf("  ");

        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(isDigit(outputQueueChar[it][0])){
                printf("%f", outputQueue[it]);

            } else {
                printf("op ");
            }

            printf("  ");
        }
    }

    for(int it = outQ_Begin; it<outQ_End;++it){
        /**If it is a function*/

        if(outputQueueCharTypes[it] == 3){
            int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);

            /** If it isn't singleVarred, change the type to @2 */
            if(!isSinglVar){
               outputQueueCharTypes[it] == 2;
            }

        }

    }

    /** FROM NOW ON, THE NUMBERS WILL BE TAKEN ONLY FROM @outputQueue */

    int deleted = 0;
    int delta_deleted = 0;
    /** @outputQueueChar , @outputQueueCharTypes , @outputQueueCharLengths */

    outputQueueIterator = outQ_Begin;

    int outQ_Len = outQ_End - outQ_Begin;

    /** Array that memorises the next positions, initially, next[i]=i+1*/

    int next[outQ_End + 1], prev[outQ_End +1];
    for(int it = outQ_Begin; it< outQ_End; ++it){
        next[it] = it+1;
        prev[it] = it-1;
    }
    next[outQ_End] = 0;
    prev[outQ_End] = outQ_End - 1;



    while(outQ_Len - deleted > 1){
        delta_deleted = 0;
        for(int it = next[outQ_End]; it< outQ_End; it = next[it]){
            /** If it is operator*/
            if(outputQueueCharTypes[it] == 1){
                /** If both the previous tokes are numbers */
                /**
                    We have a config like @num @num @op. So we solve it!
                */
                if(outputQueueCharTypes[prev[prev[it]]] == 0 && outputQueueCharTypes[prev[it]] == 0 && it>=2){
                    /**Get the 2 nrs before*/
                    long double param1 = outputQueue[prev[prev[it]]];
                    long double param2 = outputQueue[ prev[it] ];


                    long double result = solveFor2V0(outputQueueChar[it][0], param1, param2);

                    /** Replace operator val at @it wit the result for @outputQueue, and also change the type to number so we know to read said val from @outputQueue, and not from @outputQueueChar*/
                    /** The separation between long doubles and chars is made to be able to save time in not performing an eventual long double to string or string to long double operation*/

                    outputQueueCharTypes[it] = 0;
                    outputQueue[it] = result;

                    /**Delete positions prev[it] and prev[prev[it]] */

                    outputQueueCharTypes[prev[it]] = 9;
                    outputQueueCharTypes[ prev[prev[it]] ] = 9;
                    if(it<2){
                        _resp.appendError("\n2-Valued operator found with one argument!");
                        return _resp;

                    }
                    next[prev[prev[prev[it]]]] = it;
                    prev[it] = prev[prev[prev[it]]];
                    deleted += 2;
                    delta_deleted += 2;
                }
            } else if(outputQueueCharTypes[it] == 3 && it>=1){ /**If the current token is a single param function*/
                /** If the token before is a number, apply the function!*/
                if( outputQueueCharTypes[prev[it]] == 0){
                    /**Get the nr before*/
                    long double param = outputQueue[ prev[it] ];

                    long double result = solveFor1VF(outputQueueChar[it], outputQueueCharLenghts[it], param);


                    /** Replace operator val at @it wit the result for @outputQueue, and also change the type to number so we know to read said val from @outputQueue, and not from @outputQueueChar*/
                    /** The separation between long doubles and chars is made to be able to save time in not performing an eventual long double to string or string to long double operation*/

                    outputQueueCharTypes[it] = 0;
                    outputQueue[it] = result;

                    /**Delete position prev[it] */

                    outputQueueCharTypes[prev[it]] = 9;
                    if(it<1){
                        _resp.appendError("\n2-Valued operator found with one argument!");
                        return _resp;

                    }
                    next[prev[prev[it]]] = it;
                    prev[it] = prev[prev[it]];
                    deleted += 1;
                    delta_deleted +=1;
                }



            }
        }
        if(trace){
            printf("\nDeleted:%d/n", deleted);
        }
        if(delta_deleted == 0){
            _resp.appendError("Something went wrong, recheck your expression!");
            return _resp;
        }

    }
    if(trace){
        printf("Left with: \n\n");
        for(int it =outQ_Begin; it<outQ_End;++it){
            printf("%f, del?: %d\n", outputQueue[it], outputQueueCharTypes[it]);
        }

        printf("\n\n");
    }

    if(trace){
        printf("Result: %f", outputQueue[outQ_End - 1]);
        printf("\n\nComplete!\n");
        printf("-------------------------------------------------------\n\n");
    }

    _resp.ldValue = outputQueue[outQ_End - 1];

    return _resp;



}



/**
 * @brief Get RPNQ
 * @deprecated It is buggy
 */
inline Response exv_getRPNQ(char expr[], int len, int trace, int var_nr, char** vnames, long double* out_rpnq_nrs, std::string* out_rpnq_str, int* out_rpnq_types, int& out_rlen){

    /** the initial response, with result 0 [not found out yet] and 0 errors */
    Response _resp = Response(0.0, "");

    /** Initially [will] parsed */
    char parsed[MAX][MAX/20];
    int lengths[MAX];
    int type[MAX];
    long double numberValue[MAX];


    /**
    Output queue
        @pop - pops front
        @push - pushes back
        @all are hard-coded
    */
    long double outputQueue[MAX];
    int outputQueueIterator = 0;
    int outQ_End = 0, outQ_Begin = 0;
    char outputQueueChar[MAX][MAX/20];
    int outputQueueCharLenghts[MAX];
    int outputQueueCharTypes[MAX];
    int outputQueueIsVar[MAX];
    std::string outputQueueVars[MAX];



    /**
    Operator Stack
        @pop - pops back
        @push - pushes back
        @all are hard-coded
    */
    char operatorStack[MAX][MAX/20];
    int opStackLengths[MAX];
    int opertaorStackIterator = 0;
    int opS_End = 0, opS_Begin =0;

    /**Parse expr string*/
    int index = 0, i=0;
    int _sgn = 1;
    while(i<len){

       

        if(isDigit(expr[i])){ /**If digit, store the long double value in @numberValue and assign type @num @0. This will later be stored in @outputQueue. Also store the value in the @parsed char array*/
            long double num = 0.0;
            int p = 0;
            while(isDigit(expr[i])){
                num*=10;
                num+=expr[i] - '0';
                parsed[index][p] = expr[i];
                p++;
                i++;
            }

            if(expr[i] == '.'){
                parsed[index][p] = expr[i];
                p++;
                i++;
                long double po=1.0;
                while(isDigit(expr[i])){
                    po*=10.0;
                    num+=(expr[i] - '0')/po;

                    parsed[index][p] = expr[i];
                    p++;
                    i++;
                }
            }
            lengths[index]  = p;
            type[index] = 0;
            
            if(i>0 && expr[i-p-1] == MINUS_CH){
                _sgn = -1;
                //printf("\n\nSS-S: Num: %d, %d, %d,  %c, t: %c\n\n", num, _sgn, i, expr[i-p-1], expr[i]);
            } 
            //printf("\n\nSSS:Num: %d, %d, %d, %d, %c, t: %c\n\n",num, _sgn, i,p, expr[i-p-1], expr[i]);
            numberValue[index] = _sgn*num;
            index++;
        } else if(isOperator(expr[i]) || isParanthesis(expr[i])){ /**If is operator or parenthesis assign type accordingly: @1 @op, @4 @par. And store the value in the @parsed char array*/
            parsed[index][0] = expr[i];
            lengths[index]  = 1;
            if(isParanthesis(expr[i])){
                type[index] = 4;

            } else {
                type[index] = 1;

            }
            _sgn = 1;

            index++;
            i++;
        } else if(('a' <= expr[i] && 'z'>= expr[i] || expr[i] == '_' ) && !(expr[i] == MINUS_CH && !isLetter(expr[(i > 0) ? (i-1) : (i+1)]) && !isLetter(expr[i+1]) ) ){ /**If it isnt just MINUS_CHAR and if it contains letters, it is a function, assign type @3 @fun. And store the value in the @parsed char array*/
            int q = 0;
            while('a' <= expr[i] && 'z'>= expr[i] || expr[i] == '_'){

                parsed[index][q] = expr[i];
                i++;
                q++;
            }
            lengths[index]  = q;
            type[index] = 3;

            _sgn = 1;


            index++;
        } else { /**If there is sth else there, probably whitespace, ignore it.*/
            i++;
            if(expr[i] == MINUS_CH && !isLetter(expr[(i > 0) ? (i-1) : (i+1)]) && !isLetter(expr[i+1]) ){
                _sgn = -1;
            } else {
                _sgn = 1;

            }

        }





    }

    /**From @parsed to @outputQueue and @outputQueueChar wiTh RPN*/

    /**Define precedence array*/
    int precedence[MAX];

    precedence[(int)'*'] = 2;
    precedence[(int)'/'] = 2;
    precedence[(int)'+'] = 1;
    precedence[(int)'-'] = 1;
    precedence[(int)'^'] = 3;

    if(trace){
        printf("Size: %d, complexity O(size^2) \n\n", len);

    }

    int tokensNumber = index;

    if(trace)
    {
        printf("Parsed:\n");
        for(int i=0;i<tokensNumber;++i){
            for(int j=0;j<lengths[i];++j){
                printf("%c", parsed[i][j]);
            }
            printf("  ");
        }
        printf("\n\n");

    }

    /** @@here CONSTANT AND PARAMS TRACING AND REPLACING */

    /** Every x --> @num @0*/
    if(trace){
        printf("\n\nTYP:\n");

    }
    for(int it=0;it<tokensNumber;++it){
        for(int vit = 0; vit<var_nr;++vit){
            char* vnamehere = vnames[vit];
            int sw = 1;
            if(trace){
                printf("   ");
                printf(vnames[vit]);
                printf(vnamehere);
            }
            
            
            if(lengths[it] != strlen(vnamehere)){
                sw = 0;
            } else {
                for(int li = 0; li < lengths[it]; ++li){
                    if(vnamehere[li] != parsed[it][li]){
                        sw = 0;
                    }
                }
            }
            if(sw == 1){
                //they are equal;
                if(trace){
                    printf(" ~eq  ");

                }
                type[it] = 0;

            }
        }
        
    }
    if(trace){
        printf("\n\n\nTS:\n");

        for(int it = 0;  it<tokensNumber;++it){
            printf("%d  ", type[it]);
        }
        printf("\n\n\n");
    }
    
    /** Every pi --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(is(parsed[it], lengths[it], "pi", sizeof("pi"))){
            type[it] = 0;
        }
    }

    /** Every e --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(is(parsed[it], lengths[it], "e", sizeof("e"))){
            type[it] = 0;
        }


    }
    if(trace){
        printf("\n\nNVS:\n");
        for(int it=0;it<tokensNumber;++it){
            std::cout<<numberValue[it]<<"  ";


        }
        printf("\n");

    }
    


    for(int i=0;i<tokensNumber;++i){

        if(type[i] == 0){
            /**Token @i Is Number, so add it to @outputQueue */
            outputQueue[outputQueueIterator] = numberValue[i];
            for(int j=0;j<lengths[i];++j){
                outputQueueChar[outputQueueIterator][j] = parsed[i][j];
            }
            outputQueueCharLenghts[outputQueueIterator] = lengths[i];
            outputQueueIterator++;
            outQ_End++;
        } else if(type[i] == 3){
            /**Token @i Is a function, so add it to @operatorStack */
            for(int j=0;j<lengths[i];++j){
                operatorStack[opertaorStackIterator][j] = parsed[i][j];
            }
            opStackLengths[opertaorStackIterator] = lengths[i];
            opS_End++;
            opertaorStackIterator++;

        } else if(type[i] == 1){

            /**Token is an operator*/
            char o1 = parsed[i][0];
            while(operatorStack[opS_End - 1][0] != '(' && isOperator(operatorStack[opS_End - 1][0]) && ( precedence[(int)o1] < precedence[(int)operatorStack[opS_End - 1][0]] ||
                                                             (precedence[(int)o1] == precedence[(int)operatorStack[opS_End - 1][0]]) )){
                /**there is an operator o2 other than the left parenthesis at the top
                of the operator stack, and (o2 has greater precedence than o1
                or they have the same precedence and o1 is  [NOT IMPLEMENTED YET] left-associative)*/
                    char o2 = operatorStack[opS_End - 1][0];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to @outputQueue */
                    outputQueueChar[outputQueueIterator][0] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

            }
            /**Push o1 to @operatorStack */
            operatorStack[opertaorStackIterator][0] = o1;
            opStackLengths[opertaorStackIterator] = 1;
            opertaorStackIterator ++;
            opS_End++;

        } else if(type[i] == 4 && parsed[i][0] == '('){
                /**Push ( to @opertaorStack */
                operatorStack[opertaorStackIterator][0] = parsed[i][0];
                opStackLengths[opertaorStackIterator] = 1;
                opertaorStackIterator ++;
                opS_End ++;
        } else if(type[i] == 4 && parsed[i][0] == ')'){
                while(operatorStack[opS_End - 1][0] != '('){
                    if(opS_End <= opS_Begin){
                            /**Expression is incomplete*/
                            _resp.appendError("\nExpression is incomplete!");//at i
                                        return _resp;

                    }

                    char o2 = operatorStack[opS_End - 1][0];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to charQueue*/
                    outputQueueChar[outputQueueIterator][0] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

                }

                /** There must be  a left parenthesis at the top of @operatorStack */

                /** If not, return error!*/
                if(operatorStack[opS_End - 1][0] != '('){
                    _resp.appendError("\nParentheses do not match!");
                    return _resp;

                }

                /**else, all is good, discard it and go on*/
                opS_End --;
                opertaorStackIterator --;

                /**If we have a function token at the top [basically if the first letter is not an operator or parenthesis]*/

                if(!(isOperator(operatorStack[opS_End - 1][0])) && !(isParanthesis(operatorStack[opS_End - 1][0]))){
                    /**Pop the function from the @operatorStack into the outputQueue*/

                    /**Add to @outputQueue */
                    for(int j=0; j<opStackLengths[opS_End - 1]; ++j){
                        outputQueueChar[outputQueueIterator][j] = operatorStack[opS_End - 1][j];
                    }
                    outputQueueCharLenghts[outputQueueIterator] = opStackLengths[opS_End - 1];
                    outputQueueIterator ++;
                    outQ_End++;

                    /**Pop from @opStack*/
                    opS_End --;
                    opertaorStackIterator --;
                }



        }




    }
    /** Transfer the rest of the @operatorStack into the @outputQueue */
    while(opS_Begin < opS_End){
        if(operatorStack[opS_End - 1][0] == '('){
            _resp.appendError("\nExpression is incomplete!\n    err: unclosed '('.");
            return _resp;

        }

        /**Pop the function from the @operatorStack into the outputQueue*/

        /**Add to @outputQueue */
        for(int j=0; j<opStackLengths[opS_End - 1]; ++j){
            outputQueueChar[outputQueueIterator][j] = operatorStack[opS_End - 1][j];
        }
        outputQueueCharLenghts[outputQueueIterator] = opStackLengths[opS_End - 1];
        outputQueueIterator ++;
        outQ_End++;

        /**Pop from @opStack*/
        opS_End --;
        opertaorStackIterator --;


    }

    /** The RPN array is: @outputQueueChar , with it's dual (the one containing the long double correspondents on the corresponding positions -- same as in @outputQueueChar) being @outputQueue */

    /** Rough type assignment (remember that we got rid of the parentheses!) */
    /**
        0 - NUMBER
        1 - OPERATOR
        3 - FUNCTION
        4 - PARANTHESIS
    */
    for(int it = outQ_Begin; it<outQ_End;++it){
        if(outputQueueCharLenghts[it] == 1 && isOperator(outputQueueChar[it][0])){
            /** It's an operator */
            outputQueueCharTypes[it] = 1;

        } else {
            int sw = 0;
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                if(isLetter(outputQueueChar[it][j])){
                    /** It is clearly a function*/
                    outputQueueCharTypes[it] = 3;
                    sw=1;
                    break;
                }
            }
            if(sw == 0) {
               outputQueueCharTypes[it] = 0;

            }
        }



    }


    /** Some checking :)*/
    if(trace){
        for(int it = outQ_Begin; it<outQ_End;++it){
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                printf("%c", outputQueueChar[it][j]);
            }
            printf("  ");
        }
        printf("\n\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            printf("%d", outputQueueCharTypes[it]);
            printf("  ");
        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(outputQueueCharTypes[it] == 3){
                /**It is a function*/
                int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);
                printf("%d", isSinglVar);

            } else {
                printf("nf");
            }
            printf("  ");

        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(isDigit(outputQueueChar[it][0])){
                printf("%f", outputQueue[it]);

            } else {
                printf("op ");
            }

            printf("  ");
        }
    }


    /**Done checking*/


    /**Solve RPN*/

     /**
        0 - NUMBER
        1 - OPERATOR
        NEW: 2 - FUNCTION (2 VARS - ACTS LIKE OPERATOR)
        3 - FUNCTION (SINGLE - VARRED)
        4 - PARANTHESIS
        9 - DELETED
    */
   if(trace){
    printf("\nVARS:");

   }
    /**Replace variable with @xis*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        if(trace){
            printf("\n");

        }
        int scw = 0;
        for(int vit = 0; vit<var_nr;++vit){
            
            char* vnamehere = vnames[vit];
            
            int sw = 1, ind;

            if(outputQueueCharLenghts[it] != strlen(vnamehere)){
                sw= 0;
            } else {
                for(int li = 0; li < outputQueueCharLenghts[it]; ++li){
                    if(vnamehere[li] != outputQueueChar[it][li]){
                        sw = 0;
                    }
                }
            }   
           // printf("A");
            if(sw == 1){
                //they are equal;
                if(trace){
                    printf(":=  ");

                }
                                      //  printf("A");

                outputQueueCharTypes[it] = 0;
                //HAHAHA
                outputQueueIsVar[it] = 5;
                outputQueueVars[it] = vnamehere;
                scw = 1;
                 

            } 
                        //printf("A");

        }
        if(scw==0){
                outputQueueIsVar[it] = 0;
            
        }
        
    }


    /**Replace @e with @math@e*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "e", sizeof("e"))){
            /**Treat it as number and replace it with @mathe@e*/
            outputQueueCharTypes[it] = 5;
            //outputQueue[it]= CONSTANT_E;

        }
    }

    /**Replace @pi with @math@pi*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "pi", sizeof("pi"))){
            /**Treat it as number and replace it with @mathe@pi*/
            outputQueueCharTypes[it] = 5;
            //outputQueue[it]= CONSTANT_PI;

        }
    }

    if(trace){
        printf("\nTR1\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                printf("%c", outputQueueChar[it][j]);
            }
            printf("  ");
        }
        printf("\n\nOU TS:\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            printf("%d", outputQueueCharTypes[it]);
            printf("  ");
        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(outputQueueCharTypes[it] == 3){
                /**It is a function*/
                int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);
                printf("%d", isSinglVar);

            } else {
                printf("nf");
            }
            printf("  ");

        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(isDigit(outputQueueChar[it][0])){
                printf("%f", outputQueue[it]);

            } else {
                printf("op ");
            }

            printf("  ");
        }
    }

    for(int it = outQ_Begin; it<outQ_End;++it){
        /**If it is a function*/

        if(outputQueueCharTypes[it] == 3){
            int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);

            /** If it isn't singleVarred, change the type to @2 */
            if(!isSinglVar){
               outputQueueCharTypes[it] == 2;
            }

        }

    }
     /**
        0 - NUMBER
        1 - OPERATOR
        NEW: 2 - FUNCTION (2 VARS - ACTS LIKE OPERATOR)
        3 - FUNCTION (SINGLE - VARRED)
        4 - PARANTHESIS
        9 - DELETED
    */
    for(int it = outQ_Begin; it<outQ_End;++it){
        if(outputQueueIsVar[it] != 5){
            
            out_rpnq_types[it] = outputQueueCharTypes[it];
        } else {
            out_rpnq_types[it] = 5;
        }
        if(out_rpnq_types[it] == 0){  // if is number 
            out_rpnq_nrs[it] = outputQueue[it];
        } else {
            out_rpnq_str[it] = outputQueueChar[it];
            out_rpnq_str[it].resize(outputQueueCharLenghts[it]);
        }
        if(out_rpnq_types[it] == 5){
            out_rpnq_str[it] = outputQueueVars[it];
        }

    }
    /**Replace @e with @math@e*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "e", sizeof("e"))){
            /**Treat it as number and replace it with @mathe@e*/
            out_rpnq_str[it] = 5;
            //outputQueue[it]= CONSTANT_E;

        }
    }

    /**Replace @pi with @math@pi*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "pi", sizeof("pi"))){
            /**Treat it as number and replace it with @mathe@pi*/
            out_rpnq_str[it] = 5;
            out_rpnq_str[it] = outputQueueChar[it];

            //outputQueue[it]= CONSTANT_PI;

        }
    }
    out_rlen = outQ_End;



}
















/**
 * @brief Use exv_parseExpressionWithVars instead of this if you have multiple variables. Evaluates expression with one variable: 'x'
 * @deprecated It is buggy
 * @param expr 
 * @param len 
 * @param trace False for normal run, true for debugging
 * @param xis x's value
 * @return Response 
 */
inline Response exv_parseCreateRPNOQandSolve(char expr[], int len, int trace, long double xis){

    /** the initial response, with result 0 [not found out yet] and 0 errors */
    Response _resp = Response(0.0, "");

    /** Initially [will] parsed */
    char parsed[MAX][MAX/20];
    int lengths[MAX];
    int type[MAX];
    long double numberValue[MAX];


    /**
    Output queue
        @pop - pops front
        @push - pushes back
        @all are hard-coded
    */
    long double outputQueue[MAX];
    int outputQueueIterator = 0;
    int outQ_End = 0, outQ_Begin = 0;
    char outputQueueChar[MAX][MAX/20];
    int outputQueueCharLenghts[MAX];
    int outputQueueCharTypes[MAX];



    /**
    Operator Stack
        @pop - pops back
        @push - pushes back
        @all are hard-coded
    */
    char operatorStack[MAX][MAX/20];
    int opStackLengths[MAX];
    int opertaorStackIterator = 0;
    int opS_End = 0, opS_Begin =0;

    /**Parse expr string*/
    int index = 0, i=0;
    int _sgn = 1;
    while(i<len){

       

        if(isDigit(expr[i])){ /**If digit, store the long double value in @numberValue and assign type @num @0. This will later be stored in @outputQueue. Also store the value in the @parsed char array*/
            long double num = 0.0;
            int p = 0;
            while(isDigit(expr[i])){
                num*=10;
                num+=expr[i] - '0';

                parsed[index][p] = expr[i];
                p++;
                i++;
            }

            if(expr[i] == '.'){
                parsed[index][p] = expr[i];
                p++;
                i++;
                long double po=1.0;
                while(isDigit(expr[i])){
                    po*=10.0;
                    num+=(expr[i] - '0')/po;

                    parsed[index][p] = expr[i];
                    p++;
                    i++;
                }
            }
            lengths[index]  = p;
            type[index] = 0;
            
            if(i>0 && expr[i-p-1] == MINUS_CH){
                _sgn = -1;
                //printf("\n\nSS-S: Num: %d, %d, %d,  %c, t: %c\n\n", num, _sgn, i, expr[i-p-1], expr[i]);
            } 
            //printf("\n\nSSS:Num: %d, %d, %d, %d, %c, t: %c\n\n",num, _sgn, i,p, expr[i-p-1], expr[i]);
            numberValue[index] = _sgn*num;

            index++;
        } else if(isOperator(expr[i]) || isParanthesis(expr[i])){ /**If is operator or parenthesis assign type accordingly: @1 @op, @4 @par. And store the value in the @parsed char array*/
            parsed[index][0] = expr[i];
            lengths[index]  = 1;
            if(isParanthesis(expr[i])){
                type[index] = 4;

            } else {
                type[index] = 1;

            }
            _sgn = 1;

            index++;
            i++;
        } else if('a' <= expr[i] && 'z'>= expr[i] && !(expr[i] == MINUS_CH && !isLetter(expr[(i > 0) ? (i-1) : (i+1)]) && !isLetter(expr[i+1]) ) ){ /**If it isnt just MINUS_CHAR and if it contains letters, it is a function, assign type @3 @fun. And store the value in the @parsed char array*/
            int q = 0;
            while('a' <= expr[i] && 'z'>= expr[i]){

                parsed[index][q] = expr[i];
                i++;
                q++;
            }
            lengths[index]  = q;
            type[index] = 3;

            _sgn = 1;


            index++;
        } else { /**If there is sth else there, probably whitespace, ignore it.*/
            i++;
            if(expr[i] == MINUS_CH && !isLetter(expr[(i > 0) ? (i-1) : (i+1)]) && !isLetter(expr[i+1]) ){
                _sgn = -1;
            } else {
                _sgn = 1;

            }

        }





    }

    /**From @parsed to @outputQueue and @outputQueueChar wiTh RPN*/

    /**Define precedence array*/
    int precedence[MAX];

    precedence[(int)'*'] = 2;
    precedence[(int)'/'] = 2;
    precedence[(int)'+'] = 1;
    precedence[(int)'-'] = 1;
    precedence[(int)'^'] = 3;

    if(trace){
        printf("Size: %d, complexity O(size^2) \n\n", len);

    }

    int tokensNumber = index;

    if(trace)
    {
        printf("Parsed:\n");
        for(int i=0;i<tokensNumber;++i){
            for(int j=0;j<lengths[i];++j){
                printf("%c", parsed[i][j]);
            }
            printf("  ");
        }
        printf("\n\n");

    }

    /** @@here CONSTANT AND PARAMS TRACING AND REPLACING */

    /** Every x --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(parsed[it][0] == 'x' && lengths[it]==1){
            type[it] = 0;
        }
    }

    /** Every pi --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(is(parsed[it], lengths[it], "pi", sizeof("pi"))){
            type[it] = 0;
        }
    }

    /** Every e --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(is(parsed[it], lengths[it], "e", sizeof("e"))){
            type[it] = 0;
        }


    }

    



    for(int i=0;i<tokensNumber;++i){

        if(type[i] == 0){
            /**Token @i Is Number, so add it to @outputQueue */
            outputQueue[outputQueueIterator] = numberValue[i];
            for(int j=0;j<lengths[i];++j){
                outputQueueChar[outputQueueIterator][j] = parsed[i][j];
            }
            outputQueueCharLenghts[outputQueueIterator] = lengths[i];
            outputQueueIterator++;
            outQ_End++;
        } else if(type[i] == 3){
            /**Token @i Is a function, so add it to @operatorStack */
            for(int j=0;j<lengths[i];++j){
                operatorStack[opertaorStackIterator][j] = parsed[i][j];
            }
            opStackLengths[opertaorStackIterator] = lengths[i];
            opS_End++;
            opertaorStackIterator++;

        } else if(type[i] == 1){

            /**Token is an operator*/
            char o1 = parsed[i][0];
            while(operatorStack[opS_End - 1][0] != '(' && isOperator(operatorStack[opS_End - 1][0]) && ( precedence[(int)o1] < precedence[(int)operatorStack[opS_End - 1][0]] ||
                                                             (precedence[(int)o1] == precedence[(int)operatorStack[opS_End - 1][0]]) )){
                /**there is an operator o2 other than the left parenthesis at the top
                of the operator stack, and (o2 has greater precedence than o1
                or they have the same precedence and o1 is  [NOT IMPLEMENTED YET] left-associative)*/
                    char o2 = operatorStack[opS_End - 1][0];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to @outputQueue */
                    outputQueueChar[outputQueueIterator][0] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

            }
            /**Push o1 to @operatorStack */
            operatorStack[opertaorStackIterator][0] = o1;
            opStackLengths[opertaorStackIterator] = 1;
            opertaorStackIterator ++;
            opS_End++;

        } else if(type[i] == 4 && parsed[i][0] == '('){
                /**Push ( to @opertaorStack */
                operatorStack[opertaorStackIterator][0] = parsed[i][0];
                opStackLengths[opertaorStackIterator] = 1;
                opertaorStackIterator ++;
                opS_End ++;
        } else if(type[i] == 4 && parsed[i][0] == ')'){
                while(operatorStack[opS_End - 1][0] != '('){
                    if(opS_End <= opS_Begin){
                            /**Expression is incomplete*/
                            _resp.appendError("\nExpression is incomplete!");//at i
                                        return _resp;

                    }

                    char o2 = operatorStack[opS_End - 1][0];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to charQueue*/
                    outputQueueChar[outputQueueIterator][0] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

                }

                /** There must be  a left parenthesis at the top of @operatorStack */

                /** If not, return error!*/
                if(operatorStack[opS_End - 1][0] != '('){
                    _resp.appendError("\nParentheses do not match!");
                    return _resp;

                }

                /**else, all is good, discard it and go on*/
                opS_End --;
                opertaorStackIterator --;

                /**If we have a function token at the top [basically if the first letter is not an operator or parenthesis]*/

                if(!(isOperator(operatorStack[opS_End - 1][0])) && !(isParanthesis(operatorStack[opS_End - 1][0]))){
                    /**Pop the function from the @operatorStack into the outputQueue*/

                    /**Add to @outputQueue */
                    for(int j=0; j<opStackLengths[opS_End - 1]; ++j){
                        outputQueueChar[outputQueueIterator][j] = operatorStack[opS_End - 1][j];
                    }
                    outputQueueCharLenghts[outputQueueIterator] = opStackLengths[opS_End - 1];
                    outputQueueIterator ++;
                    outQ_End++;

                    /**Pop from @opStack*/
                    opS_End --;
                    opertaorStackIterator --;
                }



        }




    }
    /** Transfer the rest of the @operatorStack into the @outputQueue */
    while(opS_Begin < opS_End){
        if(operatorStack[opS_End - 1][0] == '('){
            _resp.appendError("\nExpression is incomplete!\n    err: unclosed '('.");
            return _resp;

        }

        /**Pop the function from the @operatorStack into the outputQueue*/

        /**Add to @outputQueue */
        for(int j=0; j<opStackLengths[opS_End - 1]; ++j){
            outputQueueChar[outputQueueIterator][j] = operatorStack[opS_End - 1][j];
        }
        outputQueueCharLenghts[outputQueueIterator] = opStackLengths[opS_End - 1];
        outputQueueIterator ++;
        outQ_End++;

        /**Pop from @opStack*/
        opS_End --;
        opertaorStackIterator --;


    }

    /** The RPN array is: @outputQueueChar , with it's dual (the one containing the long double correspondents on the corresponding positions -- same as in @outputQueueChar) being @outputQueue */

    /** Rough type assignment (remember that we got rid of the parentheses!) */
    /**
        0 - NUMBER
        1 - OPERATOR
        3 - FUNCTION
        4 - PARANTHESIS
    */
    for(int it = outQ_Begin; it<outQ_End;++it){
        if(outputQueueCharLenghts[it] == 1 && isOperator(outputQueueChar[it][0])){
            /** It's an operator */
            outputQueueCharTypes[it] = 1;

        } else {
            int sw = 0;
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                if(isLetter(outputQueueChar[it][j])){
                    /** It is clearly a function*/
                    outputQueueCharTypes[it] = 3;
                    sw=1;
                    break;
                }
            }
            if(sw == 0) {
               outputQueueCharTypes[it] = 0;

            }
        }



    }


    /** Some checking :)*/
    if(trace){
        for(int it = outQ_Begin; it<outQ_End;++it){
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                printf("%c", outputQueueChar[it][j]);
            }
            printf("  ");
        }
        printf("\n\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            printf("%d", outputQueueCharTypes[it]);
            printf("  ");
        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(outputQueueCharTypes[it] == 3){
                /**It is a function*/
                int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);
                printf("%d", isSinglVar);

            } else {
                printf("nf");
            }
            printf("  ");

        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(isDigit(outputQueueChar[it][0])){
                printf("%f", outputQueue[it]);

            } else {
                printf("op ");
            }

            printf("  ");
        }
    }


    /**Done checking*/


    /**Solve RPN*/

     /**
        0 - NUMBER
        1 - OPERATOR
        NEW: 2 - FUNCTION (2 VARS - ACTS LIKE OPERATOR)
        3 - FUNCTION (SINGLE - VARRED)
        4 - PARANTHESIS
        9 - DELETED
    */

    /**Replace variable with @xis*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(outputQueueChar[it][0] == 'x' && outputQueueCharLenghts[it]==1){
            /**Treat it as number and replace it with @xis*/
            outputQueueCharTypes[it] = 0;
            outputQueue[it]= xis;

        }
    }

    /**Replace @e with @math@e*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "e", sizeof("e"))){
            /**Treat it as number and replace it with @mathe@e*/
            outputQueueCharTypes[it] = 0;
            outputQueue[it]= CONSTANT_E;

        }
    }

    /**Replace @pi with @math@pi*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(is(outputQueueChar[it], outputQueueCharLenghts[it], "pi", sizeof("pi"))){
            /**Treat it as number and replace it with @mathe@pi*/
            outputQueueCharTypes[it] = 0;
            outputQueue[it]= CONSTANT_PI;

        }
    }

    if(trace){
        for(int it = outQ_Begin; it<outQ_End;++it){
            for(int j=0;j<outputQueueCharLenghts[it];++j){
                printf("%c", outputQueueChar[it][j]);
            }
            printf("  ");
        }
        printf("\n\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            printf("%d", outputQueueCharTypes[it]);
            printf("  ");
        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(outputQueueCharTypes[it] == 3){
                /**It is a function*/
                int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);
                printf("%d", isSinglVar);

            } else {
                printf("nf");
            }
            printf("  ");

        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(isDigit(outputQueueChar[it][0])){
                printf("%f", outputQueue[it]);

            } else {
                printf("op ");
            }

            printf("  ");
        }
    }

    for(int it = outQ_Begin; it<outQ_End;++it){
        /**If it is a function*/

        if(outputQueueCharTypes[it] == 3){
            int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);

            /** If it isn't singleVarred, change the type to @2 */
            if(!isSinglVar){
               outputQueueCharTypes[it] == 2;
            }

        }

    }

    /** FROM NOW ON, THE NUMBERS WILL BE TAKEN ONLY FROM @outputQueue */

    int deleted = 0;
    int delta_deleted = 0;
    /** @outputQueueChar , @outputQueueCharTypes , @outputQueueCharLengths */

    outputQueueIterator = outQ_Begin;

    int outQ_Len = outQ_End - outQ_Begin;

    /** Array that memorises the next positions, initially, next[i]=i+1*/

    int next[outQ_End + 1], prev[outQ_End +1];
    for(int it = outQ_Begin; it< outQ_End; ++it){
        next[it] = it+1;
        prev[it] = it-1;
    }
    next[outQ_End] = 0;
    prev[outQ_End] = outQ_End - 1;



    while(outQ_Len - deleted > 1){
        delta_deleted = 0;
        for(int it = next[outQ_End]; it< outQ_End; it = next[it]){
            /** If it is operator*/
            if(outputQueueCharTypes[it] == 1){
                /** If both the previous tokes are numbers */
                /**
                    We have a config like @num @num @op. So we solve it!
                */
                if(outputQueueCharTypes[prev[prev[it]]] == 0 && outputQueueCharTypes[prev[it]] == 0 && it>=2){
                    /**Get the 2 nrs before*/
                    long double param1 = outputQueue[prev[prev[it]]];
                    long double param2 = outputQueue[ prev[it] ];


                    long double result = solveFor2V0(outputQueueChar[it][0], param1, param2);

                    /** Replace operator val at @it wit the result for @outputQueue, and also change the type to number so we know to read said val from @outputQueue, and not from @outputQueueChar*/
                    /** The separation between long doubles and chars is made to be able to save time in not performing an eventual long double to string or string to long double operation*/

                    outputQueueCharTypes[it] = 0;
                    outputQueue[it] = result;

                    /**Delete positions prev[it] and prev[prev[it]] */

                    outputQueueCharTypes[prev[it]] = 9;
                    outputQueueCharTypes[ prev[prev[it]] ] = 9;
                    if(it<2){
                        _resp.appendError("\n2-Valued operator found with one argument!");
                        return _resp;

                    }
                    next[prev[prev[prev[it]]]] = it;
                    prev[it] = prev[prev[prev[it]]];
                    deleted += 2;
                    delta_deleted += 2;
                }
            } else if(outputQueueCharTypes[it] == 3 && it>=1){ /**If the current token is a single param function*/
                /** If the token before is a number, apply the function!*/
                if( outputQueueCharTypes[prev[it]] == 0){
                    /**Get the nr before*/
                    long double param = outputQueue[ prev[it] ];

                    long double result = solveFor1VF(outputQueueChar[it], outputQueueCharLenghts[it], param);


                    /** Replace operator val at @it wit the result for @outputQueue, and also change the type to number so we know to read said val from @outputQueue, and not from @outputQueueChar*/
                    /** The separation between long doubles and chars is made to be able to save time in not performing an eventual long double to string or string to long double operation*/

                    outputQueueCharTypes[it] = 0;
                    outputQueue[it] = result;

                    /**Delete position prev[it] */

                    outputQueueCharTypes[prev[it]] = 9;
                    if(it<1){
                        _resp.appendError("\n2-Valued operator found with one argument!");
                        return _resp;

                    }
                    next[prev[prev[it]]] = it;
                    prev[it] = prev[prev[it]];
                    deleted += 1;
                    delta_deleted +=1;
                }



            }
        }
        if(trace){
            printf("\nDeleted:%d/n", deleted);
        }
        if(delta_deleted == 0){
            _resp.appendError("Something went wrong, recheck your expression!");
            return _resp;
        }

    }
    if(trace){
        printf("Left with: \n\n");
        for(int it =outQ_Begin; it<outQ_End;++it){
            printf("%f, del?: %d\n", outputQueue[it], outputQueueCharTypes[it]);
        }

        printf("\n\n");
    }

    if(trace){
        printf("Result: %f", outputQueue[outQ_End - 1]);
        printf("\n\nComplete!\n");
        printf("-------------------------------------------------------\n\n");
    }

    _resp.ldValue = outputQueue[outQ_End - 1];

    return _resp;



}

/**
 * @brief Checks if resonse has errors and throws them if yes
 * 
 * @param _resp 
 */
inline void resp_checkErrors(Response _resp){
    if(_resp.hasError()){
        throw std::invalid_argument( "Invalid Expression" );
    }
}



#endif