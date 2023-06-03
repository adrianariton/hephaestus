#include "BNdecimal.h"

/**
 * @brief Construct a new BNdecimal::BNdecimal object
 * 
 * @param str Example: "-1002001.2245642" or "1021.102676919919919" or "21"
 */
BNdecimal::BNdecimal(std::string str){
    decimalPoint = 0;
    if(str.at(0) == '-'){
        isNegative = true;
        str.erase(0, 1);
    } else {
        isNegative = false;
    }

    std::size_t foundDecPoint = str.find('.');
    int pos = str.find('.');
    if(pos != str.size() && pos!=-1){
        decimalPoint = str.size() - 1 - pos;
        str.erase(pos, 1);
    } else {
        decimalPoint = 0;
    }

    
    integerPart = BNint(str);

}


BNdecimal::BNdecimal(int a){
    *this = BNdecimal(std::to_string(a));
}

/**
 * 
 * @brief Construct a new BNdecimal::BNdecimal object 
 * 
 * Initial value is set to 0 
 */
BNdecimal::BNdecimal(){
    integerPart = BNint();
    isNegative = false;
    decimalPoint = 0;
}

BNdecimal operator *(const BNdecimal lhs,const BNdecimal rhs){
    BNdecimal result;

    result.integerPart = lhs.integerPart * rhs.integerPart;
    result.decimalPoint = lhs.decimalPoint + rhs.decimalPoint;
    if(rhs.isNegative && lhs.isNegative){
        result.isNegative = false;
    } else if(!rhs.isNegative && !lhs.isNegative){
        result.isNegative = false;
    } else {
        result.isNegative = true;
    }
    return result;
}


BNdecimal operator +(const BNdecimal lhs,const BNdecimal rhs){
    BNdecimal result;
    int maxdecdigits, mindecdigits;
    BNdecimal n_maxdec, n_mindec;

    if(lhs.decimalPoint > rhs.decimalPoint){
        n_maxdec = lhs;
        n_mindec = rhs;
    } else {
        n_maxdec = rhs;
        n_mindec = lhs;
    }

    for(int i=0;i< (n_maxdec.decimalPoint - n_mindec.decimalPoint); ++i){
        n_mindec.integerPart.cvalue+='0';
    }


    result.decimalPoint = n_maxdec.decimalPoint;
    if(!n_maxdec.isNegative && !n_mindec.isNegative){
        result.integerPart = n_maxdec.integerPart + n_mindec.integerPart;
        result.isNegative = false;
    } else if(n_maxdec.isNegative && n_mindec.isNegative){
        result.integerPart = n_maxdec.integerPart + n_mindec.integerPart;
        result.isNegative = true;
    } else if(!n_maxdec.isNegative && n_mindec.isNegative){
        if(n_maxdec.integerPart > n_mindec.integerPart){
            result.integerPart = n_maxdec.integerPart - n_mindec.integerPart;
            result.isNegative = false;
        } else {
            result.integerPart = n_mindec.integerPart - n_maxdec.integerPart;
            result.isNegative = true;
        }
    } else if(n_maxdec.isNegative && !n_mindec.isNegative){
        if(n_mindec.integerPart > n_maxdec.integerPart){
            result.integerPart = n_mindec.integerPart - n_maxdec.integerPart;
            result.isNegative = false;
        } else {
            result.integerPart = n_maxdec.integerPart - n_mindec.integerPart;
            result.isNegative = true;
        }
    } 

    return result;

    
}

bool operator>(const BNdecimal lhs,const BNdecimal rhs){
    return !(lhs - rhs).isNegative;
}

bool operator<(const BNdecimal lhs,const BNdecimal rhs){
    return (lhs - rhs).isNegative;
}
bool operator==(const BNdecimal lhs,const BNdecimal rhs){
    BNdecimal _lhs = lhs, _rhs = rhs;
    BNdecimal::clean(_lhs);
    BNdecimal::clean(_rhs);

    return _lhs.integerPart.cvalue == _rhs.integerPart.cvalue && _lhs.decimalPoint == _rhs.decimalPoint && _lhs.isNegative == _rhs.isNegative;
}

