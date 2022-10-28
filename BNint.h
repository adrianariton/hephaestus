#ifndef BN_INT_H
#define BN_INT_H

#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>



class BNint {
    public: 
        std::string cvalue;
        BNint(std::string str);
        BNint();

        friend BNint operator +(const BNint lhs, const BNint rhs);
        friend BNint operator -(const BNint lhs, const BNint rhs);
        friend BNint operator *(const BNint lhs, const BNint rhs);
        friend BNint operator /(const BNint lhs, const BNint rhs);

        friend BNint &operator/=(BNint &, BNint &);

        bool operator <(BNint rhs);
        bool operator >(BNint rhs);
        bool operator >=(BNint rhs);
        bool operator <=(BNint rhs);
        bool operator ==(BNint rhs);


        friend std::ostream& operator <<(std::ostream& os, BNint& nr);
        friend std::istream& operator >>(std::istream& os, BNint& nr);

};
//2.7182818284590452353602874713527
#endif