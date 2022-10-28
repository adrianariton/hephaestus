#ifndef HEPH_UTILS_H
#define HEPH_UTILS_H
#include <iostream>
#include <string>

typedef long double (*tensor_metric_rule_longdouble)(int,int);


std::string operator |(std::string s1, std::string s2){
    return (s1+s2);
}
std::string operator |(const char* s1, std::string s2){
    return ( s1+s2);
}
#define FROM )(
inline bool HEPH_SHOW_DEBUG_LOG = true;
#define DEBUG_LOG(...) \
    if(HEPH_SHOW_DEBUG_LOG) \
        LOG __VA_ARGS__ DONE
#define USE_DEBUG_MODE() \
    HEPH_SHOW_DEBUG_LOG = true;
#define USE_RELEASE_MODE() \
    HEPH_SHOW_DEBUG_LOG = false;
#define LOG_ALONE(var) LOG NEW_LINE ALSO var ALSO NEW_LINE DONE
#define LOG_PTR(ptr, size) \
    std::cout<<"\n*["; \
    for(int i=0;i<size; ++i) {cout<<ptr[i]<<", ";} \
    std::cout<<"]\n";
#define JOIN | (std::string)
#define ALSO <<
#define LOG std::cout<<
#define DONE ;
#define NEW_LINE "\n"
#define SPACER "\n\n"
#define ALSO_SPACE <<" "<<
#define SPACE " "

#define LET auto
#define TENSOR(type) HTensor<type>

#define _ ::
typedef bigreal REAL100;
typedef long double REAL;
#define REAL100(variable) bigreal(#variable)

#define EMPTY_ARRAY []
#define COMPLEX100 bigcomplex

#define COMPLEX100(variable) bigcomplex(#variable)
#define REAL long double
#define INTEGER int
#define USE using
#define FUNCTIONS_FROM namespace
#define SAFE inline
#define GREEK Greek
#define STRING std::string
#define GREEK(val) Greek(#val) 
#define VECTOR(type) std::vector<type>
#define SHAPE HShape
#define NEW_LOG_SECTION LOG SPACER DONE
#define USING_FUNCTIONS_FOR_TYPE(namespace_name, ...) \
    { \
        using namespace namespace_name ## _FNS; \
        __VA_ARGS__ \
    } 
#define USING_NAMESPACE(namespace_name, ...) \
    { \
        using namespace namespace_name; \
        __VA_ARGS__ \
    } 
#define REAL100_FNS big_cordic
#define COMPLEX100_FNS heph_complex
#define FUNC_FNS mvef
#define GET ::
#define USE_HEPHAESTUS_CPP using namespace heph;
#define USE_HEPH_LANG ;

#define COMMA ,
typedef mve FUNC;