void BNdecimal::clean(BNdecimal &__x){
    std::string _s = __x.integerPart.cvalue;
    int _d = __x.decimalPoint;
    int _sg = __x.isNegative;
    int it = 0, _b = _s.size() - 1;
    while(it <_d && _b >= 0 && _s.at(_b) == '0'){
        _b --;
        it++;
        _s.pop_back();
    }
    if(_s == ""){
        __x =  BNdecimal("0");
        return;
    }
    _d -= it;
    it = 0;
    _b = _s.size() - 1 - _d;
    while(_s.at(0) == '0' && _b >= 0 && it < _b){
        _s.erase(_s.begin());
        it++;
    }
    BNdecimal _q(_s);
    _q.decimalPoint = _d;
    _q.isNegative = _sg;
    __x = _q;

}
/**
 * @brief Don't use this
 * @deprecated Don't use this
 * 
 * @param n Just don't use this
 * @return Just close the info box and don't use this.
 */
BNdecimal BNdecimal::ainverse(BNdecimal n){
    n.isNegative = !n.isNegative;
    return n;
}

BNdecimal operator -(const BNdecimal lhs,const BNdecimal rhs){
    BNdecimal mrhs = rhs;
    mrhs.isNegative = !mrhs.isNegative;
    BNdecimal result = lhs + mrhs;
    return result;
}


BNdecimal operator /(const BNdecimal dlhs,const BNdecimal rhs){
    if(dlhs == BNdecimal("0"))
        return BNdecimal("0");
    BNdecimal lhs = dlhs;
    lhs.isNegative = dlhs.isNegative;
    for(int i=dlhs.decimalPoint; i<BN_DEC_PRECISION;++i){
        lhs.integerPart.cvalue+="0";
        lhs.decimalPoint++;
    }

    BNdecimal result;
    result.integerPart = (lhs.integerPart / rhs.integerPart);
    result.decimalPoint = lhs.decimalPoint - rhs.decimalPoint;
    result.isNegative = (rhs.isNegative ^ lhs.isNegative);
    if(rhs.isNegative && lhs.isNegative){
        result.isNegative = false;
    } else if(!rhs.isNegative && !lhs.isNegative){
        result.isNegative = false;
    } else {
        result.isNegative = true;
    }

    int it = result.integerPart.cvalue.size()-1, cou = 0;
    while (result.integerPart.cvalue.at(it) == '0' && cou < lhs.decimalPoint-1)
    {
        cou++;
        result.integerPart.cvalue.pop_back();
        it = result.integerPart.cvalue.size()-1;
        result.decimalPoint--;
    }
    
    return result;
    
}
/**
 * @brief Rounding function
 * 
 * @param decimal Decimal to be rounded to 
 * @return BNdecimal 
 */
BNdecimal BNdecimal::roundToDecimal(int decimal){
    BNdecimal hs = *this;
    for(int i=decimalPoint; i>decimal && hs.integerPart.cvalue.size() > 0;--i){
        hs.integerPart.cvalue.pop_back();
        hs.decimalPoint--;
    }
    if(hs.integerPart.cvalue.size() == 0){
        return BNdecimal("0");
    }
    
    return hs;
}
/**
 * @brief Square root.
 * 
 * @return BNdecimal 
 */
BNdecimal BNdecimal::sqrt(){
    BNdecimal left("1"), right = *this, a=*this, v("1"), mid, prod;
    int k = 0;
    if(right.decimalPoint %2 == 1){
        a = a*BNdecimal("10");
        right = right*BNdecimal("10");
        k+=2;
    }
     int d_p = right.decimalPoint;
     int mul = 0;
     for(int i=d_p+1; i<= 2*BN_DEC_SQRTPRECISION; ++i){
         if(a.decimalPoint >0){
             a.decimalPoint --;
         } else {
             a.integerPart.cvalue+='0';
         }
         mul++;

     }
    right = a;
    right.integerPart = right.integerPart/BNint("2");
    while(left.integerPart <= right.integerPart){
        mid.integerPart = mid.integerPart+left.integerPart;
        mid.integerPart = mid.integerPart+right.integerPart;
        mid.integerPart = mid.integerPart/BNint("2");
        prod.integerPart = (mid.integerPart * mid.integerPart);
        if(prod.integerPart <= a.integerPart){
            v.integerPart = mid.integerPart;
            mid.integerPart = mid.integerPart + BNint("1");
            left.integerPart = mid.integerPart;
        }
        else{
            mid.integerPart = mid.integerPart - BNint("1");
            right.integerPart = mid.integerPart;
        }
        mid.integerPart = BNint("0");
    }
    v.decimalPoint = (a.decimalPoint + k)/2 + mul/2;
    v.isNegative = false;
    return v;
     
}


