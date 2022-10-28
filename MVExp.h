#ifndef MV_EX_H
#define MV_EX_H

#define EXV_MAX_LEN 1000
#define EXV_MAX_FLEN 20

#include "exprev.h"
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

inline bool EXV_MESSAGES = false;
const int EXV_TYPE_NUMBER = 0, EXV_TYPE_OPERATOR = 1, EXV_TYPE_2VFUNCTION = 2, EXV_TYPE_1VFUNCTION = 3, EXV_TYPE_PARANTHESIS=4,EXV_TYPE_VARIABLE=5, EXV_TYPE_MVE = 6, EXV_TYPE_DELETED = 9;
inline bool EXV_COUT_TYPES;
const int EXV_VALENCE[6] = {
    0, 2, 2, 1, 0, 0
};
inline bool is__number(std::string s){
    if(s.at(0) == '-')
        s.pop_back();
    int cou = 0;
    for(int i=0; i<s.size();++i){
        if(s.at(i) == '.')
            cou++;
        if(!(s.at(i)>='0' && s.at(i)<='9' || s.at(i) == '.'))
            return false;
    }
    if(cou >= 2)
        return false;
    return true;
}

inline bool is_supported_func(std::string s){
    for(int i=0;i<BASIC_FUNC_NR;++i){
        if(s==MVE_BASIC_FUNC_NAMES[i])
            return true;
    }
    return false;
}
inline long double solve_for_supported1vf(std::string s, long double __x){
    for(int i=0;i<BASIC_FUNC_NR;++i){
        if(s==MVE_BASIC_FUNC_NAMES[i])
            return MVE_BASIC_FUNC_POINTERS[i](__x);
    }
    return sqrt(__x);
}
inline Response mve_getRPNQ(std::string expr, int trace, long double* out_rpnq_nrs, std::string* out_rpnq_str, int* out_rpnq_types, int& out_rlen){
    // - transfoem (-sth to (0-sth
    for(int i=0; i<expr.size() - 1; ++i){
        if(expr.at(i) == '(' && expr.at(i+1) == '-'){
            expr.insert( expr.begin() + i+1, '0' );
        }
    }
    // - std::cout<<"\n\n"<<"Updated mve: "<<expr<<"\n\n";
    /** the initial response, with result 0 [not found out yet] and 0 errors */
    Response _resp = Response(0.0, "");

    int len = expr.size();

    /** Initially [will] parsed */
    std::string parsed[MAX];
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
    std::string outputQueueChar[MAX];
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
    std::string operatorStack[MAX];
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
            parsed[index]="";
            while(isDigit(expr[i])){
                num*=10;
                num+=expr[i] - '0';
                parsed[index]+= expr[i];
                p++;
                i++;
            }

            if(expr[i] == '.'){
                parsed[index] += expr[i];
                p++;
                i++;
                long double po=1.0;
                while(isDigit(expr[i])){
                    po*=10.0;
                    num+=(expr[i] - '0')/po;

                    parsed[index] += expr[i];
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
            
            parsed[index]="";
            parsed[index] += expr[i];
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
            parsed[index]="";

            while('a' <= expr[i] && 'z'>= expr[i] || expr[i] == '_'){

                parsed[index]+= expr[i];
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
        if(!is__number(parsed[it]) && !is_supported_func(parsed[it]) && !isParanthesis(parsed[it][0]) && !isOperator(parsed[it][0])){
            type[it]=0;
        }
        if(is__number(parsed[it])){
            type[it] = 0;
        }
        if(isOperator(parsed[it][0]))
            type[it] = 1;
        
    }
    if(trace){
        printf("\n\n\nTS:\n");

        for(int it = 0;  it<tokensNumber;++it){
            std::cout<<parsed[it]<<":"<<type[it]<<"  ";
        }
        printf("\n\n\n");
    }
    
    /** Every pi --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(parsed[it]=="pi"){
            type[it] = 0;
        }
    }

    /** Every e --> @num @0*/
    for(int it=0;it<tokensNumber;++it){
        if(parsed[it]=="e"){
            type[it] = 0;
        }


    }
    if(trace){
        printf("\n\nNVS:\n");
        for(int it=0;it<tokensNumber;++it){
            std::cout<<numberValue[it]<<":nr  ";


        }
        printf("\n");

    }
    


    for(int i=0;i<tokensNumber;++i){
        if(type[i] == 0){
            /**Token @i Is Number, so add it to @outputQueue */
            outputQueue[outputQueueIterator] = numberValue[i];
            outputQueueChar[outputQueueIterator]= parsed[i];
            
            outputQueueCharLenghts[outputQueueIterator] = lengths[i];
            outputQueueIterator++;
            outQ_End++;
        } else if(type[i] == 3){
            /**Token @i Is a function, so add it to @operatorStack */
            operatorStack[opertaorStackIterator] = parsed[i];
            
            opStackLengths[opertaorStackIterator] = lengths[i];
            opS_End++;
            opertaorStackIterator++;

        } else if(type[i] == 1){

            /**Token is an operator*/
            char o1 = parsed[i][0];
            std::string oo1 = parsed[i];
            //std::cout<<"b"<<operatorStack[opS_End - 1];

            while(opS_End > 0 &&operatorStack[opS_End - 1] != "(" && isOperator(operatorStack[opS_End - 1][0]) && ( precedence[(int)o1] < precedence[(int)operatorStack[opS_End - 1][0]] ||
                                                             (precedence[(int)o1] == precedence[(int)operatorStack[opS_End - 1][0]]) )){
                /**there is an operator o2 other than the left parenthesis at the top
                of the operator stack, and (o2 has greater precedence than o1
                or they have the same precedence and o1 is  [NOT IMPLEMENTED YET] left-associative)*/
                    //std::cout<<"a";
                    std::string o2 = operatorStack[opS_End - 1];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to @outputQueue */
                    outputQueueChar[outputQueueIterator] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

            }
            //std::cout<<"c";
            /**Push o1 to @operatorStack */
            operatorStack[opertaorStackIterator] = oo1;
            opStackLengths[opertaorStackIterator] = 1;
            opertaorStackIterator ++;
            opS_End++;

        } else if(type[i] == 4 && parsed[i] == "("){
                /**Push ( to @opertaorStack */
                operatorStack[opertaorStackIterator] = parsed[i];
                opStackLengths[opertaorStackIterator] = 1;
                opertaorStackIterator ++;
                opS_End ++;
        } else if(type[i] == 4 && parsed[i] == ")"){
                while(opS_End > 0 && operatorStack[opS_End - 1] != "("){
                    if(opS_End <= opS_Begin){
                            /**Expression is incomplete*/
                            _resp.appendError("\nExpression is incomplete!");//at i
                                        return _resp;

                    }

                    std::string o2 = operatorStack[opS_End - 1];

                    /**Pop o2*/
                    opS_End --;
                    opertaorStackIterator --;

                    /**Add o2 to charQueue*/
                    outputQueueChar[outputQueueIterator] = o2;
                    outputQueueCharLenghts[outputQueueIterator] = 1;
                    outputQueueIterator ++;
                    outQ_End++;

                }

                /** There must be  a left parenthesis at the top of @operatorStack */

                /** If not, return error!*/
                if(opS_End > 0 && operatorStack[opS_End - 1][0] != '('){
                    _resp.appendError("\nParentheses do not match!");
                    return _resp;

                }

                /**else, all is good, discard it and go on*/
                opS_End --;
                opertaorStackIterator --;

                /**If we have a function token at the top [basically if the first letter is not an operator or parenthesis]*/

                if(opS_End > 0 &&!(isOperator(operatorStack[opS_End - 1][0])) && !(isParanthesis(operatorStack[opS_End - 1][0]))){
                    /**Pop the function from the @operatorStack into the outputQueue*/

                    /**Add to @outputQueue */
                    outputQueueChar[outputQueueIterator] = operatorStack[opS_End - 1];
                    
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
        if(opS_End > 0 &&operatorStack[opS_End - 1][0] == '('){
            _resp.appendError("\nExpression is incomplete!\n    err: unclosed '('.");
            return _resp;

        }

        /**Pop the function from the @operatorStack into the outputQueue*/

        /**Add to @outputQueue */
        outputQueueChar[outputQueueIterator] = operatorStack[opS_End - 1];
        
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
        
            int sw = 0;
            if(is_supported_func(outputQueueChar[it])){
               outputQueueCharTypes[it] = 3;

            } else if(is__number(outputQueueChar[it])){
                outputQueueCharTypes[it]= 0;
            }
        
            if(isOperator(outputQueueChar[it][0])){
                /** It's an operator */
                outputQueueCharTypes[it] = 1;

            }


    }


    /** Some checking :)*/
    if(trace){
        for(int it = outQ_Begin; it<outQ_End;++it){
            std::cout<<outputQueueChar[it];
            
            printf("  ");
        }
        printf("DDDDDDDDDOOOOOOOOOOOONE\n\n");
        for(int it = outQ_Begin; it<outQ_End;++it){
            printf("%d", outputQueueCharTypes[it]);
            printf("  ");
        }
        printf("\n\n");

        for(int it = outQ_Begin; it<outQ_End;++it){
            if(outputQueueCharTypes[it] == 3){
                /**It is a function*/
                int isSinglVar = is_supported_func(outputQueueChar[it]);
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
        if(!is__number(outputQueueChar[it]) && !is_supported_func(outputQueueChar[it]) && !isParanthesis(outputQueueChar[it][0])  && !isOperator(outputQueueChar[it][0])){
            // is variable
            outputQueueCharTypes[it] = 0;
                //HAHAHA
            outputQueueIsVar[it] = 5;
            outputQueueVars[it] = outputQueueChar[it];
            scw = 1;
        }
        if(scw==0){
            outputQueueIsVar[it] = 0;
            
        }
        
    }


    /**Replace @e with @math@e*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(outputQueueChar[it] == "e"){
            /**Treat it as number and replace it with @mathe@e*/
            outputQueueCharTypes[it] = 5;
            //outputQueue[it]= CONSTANT_E;

        }
    }

    /**Replace @pi with @math@pi*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(outputQueueChar[it] == "pi"){
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
                //int isSinglVar = isSingleVariabled(outputQueueChar[it], outputQueueCharLenghts[it]);
                //printf("%d", isSinglVar);

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
            int isSinglVar = is_supported_func(outputQueueChar[it]);

            /** If it isn't singleVarred, change the type to @2 */
            if(!isSinglVar){
               outputQueueCharTypes[it] = 2;
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
        if(outputQueueChar[it] == "e"){
            /**Treat it as number and replace it with @mathe@e*/
            out_rpnq_types[it] = 5;
            out_rpnq_str[it] = outputQueueChar[it];

        }
    }

    /**Replace @pi with @math@pi*/
    for(int it = outQ_Begin; it<outQ_End;++it){
        /**IF Variable is found*/
        if(outputQueueChar[it] == "pi"){
            /**Treat it as number and replace it with @mathe@pi*/
            out_rpnq_types[it] = 5;
            out_rpnq_str[it] = outputQueueChar[it];

            //outputQueue[it]= CONSTANT_PI;

        }
    }
    out_rlen = outQ_End;



}



class MVExp{
    public:
        std::string rstr[EXV_MAX_LEN];
        int rtypes[EXV_MAX_LEN];
        long double rlds[EXV_MAX_LEN];
        int rlen;
    
        MVExp(char* expression, int len, int var_nr, char** var_names);
        MVExp(std::string expression, int var_nr, std::string* var_names);
        MVExp();
        MVExp(std::string expression);
        bool isvalid();
        int stacktrace();
        bool canstrip();
        void split_terms(MVExp& out1, MVExp& out2, std::string& out_op);
        void strip(MVExp& out_exp, std::string& out_funcname);
        MVExp subexp(int begin, int length);


        static MVExp solve(std::string OP, const MVExp lhs, const MVExp rhs);

        friend MVExp operator +(const MVExp lhs, const MVExp rhs);
        friend MVExp operator -(const MVExp lhs, const MVExp rhs);
        friend MVExp operator *(const MVExp lhs, const MVExp rhs);
        friend MVExp operator /(const MVExp lhs, const MVExp rhs);
        
        friend MVExp operator ^(const MVExp lhs, const MVExp rhs);
        

        friend std::ostream& operator <<(std::ostream& os, MVExp expression);

};

 /**
    0 - NUMBER
    1 - OPERATOR
    NEW: 2 - FUNCTION (2 VARS - ACTS LIKE OPERATOR)
    3 - FUNCTION (SINGLE - VARRED)
    4 - PARANTHESIS
    5 - VARIABLE
    9 - DELETED
*/
#endif