#define FUNC(...) \
    mve(#__VA_ARGS__)
#define TO_FUNC(iden) \
    mve(iden)

#define HEPH heph

#define calc_valueat(fn, ...) \
    __hephlang_solvefunction(fn, #__VA_ARGS__)
#define str_derivative(fn, var)\
    dfdx_string(fn, #var)

#define FOREACH(it ,var, IN_typeofset, vectype, ...) \
    FOREACH_##IN_typeofset(it,var, vectype, __VA_ARGS__)

#define FOREACH_IN_INTERVAL(it,var, interval, ...) \
    for(size_t it = 0; it < _heph_parse_interval_string(#interval).size(); it += _heph_parse_interval_string(#interval).step){ \
        auto var= _heph_parse_interval_string(#interval).at(it); \
        __VA_ARGS__ \
    } 
#define FOREACH_IN_TENSOR(it, indices, tensor, ...) \
    for(int it=0; it<HShape(tensor.measures()).signature(); ++it){ \
        std::vector<int> indices = tensor.coords_forindex(it, tensor.measures()); \
        __VA_ARGS__ \
    }
#define UGLY(v) _0predef_##v##_s23012_2991_hephaestus
#define LOG_VECTYPE(vectype) \
    log_vect(vectype);
    
#define FOREACH_IN_VECTYPE(it, var, vectype, ...) \
    for(size_t it = 0; it < vectype.size(); it += 1){ \
        auto& var = vectype.at(it); \
        __VA_ARGS__ \
    } 
#define EXIT_LOOP_IF(...) \
    if(__VA_ARGS__) \
        break;
#define EXIT_LOOP break;
#define SKIP continue;
#define SKIP_IF(...) \
    if(__VA_ARGS__) \
        continue;
#define LOGVAR(var) \
    std::cout<<(#var)<<":"<<(var)<<"\n";

#define WS_BEGIN {
#define WS_END }
#define IF if(
#define THEN ){
#define ELIF }else if(
#define ELSE }else{
#define END_IF }
#define DEBUG(...) \
    if(HEPH_SHOW_DEBUG_LOG) \
    { \
        __VA_ARGS__\
    }
#define TO_REAL100(cppfloatingpoint) bigreal(std::to_string(cppfloatingpoint))
class integer_interval{
    public:
        int a;
        int b;
        int step;
        integer_interval(int _a, int _b, int _step){
            a = _a;
            b = _b;
            step = _step;
        }
        size_t size(){
            return b-a+1;
        }
        int at(size_t i){
            return a+i;
        }

};
template <typename T>
inline void log_vect(std::vector<T> _vk){
    std::cout<<"\n[";
    for(int i=0;i<_vk.size(); ++i){
        std::cout<<_vk.at(i)<<", ";
    }
    std::cout<<"]\n";
}
inline integer_interval _heph_parse_interval_string(std::string interval){
    std::string a="", b="", step="", _bu="";
    short sw = 0;
    //LOG "\nfunction:\n" DONE
    for(int i=0; i<interval.size(); ++i){
        if(interval.at(i) != ':' && i != interval.size() -1){
            _bu += interval.at(i);
        } else {
            if(i == interval.size()-1) _bu += interval.at(i);
            //LOGVAR(_bu)
            sw ++;
            if(sw == 1)
                a = _bu;
            if(sw == 2)
                b = _bu;
            if(sw == 3)
                step = _bu;
            _bu="";
        }
    }
    int step_int = 1;
    if(step != "") step_int = std::stoi(step);
    int a_int = std::stoi(a);
    int b_int = std::stoi(b);
    return integer_interval(a_int, b_int, step_int);
}
inline bool could_be_integer_interval(std::string interval){
    int sw  =0;
    for(int i=0; i<interval.size(); ++i){
        char c = interval.at(i);
        if(c==':') sw++;
        if(!(('0'<c && c<'9') || c==':' || c=='.'))
            return false;
    }
    if(sw == 0) return false;
    return true;
}
#define TENSOR_AT(indices) .at(indices).val()
#define THROW(err) throw std::invalid_argument(err);
#define YEET RETURN
#define RETURN(...) return __VA_ARGS__;

#define EINSTEIN_NOTATION(type) \
    HEinsteinNotation<type>



#define INDICES(...) \
    _heph_predef_get_indexvectors(#__VA_ARGS__).indices  ,  _heph_predef_get_indexvectors(#__VA_ARGS__).is_up

#define EINSTEIN(type , tensor, indices) \
    EINSTEIN_NOTATION(type)(tensor, INDICES(indices))

#define HEPH_FLAG

#define LAMBDA []
#define AT .at

#define CONCAT(a, b) a ## b
#define AS_STRING(a) #a

#define __ AUTO_TYPE_CONVERTER
#define AUTO_TYPE_CONVERTER  _heph_predef_normalize
#define __m AUTO_TYPE_MULTIPLYER
#define __multiply AUTO_TYPE_MULTIPLIER
#define AUTO_TYPE_MULTIPLYER _heph_predef_multiply
#define EMPTY_ARRAY {}
#define EMPTY_VECTOR {}
#define EMPTY {}
#define REF &
#define POINTER *
#define REF_TO(var) &var
#define DEREF(pointer) *pointer

#define DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR(name, type_of_tens, tens1_name, tens1_indices, tens2_name, tens2_indices, tensors_bool_constraints) \
    auto DEFN_ ## name = [](HTensor<type_of_tens> tens1_name, HTensor<type_of_tens> tens2_name) { \
        if(!( tensors_bool_constraints )) THROW("Invalid product arguments at DEFINED product" ); \
        return __m(tens1_name, tens1_indices, tens2_name, tens2_indices) ; \
    } 
#define LOG_SECTION(str) \
    std::cout<<"\n\n-------------"<<str<<"-------------\n\n";

#define FRAC HRational
#define RATIONAL HRational

#define POLY HPoly
#define QPOLY HPoly<HRational>

#endif