/**
 * @brief Exponential: returns e^[number] for small numbers [2-100]. Use big_exp instead.
 * @param precision INTEGER. Number of iterations for the minmax poly.
 * @deprecated Use big_exp instead.
 * @return BNdecimal 
 */
BNdecimal BNdecimal::m_exp(BNdecimal precision){
    BNdecimal sum("1");
    BNdecimal x = *this;
    BNdecimal ii = precision;
    BNdecimal one("1");
    ii = ii-one;

    while((ii - BNdecimal("0.5")).isNegative == false){
        sum = ((x*sum)/ii)+one;
        ii = ii-one;
    }
    return sum;
}

/**
 * @brief Exp function. Use big_exp instead
 * @deprecated Works for small numbers only
 * 
 * @return BNdecimal 
 */
BNdecimal BNdecimal::exp(){
    return m_exp(BNdecimal("169"));
}

/**
 * @brief Exponential: returns e^[number]
 * @details This function is an optimised m_exp function calculated by breaking the expnent into smaller chunks that are then re-multiplied.
 * @param chunk INTEGER. The lower, the better accuracy but also slower time. Needs to be higher than 1. Recommended value: 2 - 10.
 * @param m_exp_precision INTEGER. number of iterations for the minmax poly. The higher - the better accuracy. Recommended value: 400 - 170.
 * 
 * @return BNdecimal 
 */
BNdecimal BNdecimal::big_exp(BNdecimal chunk,  BNdecimal m_exp_precision){
    BNdecimal sum("1");
    BNdecimal x = *this;
    BNdecimal half("0.5");
    BNdecimal m = chunk;
    BNdecimal a = x;
    int p = 0;
    if((a.abs()+a.abs() == a.abs())){
        return BNdecimal("1");
    }
    if(!a.isNegative){
        while( !((a - m).isNegative)) {
            a = a * half;
            a = a.roundToDecimal(BN_DEC_EXPPRECISION);
            p++;;
        }
        BNdecimal ex = a.m_exp(m_exp_precision);

        while(p > 0){
            p--;
            ex = ex.roundToDecimal(BN_DEC_EXPPRECISION);
            ex = ex * ex;

            if(BN_MESSAGES)
                std::cout<<p<<" size:>"<<ex.integerPart.cvalue.size() <<"  ex:"<<ex<<"\n";
        }

        return ex;
    } else return BNdecimal("1")/(a.abs().big_exp(chunk, m_exp_precision).roundToDecimal(BN_DEC_INVEXPPRECISION));
    
}



/**
 * @brief Sine function for not-so-big numbers.
 * @brief It is best to use big_sin [it works for all numbers and all ranges]
 * 
 * @param precision INTEGER. Number of iterations for the minmax polynomial (the higher, the better) - recommended: 50
 * @return BNdecimal 
 * @deprecated Use big_sin instead.
 */
BNdecimal BNdecimal::m_sin(BNdecimal precision){
    BNdecimal sum("1");
    BNdecimal x = *this, zero  = BNdecimal("0");
    BNdecimal ii = precision;
    BNdecimal one("1"), four("4"), two("2");
    BNdecimal p0 = four * ii;
    BNdecimal p1 = four * ii + BNdecimal("1");
    BNdecimal p2 = four * ii + BNdecimal("2");
    BNdecimal p3 = four * ii + BNdecimal("3");
    int parity = 0;
    while((p2 - BNdecimal("0.5")).isNegative == false){
        BNdecimal aa = (((x*x*sum)/(p2 * p3)));
        aa.isNegative = !aa.isNegative;
        sum = aa+one;
        p1 = p1 - two;
        p3 = p3 - two;
        p2 = p2 - two;
        p0 = p0 - two;

        sum = sum.roundToDecimal(BN_DEC_TRIGPRECISION);
    }
    return (sum*x).roundToDecimal(BN_DEC_TRIGPRECISION);
}
/**
 * @brief Use big_sin instead
 * @deprecated Works only for small numbers
 * @return BNdecimal 
 */
