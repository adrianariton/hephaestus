#ifndef hcomp
#define hcomp
#include "big_cordic.cpp"
#include "BNcomplex.h"
typedef BNcomplex bigcomplex;

inline namespace hcomp{
    inline bigcomplex from_polar(bigreal r, bigreal theta){
        bigreal sin_th;
        bigreal cos_th;
        big::calc_sincos(theta, sin_th, cos_th);
        return bigcomplex( r*cos_th, r*sin_th);
    }
    inline bigreal brute_norm(bigcomplex __z){
        return brute::sqrt(__z.square_norm());
    }

    inline bigcomplex polar_coords(bigcomplex __z){
        bigreal _theta, _hyp;
        big::calc_arctan(__z.imaginary_part/__z.real_part, _theta, _hyp);
        if(__z.real_part.isNegative){
            _theta = _theta + BIG_PI;
        }
        return bigcomplex(_hyp * __z.real_part , _theta);
    }

    inline bigcomplex real_pow(bigcomplex __z, bigreal __e){
        bigcomplex __polar = hcomp::polar_coords(__z);
        bigreal __abs = __polar.real_part;
        bigreal __th = __polar.imaginary_part;

        bigreal __expabs = big::pow(__abs, __e);
        bigreal __nth = __th * __e;

        return hcomp::from_polar(__expabs, __nth);
    }
       
}

#endif