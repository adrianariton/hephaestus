#ifndef BN_DECIMAL_H
#define BN_DECIMAL_H

#include "BNint.h"

/**
 * @brief All BN_DEC_[precisions] are used in the brute:: namespace for limiting the size of the after-decimal-point-digits
 * 
 *
 * 
 */

/**
 * All BN_DEC_[precisions] are used for limiting the size of the after-decimal-point-digits.
 * Type: Rounding factor -> division (in all namespaces)
 * 
*/
inline int BN_DEC_PRECISION = 1300;

/**
 * All BN_DEC_[precisions] are used for limiting the size of the after-decimal-point-digits.
 * Type: Rounding factor -> sqrt (only in brute::)
*/
inline int BN_DEC_SQRTPRECISION = 100;

/**
 * All BN_DEC_[precisions] are used for limiting the size of the after-decimal-point-digits.
 * Type: Rounding factor -> trig functions (only in brute::)
*/
inline int BN_DEC_TRIGPRECISION = 100;

/**
 * All BN_DEC_[precisions] are used for limiting the size of the after-decimal-point-digits.
 * Type: Rounding factor -> exp for positive nrs (only in brute::)
*/
inline int BN_DEC_EXPPRECISION = 1000;

/**
 * Less precision required because the results are closer together
 * Might fail if raised above 300-400 with std::out_of_range error
 * because of string size limitatons [probably] (only in brute::)
*/
inline int BN_DEC_INVEXPPRECISION = 100;

/**
 * All BN_DEC_[precisions] are used for limiting the size of the after-decimal-point-digits.
 * Type: Rounding factor -> ln  (only in brute:: and when the inverse of the exp is required TODO: change the way of functioning of this algo soo that 1/e is stored)
*/
inline int BN_DEC_LNPRECISION = 1000;

/**
 * @brief Write messages regarding the progress of mre time-consuming operations
 * 
 */
inline bool BN_MESSAGES = false;

/**
 * @brief Max decimal digits written by cout. Default is 100
 * 
 */
inline int BN_COUT_SETPREC = 100;

/**
 * @brief If the exp precision should be doubled when calculating. Default: true, for better precision
 *  (only in brute::)
 */
inline bool DOUBLE_THE_FUN = true;

/**
 * @brief Do not use the functions (non static ones) in this class if you want floating point precision. Use the ones in the big_cordic:: namespace instead
 * 
 */
class BNdecimal{
    public:
    
        /*dec = iP * 10^(-decPoint)*/
        BNint integerPart;
        /*Counted from the end*/
        int decimalPoint;
        bool isNegative;

        BNdecimal(std::string str);
        BNdecimal();
        BNdecimal(int a);
        friend BNdecimal operator +(const BNdecimal lhs,const BNdecimal rhs);
        friend BNdecimal operator -(const BNdecimal lhs,const BNdecimal rhs);
        friend BNdecimal operator *(const BNdecimal lhs,const BNdecimal rhs);
        friend BNdecimal operator /(const BNdecimal lhs,const BNdecimal rhs);

        BNdecimal ainverse(BNdecimal n);
        BNdecimal sqrt();
        BNdecimal abs();

        static BNdecimal get_pi(BNdecimal precision);
        static void clean(BNdecimal &__x);

        BNdecimal exp();
        BNdecimal m_exp(BNdecimal precision);
        BNdecimal big_exp(BNdecimal chunk, BNdecimal m_exp_precision);

        BNdecimal sin();
        BNdecimal m_sin(BNdecimal precision);
        BNdecimal big_sin(BNdecimal m_sin_precision);

        BNdecimal cos();
        BNdecimal m_cos(BNdecimal precision);
        BNdecimal big_cos(BNdecimal m_cos_precision);

        BNdecimal ln(BNdecimal precision);
        BNdecimal big_ln(BNdecimal precision);

        BNdecimal arctan_e();
        BNdecimal arctan_p7();

        BNdecimal big_raise_to(BNdecimal exponent, BNdecimal lnprec, BNdecimal exprec, BNdecimal exchunk);
        BNdecimal big_raise_to_natural(BNdecimal exponent);
        BNdecimal floor();

        BNdecimal roundToDecimal(int decimal);

        friend bool operator < (BNdecimal lhs, BNdecimal rhs);
        friend bool operator > (BNdecimal lhs, BNdecimal rhs);
        friend bool operator >=(BNdecimal lhs, BNdecimal rhs);
        friend bool operator <=(BNdecimal lhs, BNdecimal rhs);
        friend bool operator ==(BNdecimal lhs, BNdecimal rhs);

        std::string to_string();

        friend std::ostream& operator <<(std::ostream& os, BNdecimal nr);
        friend std::istream& operator >>(std::istream& os, BNdecimal& nr);
};

#endif