BNdecimal BNdecimal::sin(){
    return m_sin(BNdecimal("50"));
}

/**
 * @brief Sine function
 * 
 * @param m_sin_precision INTEGER. Number of iterations for the minmax polynomial (the higher, the better) - recommended: 50
 * @return BNdecimal 
 */
BNdecimal BNdecimal::big_sin(BNdecimal m_sin_precision){
    BNdecimal sum("1");
    BNdecimal x = *this;
    BNdecimal half("0.5"), two("2");
    BNdecimal a = x;
    BNdecimal pi("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145");
    
    BNdecimal __c = half * x / pi;
    __c = __c.floor();
    
    BNdecimal rem = x - (two * pi * __c);
    BNdecimal::clean(rem);
    return rem.m_sin(m_sin_precision);
}





/**
 * @brief Cosine function for not-so-big numbers.
 * @brief It is best to use big_cos [it works for all numbers and all ranges]
 * 
 * @param precision INTEGER. Number of iterations for the minmax polynomial (the higher, the better) - recommended: 50
 * @return BNdecimal 
 * @deprecated Use big_cos instead.
 */
BNdecimal BNdecimal::m_cos(BNdecimal precision){
    BNdecimal sum("1");
    BNdecimal x = *this, zero  = BNdecimal("0");
    BNdecimal ii = precision;
    BNdecimal one("1"), four("4"), two("2");
    BNdecimal p0 = four * ii;
    BNdecimal p1 = four * ii + BNdecimal("1");
    BNdecimal p2 = four * ii + BNdecimal("2");
    BNdecimal p3 = four * ii + BNdecimal("3");
    int parity = 0;
    while((p2 - BNdecimal("0.5")).isNegative == false){
        BNdecimal aa = (((x*x*sum)/(p2 * p1)));
        aa.isNegative = !aa.isNegative;
        sum = aa+one;
        p1 = p1 - two;
        p3 = p3 - two;
        p2 = p2 - two;
        p0 = p0 - two;

        sum = sum.roundToDecimal(BN_DEC_TRIGPRECISION);
    }
    return sum;
}
/**
 * @brief Use big_cos instead
 * @deprecated Works only for small numbers
 * @return BNdecimal 
 */
BNdecimal BNdecimal::cos(){
    return m_sin(BNdecimal("50"));
}

/**
 * @brief Cosine function
 * 
 * @param m_cos_precision INTEGER. Number of iterations for the minmax polynomial (the higher, the better) - recommended: 50
 * @return BNdecimal 
 */
BNdecimal BNdecimal::big_cos(BNdecimal m_cos_precision){
    BNdecimal sum("1");
    BNdecimal x = *this;
    BNdecimal half("0.5"), two("2");
    BNdecimal a = x;
    BNdecimal pi("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145");
    
    BNdecimal __c = half * x / pi;
    __c = __c.floor();
    
    BNdecimal rem = x - (two * pi * __c);
    BNdecimal::clean(rem);
    return rem.m_cos(m_cos_precision);
}


/**
 * @brief Floor function
 * 
 * @return BNdecimal 
 */
BNdecimal BNdecimal::floor(){
    BNdecimal __x = *this, _c = __x;
    BNdecimal::clean(__x);
    BNdecimal::clean(_c);
    if(__x.integerPart.cvalue.size() < __x.decimalPoint)
        return  BNdecimal("0");
    std::string __s = __x.integerPart.cvalue;
    __x.integerPart.cvalue = __s.substr(0, __s.size()-__x.decimalPoint);
    __x.decimalPoint = 0;
    if(__x.isNegative && !(_c == __x)){
        __x = __x - BNdecimal("1");
    }
    return __x;
    
}
/**
 * @brief Returns the absolute value of a number
 * 
 * @return BNdecimal 
 */
