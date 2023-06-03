#ifndef BN_COMPLEX_H
#define BN_COMPLEX_H

#include "BNdecimal.h"
class BNcomplex{
    public:
        BNdecimal real_part;
        BNdecimal imaginary_part;
        /**
         * @brief Default is -1
         * 
         */
        BNdecimal square_i;
        BNcomplex(BNdecimal real_);
        BNcomplex(BNdecimal real_, BNdecimal imag_);
        BNcomplex(BNdecimal real_, BNdecimal imag_, BNdecimal sq_i);
        BNcomplex conj();
        BNdecimal square_norm();
        BNcomplex inverse();
        friend BNcomplex operator +(const BNcomplex lhs, const BNcomplex rhs);
        friend BNcomplex operator -(const BNcomplex lhs, const BNcomplex rhs);
        friend BNcomplex operator *(const BNcomplex lhs, const BNcomplex rhs);
        friend BNcomplex operator /(const BNcomplex lhs, const BNcomplex rhs);
        
        friend std::ostream& operator <<(std::ostream& os, BNcomplex nr);
        friend std::istream& operator >>(std::istream& os, BNcomplex& nr);
};

#endif