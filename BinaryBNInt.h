#ifndef BINARY_BN_INT
#define BINARY_BN_INT

#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

class BinaryBNint{
    public:
        std::string bits;
        bool isNegative;
        BinaryBNint(std::string str);
        BinaryBNint();

        friend BinaryBNint operator +(const BinaryBNint lhs, const BinaryBNint rhs);
        friend BinaryBNint operator -(const BinaryBNint lhs, const BinaryBNint rhs);
        
        friend bool operator >(const BinaryBNint lhs, const BinaryBNint rhs);
        friend bool operator <(const BinaryBNint lhs, const BinaryBNint rhs);
        friend bool operator >=(const BinaryBNint lhs, const BinaryBNint rhs);
        friend bool operator <=(const BinaryBNint lhs, const BinaryBNint rhs);
        

        static BinaryBNint addPositives(const BinaryBNint lhs, const BinaryBNint rhs);
        static BinaryBNint subsPositives(const BinaryBNint lhs, const BinaryBNint rhs);

        /**Multiply (Shift left)*/
        friend BinaryBNint operator <<(const BinaryBNint lhs, int shift);

        /**COUT*/
        friend std::ostream& operator <<(std::ostream& os, BinaryBNint nr);
        /**Shift Right (divide)*/
        friend BinaryBNint operator >>(const BinaryBNint lhs, int shift);

};




#endif