BNdecimal BNdecimal::abs(){
    BNdecimal __x = *this;
    __x.isNegative = false;
    return __x;
}
/**
 * @brief Returns the natural logarithm of a number. Works for all nrs.
 * 
 * @param precision INTEGER. The number of iterations for the minmax poly. Recommended: 50
 * @return BNdecimal 
 */
BNdecimal BNdecimal::ln(BNdecimal precision){
    BNdecimal ln10("2.3025850929940456840179914546843642076011014886287729760333279009675726096773524802359972050895982983419677840422862486334095254650828067566662873690987816894829072083255546808437998948262331985283935053089653777326288461633662222876982198867465436674744042");

    BNdecimal __x = *this, one = BNdecimal("1");
     
    __x = __x.abs();
    int a = 0, _a =0;

    BNdecimal c("0");
    if((__x - BNdecimal("10")).isNegative == false){
        while((__x - BNdecimal("10")).isNegative == false){
            __x = __x / BNdecimal("10");
                        c = c + one;

        }
    } else if((__x - BNdecimal("1")).isNegative == true){
        while((__x - BNdecimal("1")).isNegative == true){
            __x = __x * BNdecimal("10");
            a--;
            c = c - one;
        }
    }
    int _bp = _a + a;
    BNdecimal y = (__x - one) / (__x + one);

    BNdecimal Spp2("0");
    BNdecimal f("1"), pwy = y, y2 = y*y;
    BNdecimal _p = precision * BNdecimal("2");
    for(f; (f - _p).isNegative == true; f = f + BNdecimal("2")){
        Spp2 = Spp2 + pwy / f;
        pwy = pwy * y2;
        pwy = pwy.roundToDecimal(BN_DEC_LNPRECISION);
        Spp2 = Spp2.roundToDecimal(BN_DEC_LNPRECISION);
    }
    Spp2 = Spp2 * BNdecimal("2"); 
    return Spp2 + c * ln10;
}
/**
 * @brief Same as ln.
 * 
 * @param precision Same as ln.
 * @return BNdecimal 
 */
BNdecimal BNdecimal::big_ln(BNdecimal precision){
    return (*this).ln(precision);
}

/**
 * @brief Gets pi through a fast converging iterative method. It is quite slow to compute, so it's unreasonable to use it in calculations.
 * 
 * @param precision INTEGER. Number of iterations.
 * @return BNdecimal 
 */
BNdecimal BNdecimal::get_pi(BNdecimal precision){
    BNdecimal a("1"), aa("0"), b("0"), one("1"), two("2"), four("4"), five("5"), six("6"), eight("8"), sixteen("16");
    BNdecimal pi("0");
    int a_ = 0;
    while((aa-precision+BNdecimal("0.5")).isNegative == true){
        pi = pi + (a * (four/(b + one) - two/(b+four) - one/(b + five) -one/(b + six) ));
        a = a/sixteen;
        b = b+ eight;
        aa = aa + one;
    }
    return pi;
}

/**
 * @brief Returns the base rissen to a real exponent. The base must be positive!
 * 
 * @param exponent The exponent to raise to
 * @param lnprec INTEGER. Number of iterations to run the ln function. Recommended: 50
 * @param exprec INTEGER. Number of iterations to run the big_exp function
 * @param exchunk INTEGER. Chunks to be used in the big_exp function [see big_exp for refference]
 * @return BNdecimal 
 */
BNdecimal BNdecimal::big_raise_to(BNdecimal exponent, BNdecimal lnprec, BNdecimal exprec, BNdecimal exchunk){
    BNdecimal __x = *this;
    if(__x.isNegative){
        throw std::invalid_argument("Negative number cannot be raised to an exponent");
    }
    BNdecimal _r = __x.ln(lnprec).roundToDecimal(BN_DEC_INVEXPPRECISION) * exponent;
    if(BN_MESSAGES)
        std::cout<<_r<<" <-r\n";
    return _r.big_exp(exchunk, exprec);
}
/**
 * @brief Raises a number to a natural power. Works faster than big_raise_to because of this restriciton
 * 
 * @param exponent The exponent to raise to
 * @return BNdecimal 
 */
