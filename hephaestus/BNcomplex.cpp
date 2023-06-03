#include "BNcomplex.h"

BNcomplex::BNcomplex(BNdecimal real_){
    real_part = real_;
    imaginary_part = BNdecimal("0");
    square_i = BNdecimal("-1");
}

BNcomplex::BNcomplex(BNdecimal real_, BNdecimal imag_){
    real_part = real_;
    imaginary_part = imag_;
    square_i = BNdecimal("-1");
}

BNcomplex::BNcomplex(BNdecimal real_, BNdecimal imag_, BNdecimal sq_i){
    real_part = real_;
    imaginary_part = imag_;
    square_i = sq_i;
}

BNcomplex operator +(const BNcomplex lhs, const BNcomplex rhs){
    if(!(lhs.square_i == rhs.square_i)){
        throw("Error, cannot add elements that don't belong in the same ring!");
    }
    return BNcomplex(lhs.real_part+rhs.real_part, lhs.imaginary_part + rhs.imaginary_part, lhs.square_i);
}

BNcomplex operator -(const BNcomplex lhs, const BNcomplex rhs){
    if(!(lhs.square_i == rhs.square_i)){
        throw("Error, cannot substract elements that don't belong in the same ring!");
    }
    return BNcomplex(lhs.real_part-rhs.real_part, lhs.imaginary_part - rhs.imaginary_part, lhs.square_i);
}

BNcomplex operator *(const BNcomplex lhs, const BNcomplex rhs){
    if(!(lhs.square_i == rhs.square_i)){
        throw("Error, cannot multiply elements that don't belong in the same ring!");
    }
    BNdecimal rp = lhs.real_part*rhs.real_part + lhs.square_i*lhs.imaginary_part*rhs.imaginary_part;
    BNdecimal ip = lhs.real_part*rhs.imaginary_part+rhs.real_part*lhs.imaginary_part;

    return BNcomplex(rp, ip, lhs.square_i);
}
 
BNdecimal BNcomplex::square_norm(){
    BNcomplex __t = (*this);
    return (__t.real_part*__t.real_part+__t.imaginary_part*__t.imaginary_part);
}

BNcomplex BNcomplex::conj(){
    BNcomplex __t = (*this);
    if(__t.imaginary_part == BNdecimal("0")){
        return __t;
    }
    __t.imaginary_part.isNegative = !__t.imaginary_part.isNegative;
    return __t;
}
BNcomplex BNcomplex::inverse(){
    BNcomplex __t = (*this);
    BNcomplex __conj = __t.conj();
    BNdecimal __real_part = (__conj.real_part / __t.square_norm());
    BNdecimal __im_part = (__conj.imaginary_part / __t.square_norm());
    return BNcomplex(__real_part, __im_part, __t.square_i);
}
BNcomplex operator /(const BNcomplex lhs, const BNcomplex rhs){
    return lhs * ((BNcomplex)rhs).inverse();
}

std::ostream& operator <<(std::ostream& os, BNcomplex nr){
    os<<nr.real_part<<"+"<<nr.imaginary_part<<"i";
    return os;
}