#include "MVexp.h"

MVExp::MVExp(char* expression, int len, int var_nr, char** var_names){
    exv_getRPNQ(expression, len, EXV_MESSAGES, var_nr, var_names, rlds, rstr, rtypes, rlen);
}

MVExp::MVExp(std::string expression, int var_nr, std::string* var_names){
    int _exlen = expression.size();
    char _ex[_exlen];

    std::copy(expression.c_str(), expression.c_str() + _exlen, _ex);

    char* _vn[var_nr];
    for(int i=0; i<var_nr; ++i){
        std::string currentvar =  var_names[i];
        int l = currentvar.size();

        _vn[i] = (char*) malloc (l+1);
        std::copy(currentvar.c_str(), currentvar.c_str() + l, _vn[i]);
    }

    exv_getRPNQ(_ex, _exlen, EXV_MESSAGES, var_nr, _vn, rlds, rstr, rtypes, rlen);
}
MVExp::MVExp(std::string expression){
    mve_getRPNQ(expression, false, rlds, rstr, rtypes, rlen);
}
MVExp::MVExp(){
    rlen = 0;
}

MVExp MVExp::solve(std::string OP, const MVExp lhs, const MVExp rhs){
    MVExp _new;

    std::string new_rstr[EXV_MAX_LEN];
    int new_rtypes[EXV_MAX_LEN];
    long double new_rlds[EXV_MAX_LEN];
    int new_rlen = lhs.rlen + rhs.rlen + 1;

    int m = lhs.rlen;
    int n = rhs.rlen;
    n++;

    MVExp _l = lhs, _r = rhs;


    int* X = _l.rtypes;
    int* Y = _r.rtypes;
    Y[_r.rlen] = EXV_TYPE_OPERATOR;
    std::copy(X, X + m, _new.rtypes);
    std::copy(Y, Y + n, _new.rtypes + m);

    std::string* Xs = _l.rstr;
    std::string* Ys = _r.rstr;
    Ys[_r.rlen] = OP;
    std::copy(Xs, Xs + m, _new.rstr);
    std::copy(Ys, Ys + n, _new.rstr + m);

    long double* Xi = _l.rlds;
    long double* Yi = _r.rlds;
    Yi[_r.rlen] = 0.0;
    std::copy(Xi, Xi + m, _new.rlds);
    std::copy(Yi, Yi + n, _new.rlds + m);

    
    _new.rlen = new_rlen;

    return _new;

}

MVExp operator +(const MVExp lhs, const MVExp rhs){
    return MVExp::solve("+", lhs, rhs);
}

MVExp operator -(const MVExp lhs, const MVExp rhs){
    return MVExp::solve("-", lhs, rhs);
}

MVExp operator *(const MVExp lhs, const MVExp rhs){
    return MVExp::solve("*", lhs, rhs);
}

MVExp operator /(const MVExp lhs, const MVExp rhs){
    return MVExp::solve("/", lhs, rhs);
}

MVExp operator ^(const MVExp lhs, const MVExp rhs){
    return MVExp::solve("^", lhs, rhs);
}

MVExp MVExp::subexp(int begin, int length){
    MVExp _exp = (*this);
    int _rlen = length;
    std::string _rstr[length];
    int _rtypes[length];
    long double _rlds[length];

    std::copy(_exp.rstr + begin, _exp.rstr + begin + _rlen, _rstr);
    std::copy(_exp.rlds + begin, _exp.rlds + begin + _rlen, _rlds);
    std::copy(_exp.rtypes + begin, _exp.rtypes + begin + _rlen, _rtypes);

    MVExp _n;
    _n.rlen = _rlen;
    std::copy(_rlds, _rlds + _rlen, _n.rlds);
    std::copy(_rstr, _rstr + _rlen, _n.rstr);
    std::copy(_rtypes, _rtypes + _rlen, _n.rtypes);
    return _n;

}

bool MVExp::isvalid(){
    int _s = 0;
    for(int i=0; i<rlen; ++i){
        _s++;
        _s-=EXV_VALENCE[rtypes[i]];
        if(_s < 0)
            return false;
    }
    if(_s == 1)
        return true;
    else
        return false;
}

int MVExp::stacktrace(){
    int _s = 0;
    for(int i=0; i<rlen; ++i){
        _s++;
        _s-=EXV_VALENCE[rtypes[i]];
    }
    return _s;
}

void MVExp::split_terms(MVExp& out1, MVExp& out2, std::string& out_op){
    if(!(*this).isvalid())
        throw("Unvalid Expression");
    MVExp _exp = (*this);
    if(_exp.rtypes[_exp.rlen -1] == EXV_TYPE_OPERATOR){
        out_op = _exp.rstr[_exp.rlen - 1];
        for(int i = 1; i <_exp.rlen -1; ++i){
            MVExp e1 = _exp.subexp(0, i);
            MVExp e2 = _exp.subexp(i, _exp.rlen - 1 - i);
            if(e1.isvalid() && e2.isvalid()){
                out1 = e1;
                out2 =e2;
            }  
        }
    } else {
        out_op = "invalid";
    }
    

}

bool MVExp::canstrip(){
    MVExp _exp = (*this);
    return (_exp.rtypes[_exp.rlen - 1] ==EXV_TYPE_1VFUNCTION);
}

void MVExp::strip(MVExp& out_exp, std::string& out_funcname){
    if(!(*this).isvalid())
        throw("Unvalid Expression");
    MVExp _exp = (*this);
    if(_exp.rtypes[_exp.rlen - 1] ==EXV_TYPE_1VFUNCTION){
        out_exp = _exp.subexp(0, _exp.rlen - 1);
        out_funcname = _exp.rstr[_exp.rlen - 1];
    } else {
        out_funcname = "invalid";
    }
}


std::ostream& operator <<(std::ostream& os, MVExp expression){
    std::cout<<"[";
    for(int it=0; it<expression.rlen; ++it){
       
        if(expression.rtypes[it] == EXV_TYPE_NUMBER){
            if(it == expression.rlen-1)
                std::cout<<expression.rlds[it];
            else
                std::cout<<expression.rlds[it]<<", ";
        } else {
            if(it == expression.rlen-1)
                std::cout<<expression.rstr[it];
            else
                std::cout<<expression.rstr[it]<<", ";
        }
    }
    std::cout<<"] : len:"<<expression.rlen;
    if(EXV_COUT_TYPES){
        std::cout<<"\n[";
        for(int it=0; it<expression.rlen; ++it){
            if(it == expression.rlen-1)
                std::cout<<expression.rtypes[it];
            else
                std::cout<<expression.rtypes[it]<<", ";
        }
        std::cout<<"]";
    }
}