BNdecimal BNdecimal::big_raise_to_natural(BNdecimal exponent){
    exponent = exponent.floor();
    BNdecimal::clean(exponent);
    std::string _s = exponent.integerPart.cvalue;
    char lastdigit = _s.at(_s.size()-1);
    int _v = lastdigit - '0';
    BNdecimal _ex = exponent, _b = *this, two = BNdecimal("2"), one = BNdecimal("1");
    BNdecimal half = (_ex / two).floor();
    if(_ex == BNdecimal("0")) return BNdecimal("1");
    if(_ex == BNdecimal("1")) return _b;

    if(_v %2 == 0){
        return (_b.big_raise_to_natural(half) * _b.big_raise_to_natural(half)).roundToDecimal(BN_DEC_EXPPRECISION);
    } else {
        return (_b.big_raise_to_natural(half) * _b.big_raise_to_natural(half) * _b).roundToDecimal(BN_DEC_EXPPRECISION);

    }

}


BNdecimal BNdecimal::arctan_e(){
    BNdecimal pi("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145");
    BNdecimal pi4 = pi/BNdecimal("4");
    BNdecimal pi2 = pi/BNdecimal("2");
    BNdecimal __x = *this, one("1"), _d("0.2447"), _c("0.0663");
    BNdecimal _abs = __x.abs();
    BNdecimal arctan = pi4*__x - __x*(_abs - one)*(_d + _c*_abs);

    if(_abs < one)
        return arctan;
    BNdecimal _xinv = one/__x;
    return pi2-_xinv.arctan_e();
}
/**
 * @brief Tried an aproximation. Did not work!
 * @deprecated Does not work:(
 * 
 * @return BNdecimal 
 */
BNdecimal BNdecimal::arctan_p7(){
    BNdecimal pi("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145");
    BNdecimal pi4 = pi/BNdecimal("4");
    BNdecimal pi2 = pi/BNdecimal("2");
    BNdecimal x = *this, one("1");
    BNdecimal _abs = x.abs();

    BNdecimal a1("0.6366198228040826"),
        a2("2.1940566630059660"),
        a3("4.1987334443688801"),
        b1("3.4464210488063778"),
        b2("6.9285856685452193"),
        b3("9.5401599602587312");

    BNdecimal x_[8];
    x_[0]=one;
    for(int i=0;i<8;++i){
        x_[i+1] = x_[i]*x;
    }
    BNdecimal phi7_d = a1*x+a2*x_[2]+a3*x_[3]+(b3-a3)*x_[4]+(b2-a2)*x_[5]+(b1-a1)*x_[6]+x_[7];
    BNdecimal phi7_e = one + b1*x + b2*x_[2]+b3*x_[3]+b3*x_[4]+b2*x_[5]+b1*x_[6]+x_[7];

    return phi7_d/phi7_e;
}

std::ostream& operator <<(std::ostream& os, BNdecimal nr){
    std::string s="";
    BNdecimal::clean(nr);
    nr = nr.roundToDecimal(BN_COUT_SETPREC);
    if(nr.isNegative){
        s+='-';
    }
    std::string abs="";
    abs=nr.integerPart.cvalue;
    if(nr.decimalPoint < nr.integerPart.cvalue.size()){
        abs.insert(abs.begin() + abs.size()-nr.decimalPoint, '.');

        s+=abs;
        os<<s;
    } else {
        if(nr.isNegative) os<<"-";
        os<<"0.";
        for(int i=0;i<nr.decimalPoint - abs.size();++i){
            os<<"0";
        }
        os<<abs;
    }
    return os;
}

std::string BNdecimal::to_string(){
    BNdecimal nr = (*this);
    BNdecimal::clean(nr);
    std::string s="";
    nr = nr.roundToDecimal(BN_COUT_SETPREC);
    if(nr.isNegative){
        s+='-';
    }
    std::string abs="";
    abs=nr.integerPart.cvalue;
    if(nr.decimalPoint < nr.integerPart.cvalue.size()){
        abs.insert(abs.begin() + abs.size()-nr.decimalPoint, '.');

        s+=abs;
    } else {
        if(nr.isNegative) s+="-";
        s+="0.";
        for(int i=0;i<nr.decimalPoint - abs.size();++i){
            s+="0";
        }
        s+=abs;
    }
    if(s.at(s.size()-1) == '.')
        s.pop_back();
    return s;
}



