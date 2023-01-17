#ifndef HEPHAESTUS_CPP
#define HEPHAESTUS_CPP

#include "FCO.h"
#include "mvex.cpp"
#include "heph_complex.cpp"
#include "HTensor.h"
#include "HPoly.h"
#include "HRational.h"
#include "HSymbolic.h"
namespace heph
{
    inline bigreal sin(bigreal x){
        return big::sin(x);
    }
    inline bigreal cos(bigreal x){
        return big::cos(x);
    }
    inline bigreal exp(bigreal x){
        return big::exp(x);
    }
    inline bigreal ln(bigreal x){
        return big::ln(x);
    }
    inline bigreal pow(bigreal x, bigreal y){
        return big::pow(x, y);
    }
} // namespace heph

class _heph_predef_index_en{
    public:
    std::vector<std::string> indices;
    std::vector<bool> is_up;
    _heph_predef_index_en(std::vector<std::string> _indices, std::vector<bool> _is_up){
        indices = _indices;
        is_up = _is_up;
    }
};

inline _heph_predef_index_en _heph_predef_get_indexvectors(const std::string& s){
    std::string _bu = "";
    std::vector<std::string> _vstr;
    std::vector<bool> _vbool;
    char lastop = '^';
    for(int i=0; i<s.size(); ++i){
        if(s.at(i) == ' ') continue;
        if((s.at(i) != '^' && s.at(i) != '_') && (i != s.size()-1)){
            _bu+=s.at(i);
        } else {
            if(i == s.size()-1) _bu+=s.at(i);
            if(_bu != ""){
                if(lastop == '_'){
                    _vstr.push_back(_bu);
                    _vbool.push_back(false);
                } else if(lastop == '^'){
                    _vstr.push_back(_bu);
                    _vbool.push_back(true);
                }
            }
            _bu="";
            lastop = s.at(i);
        }
    }

    return _heph_predef_index_en(_vstr, _vbool);
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_normalize( const HTensor<T>& tensor, const std::string& values_indices){
    return HEinsteinNotation<T>(tensor, _heph_predef_get_indexvectors(values_indices).indices  ,  _heph_predef_get_indexvectors(values_indices).is_up);
}

template<typename T>
inline HTensor<T> _heph_predef_normalize(const HTensor<T>& tensor){
    return tensor;
}

// inline long double _heph_predef_normalize(const mve& func, const std::string& values){
//     return mvef::__hephlang_solvefunction(func, values);
// }

template<typename T>
inline HTensor<T> _heph_predef_normalize(const std::vector<T>& vals, const HShape& shape){
    return HTensor<T>(vals, shape);
}

template<typename T>
inline T _heph_predef_normalize(const HTensor<T>& tensor, const std::string& values_indices, const std::vector<int>& coords){
    return HEinsteinNotation<T>(tensor, _heph_predef_get_indexvectors(values_indices).indices  ,  _heph_predef_get_indexvectors(values_indices).is_up).at(coords);
}

template<typename T>
inline T _heph_predef_normalize(HTensor<T>& tensor, const std::vector<int>& coords){
    return tensor.at(coords).val();
}

inline long double _heph_predef_normalize(const mve& func, const std::vector<std::string>& var_names, const std::vector<long double>& var_values){
    return mvef::solvefunction(func, var_names, var_values);
}

template<typename T>
inline HTensor<T> _heph_predef_multiply(const HTensor<T>& lhs, const HTensor<T>& rhs){
    return HTensor<T>::tensor_product(lhs, rhs);
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const HEinsteinNotation<T>& lhs, const HEinsteinNotation<T>& rhs){
    return (lhs * rhs);
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const HTensor<T>& lhs, const std::string& lhs_indices, const HTensor<T>& rhs, const std::string& rhs_indices){
    return ( _heph_predef_normalize(lhs, lhs_indices) * _heph_predef_normalize(rhs, rhs_indices) );
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const HEinsteinNotation<T>& lhs, const HTensor<T>& rhs, const std::string& rhs_indices){
    return ( lhs * _heph_predef_normalize(rhs, rhs_indices) );
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const HTensor<T>& lhs, const std::string& lhs_indices, const HEinsteinNotation<T>& rhs){
    return ( _heph_predef_normalize(lhs, lhs_indices) * rhs );
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const HTensor<T>& lhs, const std::string& lhs_indices, const T& rhs){
    return ( _heph_predef_normalize(lhs, lhs_indices) * HEinsteinNotation<T>(HTensor<T>(rhs), {}, {}) );
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const T& lhs, const HTensor<T>& rhs, const std::string& rhs_indices){
    return (HEinsteinNotation<T>(HTensor<T>(lhs), {}, {})  *  _heph_predef_normalize(rhs, rhs_indices) );
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const HEinsteinNotation<T>& lhs, const T& rhs){
    return (lhs * HEinsteinNotation<T>(HTensor<T>(rhs), {}, {}) );
}

template<typename T>
inline HEinsteinNotation<T> _heph_predef_multiply(const T& lhs, const HEinsteinNotation<T>& rhs){
    return (HEinsteinNotation<T>(HTensor<T>(lhs), {}, {})  *  rhs );
}

inline auto METRIC_Minkowski = [](int x, int y){
    if(x==0 && y==0) return -1;
    return int(x==y);
};

inline auto METRIC_Euclid = [](int x, int y){ return int(x==y); };

inline HShape MATRIX_3X3({3,3});
inline HShape MATRIX_4X4({4,4});
inline HShape MATRIX_2x2({2,2});
inline HShape VECTOR_3({3});
inline HShape VECTOR_4({4});
inline HShape VECTOR_2({2});
inline HShape CUBE_4({4,4,4});
inline HShape CUBE_3({3,3,3});
inline HShape CUBE_2({2,2,2});

inline HPoly<HRational> QPOLY_ZERO((HRational)0);
inline HPoly<HRational> QPOLY_ONE((HRational)1);


/** Operators and shortcuts */

inline bigreal operator"" _big(long double x){
    return bigreal(std::to_string(x));
}
inline bigreal operator"" _big(unsigned long long x){
    return bigreal(std::to_string(x));
}
inline bigreal operator-(bigreal x){
    x.isNegative = !(x.isNegative);
    return x;
}
inline HRational operator"" _frac(unsigned long long x){
    return HRational(x, 1);
}
inline HRational operator-(HRational x){
    x = HRational(0) - x;
    return x;
}
template <typename T>
inline HPoly<T> operator-(HPoly<T> p){
    return p.zero_inverse();
}


inline HPoly<long double> operator"" _poly(long double x){
    return HPoly<long double>({(long double)x});
}
inline HPoly<HRational> operator"" _poly(unsigned long long x){
    return HPoly<HRational>({(HRational)x});
}
inline HPoly<int> operator"" _polyint(unsigned long long x){
    return HPoly<int>({(int)x});
}
inline BNcomplex I_big(0_big, 1_big);

inline HSymbolic operator"" _sym(unsigned long long x){
    return HSymbolic(x);
}
inline HSymbolic operator"" _sym(const char* x){
    return HSymbolic(x);
}

#define NEAR ALSO NEW_LINE ALSO
#define END_LINE ALSO NEW_LINE DONE;
#define ENDL END_LINE;
#define SYM HSymbolic
#define PLAIN SYM _ to_clean_string
#endif