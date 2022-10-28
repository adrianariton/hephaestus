#include "BinaryBNInt.h"

BinaryBNint::BinaryBNint(std::string str){
    isNegative = false;
    if(str.at(0) == '-'){
        str.erase(0,1);
        isNegative = true;
    }
    bits = str;

}
BinaryBNint::BinaryBNint(){
    bits = "0";
    isNegative = false;
}

BinaryBNint BinaryBNint::addPositives(const BinaryBNint lhs, const BinaryBNint rhs){
     if(lhs.bits == "0"){
        return rhs;
    }
    if(rhs.bits == "0"){
        return lhs;
    }
    int it_rhs = rhs.bits.length()-1;
    int it_h = lhs.bits.length()-1;
    
    int max_it = it_rhs > it_h ? it_rhs : it_h;
    int carrydigit = 0;
    int reslen = max_it +1;
    std::string res = "0" + ((it_rhs > it_h) ? rhs.bits : lhs.bits);
    while(max_it >= 0){
        char _ch1 = (it_rhs >=0) ? rhs.bits.at(it_rhs) : '0';
        char _ch2 = (it_h >=0) ? lhs.bits.at(it_h) : '0';
        int _r = (_ch1- '0') + (_ch2- '0') + carrydigit;
        int _d = _r%2;
        int _c = _r/2;
        res.at(reslen) = _d + '0'; 
        carrydigit = _c;
        reslen --;
        max_it--;
        it_h--;
        it_rhs--;
    }
    res.at(0) = carrydigit + '0';
    while(res.at(0) == '0'){
        res.erase(0,1);

    }
    if(res == ""){
        res.push_back('0');
    }
    BinaryBNint _res = BinaryBNint(res);

    return _res;
}

BinaryBNint BinaryBNint::subsPositives(const BinaryBNint lhs, const BinaryBNint rhs){
    int it_rhs = rhs.bits.length()-1;
    int it_h = lhs.bits.length()-1;

    if(lhs.bits == rhs.bits){
        return BinaryBNint("0");
    }
    
    int max_it = it_rhs > it_h ? it_rhs : it_h;
    int borrower[max_it];
    int reslen = max_it;
    std::string res="0";
    for(int i=0; i<max_it;++i){
        res += "0";
        borrower[i] = 0;
    }
    // h-rhs
    while(reslen >=0){
        char _chh = (it_h >=0) ? lhs.bits.at(it_h) : '0';
        char _chrhs = (it_rhs >=0) ? rhs.bits.at(it_rhs) : '0';
        int _ih = _chh - '0';
        int _irhs = _chrhs - '0';
        int _d=0;
        if(_ih == 0 && borrower[it_h] == 1){
            _ih = 1;
        } else
        if(_ih !=0 && borrower[it_h]== 1){
            _ih --;
        }
        if( _ih < _irhs){
            int _i = reslen -1;
            if(lhs.bits.at(_i) == '0'){
                while (lhs.bits.at(_i) == '0' && _i>=0){
                    borrower[_i] ++;
                    _i --;
                }
                borrower[_i]++;
            } else {
                borrower[_i]++;
            }
            
            _d = 2 + _ih - _irhs;
            
        } else {
            _d = _ih - _irhs;
        }
        res.at(reslen) = _d + '0';
        reslen --;
        max_it--;
        it_h--;
        it_rhs--;
    }
    while(res.at(0) == '0'){
        res.erase(0,1);

    }
    if(res == ""){
        res.push_back('0');
    }
    BinaryBNint _res = BinaryBNint(res);

    return _res;
}

bool operator>(const BinaryBNint lhs, const BinaryBNint rhs){
    std::string _lhsstr = lhs.bits;
    std::string _rhsstr = rhs.bits;
    while(_lhsstr.at(0) == '0'){
        _lhsstr.erase(0,1);
    }
    if(_lhsstr == "")
        _lhsstr = "0";
    while(_rhsstr.at(0) == '0'){
        _rhsstr.erase(0,1);
    }
    if(_rhsstr == "")
        _rhsstr = "0";
    if(_lhsstr.size() != _rhsstr.size())
        return (_lhsstr.size() > _rhsstr.size());

    return _lhsstr > _rhsstr;
}

