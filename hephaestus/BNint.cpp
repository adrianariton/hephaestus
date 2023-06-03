#include "BNint.h"

BNint::BNint(std::string str){
    cvalue = str;
}

BNint::BNint(){
    cvalue = "0";
}


BNint operator +(const BNint lhs, const BNint rhs){
    if(lhs.cvalue == "0"){
        return rhs;
    }
    if(rhs.cvalue == "0"){
        return lhs;
    }
    int it_rhs = rhs.cvalue.length()-1;
    int it_h = lhs.cvalue.length()-1;
    
    int max_it = it_rhs > it_h ? it_rhs : it_h;
    int carrydigit = 0;
    int reslen = max_it +1;
    std::string res = "0" + ((it_rhs > it_h) ? rhs.cvalue : lhs.cvalue);
    while(max_it >= 0){
        char _ch1 = (it_rhs >=0) ? rhs.cvalue.at(it_rhs) : '0';
        char _ch2 = (it_h >=0) ? lhs.cvalue.at(it_h) : '0';
        int _r = (_ch1- '0') + (_ch2- '0') + carrydigit;
        int _d = _r%10;
        int _c = _r/10;
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
    BNint _res = BNint(res);

    return _res;
}


bool BNint::operator >(BNint rhs){
    std::string lhsstr = cvalue;
    std::string rhsstr = rhs.cvalue;
    if(lhsstr.size() != rhsstr.size() )
        return (lhsstr.size()  > rhsstr.size() );
    
    return (lhsstr > rhsstr);

}

bool BNint::operator <(BNint rhs){
    std::string lhsstr = cvalue;
    std::string rhsstr = rhs.cvalue;
    while (cvalue.at(0) == '0' && cvalue.size() > 1)
    {
        cvalue.erase(0,1);
    }
    while (rhs.cvalue.at(0) != '0' && rhs.cvalue.size() > 1)
    {
        rhs.cvalue.erase(0,1);
    }
    if(lhsstr.size() != rhsstr.size() )
        return (lhsstr.size()  < rhsstr.size() );
    
    return (lhsstr < rhsstr);

}

bool BNint::operator>=(BNint rhs){
    return !(*this < rhs);
}

bool BNint::operator<=(BNint rhs){
    return !(*this > rhs);
}

bool BNint::operator==(BNint rhs){
    return (*this <= rhs && *this >= rhs);
}


BNint operator -(const BNint lhs, const BNint rhs){
    int it_rhs = rhs.cvalue.length()-1;
    int it_h = lhs.cvalue.length()-1;

    if(lhs.cvalue == rhs.cvalue){
        return BNint("0");
    }
    
    int max_it = it_rhs > it_h ? it_rhs : it_h;
    int borrower[max_it];
    int reslen = max_it;
    std::string res="0";
    //JAJJA
    for(int i=0; i<max_it;++i){
        res += "0";
        borrower[i] = 0;
    }
    borrower[max_it] = 0;

    int i, t=0, s;
    //h-rhs
    while(reslen >=0){
        char _chh = (it_h >=0) ? lhs.cvalue.at(it_h) : '0';
        char _chrhs = (it_rhs >=0) ? rhs.cvalue.at(it_rhs) : '0';
        int _ih = _chh - '0';
        int _irhs = _chrhs - '0';
        int _d=0;
        if(_ih == 0 && borrower[it_h] == 1){
            _ih = 9;
        } else
        if(_ih !=0 && borrower[it_h]== 1){
            _ih --;
        }
        if( _ih < _irhs){
            int _i = reslen -1;
            if(lhs.cvalue.at(_i) == '0'){
                while (lhs.cvalue.at(_i) == '0' && _i>=0){
                    borrower[_i] ++;
                    _i --;
                }
                borrower[_i]++;
            } else {
                borrower[_i]++;
            }
            
            _d = 10 + _ih - _irhs;
            
        } else {
            _d = _ih - _irhs;
        }
        res.at(reslen) = _d + '0';
        reslen --;
        max_it--;
        it_h--;
        it_rhs--;
    }
    while(res.at(0) == '0' && res.size() > 1){
        res.erase(0,1);

    }
    if(res == ""){
        res.push_back('0');
    }
    BNint _res = BNint(res);

    return _res;
    
    
}

BNint operator *(const BNint lhs, const BNint rhs){
    int n = lhs.cvalue.size();
    int m = rhs.cvalue.size();

    if(lhs.cvalue == "0" || rhs.cvalue=="0"){
        return BNint("0");
    }
    
    std::vector<int> result(n + m, 0);
    
    for (int i = n - 1; i >= 0; i--)
    for (int j = m - 1; j >= 0; j--)
    result[i + j + 1] += (lhs.cvalue[i] - '0') * (rhs.cvalue[j] - '0');
    
    
    int size = result.size();
    for (int i = size - 1; i > 0; i--) {
        if (result[i] >= 10) {
            result[i - 1] += result[i] / 10;
            result[i] = result[i] % 10;
        }
    }
    
    int i = 0;
    while (i < size && result[i] == 0)
        i++;
    
    
    if (i == size)
        return BNint("0");
    
    std::string temp;
    
    
    while (i < size) {
        temp += (result[i] + '0');
        i++;
    }
    BNint _r = BNint(temp);
    return _r;
}




BNint operator/(const BNint lhs, const BNint rhs){
    BNint a = lhs;
    BNint b = rhs;
    if(b.cvalue == "0")
        throw("Arithmetic Error: Division By 0");
    if(a < b){
        a = BNint("0");
        return a;
    }
    if(a == b){
        a = BNint("1");
        return a;
    }
    int i, lgcat = 0, cc;
    BNint ccc("9");
    int n = a.cvalue.size(), m = b.cvalue.size();
    std::vector<int> cat(n, 0);
    BNint t("");
    for (i = 0; BNint(t.cvalue + a.cvalue[i])  < b && i<a.cvalue.size();i++){
        
        t.cvalue += a.cvalue[i] ;
    }
    


    for (; i <n; i++){

        t.cvalue += a.cvalue[i];
        while (t.cvalue.at(0) == '0' && t.cvalue.size() > 1)
        {
            t.cvalue.erase(0,1);
        }

        for (ccc = BNint("9"); ccc * b > t && ccc > BNint("0");ccc = ccc - BNint("1"));

        if(!(ccc == BNint("0")) && ccc*b <= t)
        t = t - (ccc * b);


        cat[lgcat++] = ccc.cvalue[0] - '0';

    }

    a.cvalue.resize(cat.size());
    for (i = 0; i < lgcat;i++){
        a.cvalue[i] = cat[i]+'0';

    }
    a.cvalue.resize(lgcat);
    return a;
}
 

std::ostream& operator <<(std::ostream& os, BNint& nr){
    os<<nr.cvalue;
    return os;
}

std::istream& operator >>(std::istream& os, BNint& nr){
    os>>nr.cvalue;
    return os;
}