bool operator<(const BinaryBNint lhs, const BinaryBNint rhs){
    std::string _lhsstr = lhs.bits;
    std::string _rhsstr = rhs.bits;
    while(_lhsstr.at(0) == '0'){
        _lhsstr.erase(0,1);
    }
    if(_lhsstr == "")
        _lhsstr = "0";
    while(_rhsstr.at(0) == '0'){
        _rhsstr.erase(0,1);
    }
    if(_rhsstr == "")
        _rhsstr = "0";
    if(_lhsstr.size() != _rhsstr.size())
        return (_lhsstr.size() < _rhsstr.size());

    return _lhsstr < _rhsstr;
}

bool operator>=(const BinaryBNint lhs, const BinaryBNint rhs){
    return !(lhs < rhs);
}

bool operator<=(const BinaryBNint lhs, const BinaryBNint rhs){
    return !(lhs > rhs);
}

BinaryBNint operator+(const BinaryBNint lhs, const BinaryBNint rhs){
    if(rhs.bits == "0"){
        return lhs;
    }
     if(lhs.bits == "0"){
       
        return rhs;
    }
    BinaryBNint result, plhs = lhs, prhs = rhs;
    plhs.isNegative = false;
    prhs.isNegative = false;
    if(lhs.isNegative && rhs.isNegative){
        result = BinaryBNint::addPositives(plhs, prhs);
        result.isNegative = true;
    } else if(!lhs.isNegative && !rhs.isNegative){
        result = BinaryBNint::addPositives(plhs, prhs);
        result.isNegative = false;
    } else if(!lhs.isNegative && rhs.isNegative){
        if(plhs > prhs){
            result =    BinaryBNint::subsPositives(plhs, prhs);
            result.isNegative = false;
        } else {
            result =BinaryBNint::subsPositives(prhs, plhs);
            result.isNegative = true;
        }
    } else if(lhs.isNegative && !rhs.isNegative){
        if(prhs > plhs){
            result = BinaryBNint::subsPositives(prhs, plhs);
            result.isNegative = false;
        } else {
            result = BinaryBNint::subsPositives(plhs, prhs);
            result.isNegative = true;
        }
    }
    return result;
}

BinaryBNint operator-(const BinaryBNint lhs, const BinaryBNint rhs){
    if(rhs.bits == "0"){
        return lhs;
    }
     if(lhs.bits == "0"){
        BinaryBNint _lh = lhs;
        _lh.isNegative = !lhs.isNegative;
        return _lh;
    }
    BinaryBNint result, plhs = lhs, prhs = rhs;
    prhs.isNegative = !rhs.isNegative;
    result = plhs + prhs;
    return result;
}

std::ostream& operator <<(std::ostream& os, BinaryBNint nr){
    if(nr.isNegative)
        os<<"-";
    os<<nr.bits;
    return os;
}

BinaryBNint operator<<(const BinaryBNint lhs, int shift){
    BinaryBNint _lhs = lhs;
    while(_lhs.bits.at(0) == '0'){
        _lhs.bits.erase(0,1);
    }
    if(_lhs.bits == "")
        _lhs.bits = "0";
    for(int i=0; i<shift; ++i){
        _lhs.bits+="0";
    }
    return _lhs;
}
BinaryBNint operator>>(const BinaryBNint lhs, int shift){
    BinaryBNint _lhs = lhs;
    if(_lhs.bits == "0"){
        _lhs.bits = "0";
        return BinaryBNint("0");
    }
    while(_lhs.bits.at(0) == '0'){
        _lhs.bits.erase(0,1);
    }
    if(_lhs.bits == ""){
        _lhs.bits = "0";
        return BinaryBNint("0");
    }
    if(_lhs.bits.size() <= shift){
        return BinaryBNint("0");
    } 
    int sz = _lhs.bits.size();
    _lhs.bits.resize(sz - shift);
    return _lhs;
}