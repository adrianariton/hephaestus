#ifndef MVEX_CPP    
#define MVEX_CPP
#include "MVExp.h"
#include "big_cordic.cpp"
#define DERIV_MAX_TREE_INDEX 2000
typedef MVExp mve;

inline std::string EMPTY_STR_ARR[0] = {};

// -------------------------------------------------
// c - constant, v - variable

 /**
    0 - NUMBER
    1 - OPERATOR
    NEW: 2 - FUNCTION (2 VARS - ACTS LIKE OPERATOR)
    3 - FUNCTION (SINGLE - VARRED)
    4 - PARANTHESIS
    9 - DELETED
*/
inline namespace mvef{
    inline bool is_variable(std::string __v){
        for(int i=0;i<BASIC_FUNC_NR;++i){
            if(__v == MVE_BASIC_FUNC_NAMES[i])
                return false;

        }
        if(big::is_number(__v))
            return false;
        for(int i=0;i<__v.size();++i){
            if(__v.at(i)<'a' || __v.at(i)>'z')
                return false;
            if(__v.at(i) == '-')
                return false;
        }
        
        return true;
    }
    inline mve applysvfun(std::string fun, mve _exp){
        int _l = _exp.rlen;
        std::string _rstr[_l+1];
        int _rtypes[_l+1];
        long double _rlds[_l+1];
        std::copy(_exp.rstr, _exp.rstr + _l, _rstr);
        _rstr[_l] = fun;
        std::copy(_exp.rlds, _exp.rlds + _l, _rlds);
        _rlds[_l] = 0;
        std::copy(_exp.rtypes, _exp.rtypes + _l, _rtypes);
        _rtypes[_l] = 3;
        mve _n;
        _n.rlen = _l+1;
        std::copy(_rstr, _rstr + _l +1, _n.rstr);
        std::copy(_rlds, _rlds + _l +1, _n.rlds);
        std::copy(_rtypes, _rtypes + _l +1, _n.rtypes);
        return _n;
    }
    inline mve constantf(std::string nr){
        return mve(nr, 0, EMPTY_STR_ARR);
    }

    inline mve negative(mve _exp){
        return (mvef::constantf("0") - _exp);
    }
    struct nodef{
        int type;
        long double data_nr;
        std::string data_str;
        int posinfun;
        int fatherposinfun;
    };
    struct nodeftree{
        nodef val;
        struct nodeftree* father;
    };
    inline void __buildfunctiontree(mve fun, nodef* out_tree, int& tree_len);
    inline bool needsParantheses(std::string op, std::string str){
        if(op=="+")
            return false;
        int index = 0;
        for(int i=0; i<str.size();++i){
            
            if(index == 0) {
                switch (op[0])
                {
                case '-':
                    if(str.at(i) == '+' || str.at(i) == '-')
                        return true;
                    break;
                case '*':
                    if(str.at(i) == '+' || str.at(i) == '-')
                        return true;
                    break;
                case '/':
                    if(str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '*' || str.at(i) == '/' || str.at(i) == '{')
                        return true;
                    break;
                case '^':
                    if(str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '*' || str.at(i) == '/' || str.at(i) == '{')
                        return true;
                    break; 

                default:
                    break;
                }
            }
            if(str.at(i) == '('  || str.at(i) == '{'){
                index++;
            }
            else if(str.at(i) == ')' || str.at(i) == '}'){
                index--;
            } 
        }
        return false;
    }
    inline std::string applyOpString(std::string op, std::string f1, std::string f2){
        if(op == "*"){
             if(f1 == "1" || f1 == "(1)"){
                return f2;
            }
            if(f2 == "1" || f2 == "(1)"){
                return f1;
            }
        }
        if(op == "+"){
            if(f1 == "0"){
                return f2;
            }
            if(f2 == "0"){
                return f1;
            }
        }
        if(op == "/"){
            if(f1 == "0"){
                return "0";
            }    
        }
        if(op == "-"){
            if(f2 == "0"){
                return f1;
            }
            if(f2 == f1){
                return "0";
            }

            
        }
        if(op == "*"){
            if(f1 == "1" || f1 == "(1)"){
                return f2;
            }
            if(f2 == "1" || f2 == "(1)"){
                return f1;
            }
            if(f1 == "0"){
                return "0";
            }
            if(f2 == "0"){
                return "0";
            }
        }

        if(big::is_number(f1) && big::is_number(f2)){
            bigreal nf1(f1);
            bigreal nf2(f2);
            bigreal res = nf1;
            switch (op[0])
            {
                case '+':
                    res = nf1 + nf2;
                    break;
                case '-':
                    res = nf1 - nf2;
                    break;
                case '*':
                    res = nf1 * nf2;
                    break;
                case '/':
                    if(!(nf2 == bigreal("0")))
                    res = nf1 / nf2;
                    break;
            default:
                break;
            }
            if(!(nf2 == bigreal("0")))
            return res.to_string();
        }
        if(big::is_number(f1)){
            f1 = bigreal(f1).to_string();
        }
        if(big::is_number(f2)){
            f2 = bigreal(f2).to_string();
        }
        if(op == "+"){
            if(big::is_number(f1) && big::is_number(f2)){
                return f1+op+f2;
            } else if(big::is_number(f1)){
                return f1+op+f2;
            } else if(big::is_number(f2)){
                return f2+op+f1;
            } else {
                return f1+op+f2;
            }
        }
        if(op == "-"){

            if(big::is_number(f2)){
                bigreal nf2(f2);
                if(nf2.isNegative){
                    return f1+"+"+nf2.abs().to_string();
                } else return f1+op+f2;
            } else if(mvef::is_variable(f2)){
                return f1+op+f2;
            }
            if(mvef::needsParantheses(op, f2))
            return f1+op+"("+f2+")";
            else return f1+op+f2;
        }
        if(op == "^"){
            if(big::is_number(f2)){
                bigreal nf2(f2);
                bigreal::clean(nf2);
                if(nf2 == BIG_ONE){
                    return f1;
                } else if(nf2 == BIG_ZERO){
                    return "1";
                }
            }
        }
        if(op == "/"){
            if(big::is_number(f2)){
                bigreal nf2(f2);
                bigreal::clean(nf2);
                 if(nf2 == BIG_ZERO){
                    return "0";
                }
            }
        }
        bool needs1 = mvef::needsParantheses(op, f1);
        bool needs2 = mvef::needsParantheses(op, f2);

        if(needs1 && needs2){
            return "("+f1+")"+op+"("+f2+")";

        } else if(needs1){
            return "("+f1+")"+op+f2;
        } else if(needs2){
            return f1+op+"("+f2+")";
        } else {
            return f1+op+f2;
        }

        return "("+f1+")"+op+"("+f2+")";

        
    }
    inline std::string latex_applyOpString(std::string op, std::string f1, std::string f2){
        
         if(op == "+"){
            if(f1 == "0"){
                return f2;
            }
            if(f2 == "0"){
                return f1;
            }
        }
         if(op == "/"){
            if(f1 == "0"){
                return "0";
            }    
        }
        if(op == "-"){
            if(f2 == "0"){
                return f1;
            }
            if(f2 == f1){
                return "0";
            }

            
        }
        if(op == "*"){
            if(f1 == "1"){
                return f2;
            }
            if(f2 == "1"){
                return f1;
            }
            if(f1 == "0"){
                return "0";
            }
            if(f2 == "0"){
                return "0";
            }
        }

        if(big::is_number(f1) && big::is_number(f2)){
            bigreal nf1(f1);
            bigreal nf2(f2);
            bigreal res = nf1;
            switch (op[0])
            {
                case '+':
                    res = nf1 + nf2;
                    break;
                case '-':
                    res = nf1 - nf2;
                    break;
                case '*':
                    res = nf1 * nf2;
                    break;
                case '/':
                    res = nf1 / nf2;
                    break;
            default:
                break;
            }
            return res.to_string();
        }
        if(big::is_number(f1)){
            f1 = bigreal(f1).to_string();
        }
        if(big::is_number(f2)){
            f2 = bigreal(f2).to_string();
        }
        if(op == "+"){
            if(big::is_number(f1) && big::is_number(f2)){
                return f1+op+f2;
            } else if(big::is_number(f1)){
                return f1+op+f2;
            } else if(big::is_number(f2)){
                return f2+op+f1;
            } else {
                return f1+op+f2;
            }
        }
        if(op == "-"){

            if(big::is_number(f2)){
                bigreal nf2(f2);
                if(nf2.isNegative){
                    return f1+"+"+nf2.abs().to_string();
                } else return f1+op+f2;
            } else if(mvef::is_variable(f2)){
                return f1+op+f2;
            }
            if(mvef::needsParantheses(op, f2))
            return f1+op+"("+f2+")";
            else return f1+op+f2;
        }
        if(op == "^"){
            if(big::is_number(f2)){
                bigreal nf2(f2);
                bigreal::clean(nf2);
                if(nf2 == BIG_ONE){
                    return f1;
                } else if(nf2 == BIG_ZERO){
                    return "1";
                }
            }
        }
        if(op == "/"){
            if(big::is_number(f2)){
                bigreal nf2(f2);
                bigreal::clean(nf2);
                 if(nf2 == BIG_ZERO){
                    return "0";
                }
            }
        }
        bool needs1 = mvef::needsParantheses(op, f1);
        bool needs2 = mvef::needsParantheses(op, f2);

        if(op == "/"){
            if(big::is_number(f2)){
                bigreal nf2(f2);
                bigreal::clean(nf2);
                if(nf2 == BIG_ONE){
                    return f1;
                } 
            } 
            return "\\frac{"+f1+"}{"+f2+"}";
        }

        if(needs1 && needs2){
            return "("+f1+")"+op+"("+f2+")";

        } else if(needs1){
            return "("+f1+")"+op+f2;
        } else if(needs2){
            if(op == "^")
                return f1+op+"{"+f2+"}";

            return f1+op+"("+f2+")";
        } else {
            return f1+op+f2;
        }
        if(op == "^")
            return "("+f1+")"+op+"{"+f2+"}";
        return "("+f1+")"+op+"("+f2+")";

    }
    inline std::string applyFunString(std::string fun, std::string f1){
        if(fun == "ln"){
            if(f1 == "1" || f1=="(1)"){
                return "0";
            }
        }
        return fun+"("+f1+")";
    }
    inline std::string applyFunCFloat(std::string fun, long double f1){
        //HERE
    }
    inline std::string latex_applyFunString(std::string fun, std::string f1){
        if(fun == "ln"){
            if(f1 == "1" || f1=="(1)"){
                return "0";
            }
        }
        return "\\"+fun+"("+f1+")";
    }
    inline std::string apply5VFunString(std::string fun, std::string p1, std::string p2, std::string p3, std::string p4, std::string p5){
        if(fun == "sum"){
            return fun+"("+p1+","+p2+","+p3+","+p4+","+p5+")";
        }
        return fun+"("+p1+","+p2+","+p3+","+p4+","+p5+")";
    }
    inline std::string latex_apply5VFunString(std::string fun, std::string p1, std::string p2, std::string p3, std::string p4, std::string p5){
        if(fun == "sum"){
            return "("+ fun+"_{"+p1+"="+p2+"; +="+p4+"}^{"+p3+"}"+p5+")";
        }
        return "\\" + fun+"("+p1+","+p2+","+p3+","+p4+","+p5+")";
    }
    
    inline mve identityf(std::string var){
        std::string _Arr[1] = {var};
        mve _f(var, 1, _Arr);
        return _f;
    }
    
    
    
    inline std::string MVEF_BUFFER[DERIV_MAX_TREE_INDEX];
    inline long double MVEF_CFLOAT_BUFFER[DERIV_MAX_TREE_INDEX];
    inline bigreal MVEF_BIGREAL_BUFFER[DERIV_MAX_TREE_INDEX];

    inline void empty_buffer(){
        for(int i=0; i<DERIV_MAX_TREE_INDEX;++i){
            MVEF_BUFFER[i] = "";
        }
    }
    inline void fillBuffer(nodef* tree, int tree_len, int position){
        if(tree[position].type == EXV_TYPE_VARIABLE){
            MVEF_BUFFER[position] =  tree[position].data_str;
        } else if(tree[position].type == EXV_TYPE_NUMBER){
            MVEF_BUFFER[position] = std::to_string(tree[position].data_nr);
        } else if(tree[position].type == EXV_TYPE_OPERATOR){
            int f1;
            int f2;
            int csw = 0;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    if(csw == 0){
                        f1 = i;
                        csw++;

                    }
                    else if(csw == 1)
                        f2 = i;
                }
                
            }
            char op = tree[position].data_str[0];
            std::string opstr = tree[position].data_str;
            fillBuffer(tree, tree_len, f1);
            fillBuffer(tree, tree_len, f2);
            MVEF_BUFFER[position] = mvef::applyOpString(opstr,MVEF_BUFFER[f1], MVEF_BUFFER[f2]);


        } else if(tree[position].type == EXV_TYPE_1VFUNCTION){
            int f1;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    f1=i;
                }
            }
            std::string fct = tree[position].data_str;
            fillBuffer(tree, tree_len, f1);

            MVEF_BUFFER[position] =  mvef::applyFunString(fct, MVEF_BUFFER[f1]);
           

        }
    }
    
    inline void latex_fillBuffer(nodef* tree, int tree_len, int position){
        if(tree[position].type == EXV_TYPE_VARIABLE){
            MVEF_BUFFER[position] =  tree[position].data_str;
        } else if(tree[position].type == EXV_TYPE_NUMBER){
            MVEF_BUFFER[position] = std::to_string(tree[position].data_nr);
        } else if(tree[position].type == EXV_TYPE_OPERATOR){
            int f1;
            int f2;
            int csw = 0;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    if(csw == 0){
                        f1 = i;
                        csw++;

                    }
                    else if(csw == 1)
                        f2 = i;
                }
                
            }
            char op = tree[position].data_str[0];
            std::string opstr = tree[position].data_str;
            latex_fillBuffer(tree, tree_len, f1);
            latex_fillBuffer(tree, tree_len, f2);
            MVEF_BUFFER[position] = mvef::latex_applyOpString(opstr,MVEF_BUFFER[f1], MVEF_BUFFER[f2]);


        } else if(tree[position].type == EXV_TYPE_1VFUNCTION){
            int f1;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    f1=i;
                }
            }
            std::string fct = tree[position].data_str;
            latex_fillBuffer(tree, tree_len, f1);

            MVEF_BUFFER[position] =  mvef::latex_applyFunString(fct, MVEF_BUFFER[f1]);
           

        }
    }

    inline void solve_fill_cBuffer(nodef* tree, int tree_len, int position, std::vector<long double> vals, std::vector<std::string> vars){
        if(tree[position].type == EXV_TYPE_VARIABLE){
            int sw = 0;
            for(int it = 0; it< vals.size(); ++it){
                if(vars.at(it) == tree[position].data_str){
                    MVEF_CFLOAT_BUFFER[position] =  vals.at(it);
                    tree[position].data_nr = vals.at(it);
                    sw = 1;
                    tree[position].type = EXV_TYPE_NUMBER;
                    break;
                }
                
            }
            if(sw == 0)
                    throw std::invalid_argument("Not enough variables or values");
        } else if(tree[position].type == EXV_TYPE_NUMBER){
            MVEF_CFLOAT_BUFFER[position] = (tree[position].data_nr);
        } else if(tree[position].type == EXV_TYPE_OPERATOR){
            int f1;
            int f2;
            int csw = 0;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    if(csw == 0){
                        f1 = i;
                        csw++;

                    }
                    else if(csw == 1)
                        f2 = i;
                }
                
            }
            char op = tree[position].data_str[0];
            std::string opstr = tree[position].data_str;
            solve_fill_cBuffer(tree, tree_len, f1, vals, vars);
            solve_fill_cBuffer(tree, tree_len, f2, vals, vars);
            switch (op)
            {
            case '-':
                MVEF_CFLOAT_BUFFER[position] = MVEF_CFLOAT_BUFFER[f1] - MVEF_CFLOAT_BUFFER[f2];
                break;
            case '+':
                MVEF_CFLOAT_BUFFER[position] = MVEF_CFLOAT_BUFFER[f1] + MVEF_CFLOAT_BUFFER[f2];
                break;
            case '/':
                MVEF_CFLOAT_BUFFER[position] = MVEF_CFLOAT_BUFFER[f1] / MVEF_CFLOAT_BUFFER[f2];
                break;
            case '*':
                MVEF_CFLOAT_BUFFER[position] = MVEF_CFLOAT_BUFFER[f1] * MVEF_CFLOAT_BUFFER[f2];
                break;
            case '^':
                MVEF_CFLOAT_BUFFER[position] = std::pow(MVEF_CFLOAT_BUFFER[f1] , MVEF_CFLOAT_BUFFER[f2]);
                break;
            default:
                std::cout<<"EXVEPTOION";
                break;
            }


        } else if(tree[position].type == EXV_TYPE_1VFUNCTION){
            int f1;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    f1=i;
                }
            }
            std::string fct = tree[position].data_str;
            solve_fill_cBuffer(tree, tree_len, f1, vals, vars);
            if(fct == "sin"){
                MVEF_CFLOAT_BUFFER[position] =  std::sin(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "cos") {
                MVEF_CFLOAT_BUFFER[position] =  std::cos(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "ln"){
                MVEF_CFLOAT_BUFFER[position] =  std::log(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "tan"){
                MVEF_CFLOAT_BUFFER[position] =  std::tan(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "cot"){
                MVEF_CFLOAT_BUFFER[position] =  1.0/std::tan(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "sinh"){
                MVEF_CFLOAT_BUFFER[position] =  std::sinh(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "cosh") {
                MVEF_CFLOAT_BUFFER[position] =  std::cosh(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "atan"){
                MVEF_CFLOAT_BUFFER[position] =  std::atan(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "asin"){
                MVEF_CFLOAT_BUFFER[position] =  std::asin(MVEF_CFLOAT_BUFFER[f1]);
            } else if(fct == "acos"){
                MVEF_CFLOAT_BUFFER[position] =  1.0/std::acos(MVEF_CFLOAT_BUFFER[f1]);
            } else throw std::invalid_argument("Function not supported!");
           

        }
    }
    inline std::string dfdx_recsortedtree(nodef* tree, int tree_len, int position, std::string var){
        if(tree[position].type == EXV_TYPE_VARIABLE){
            if(tree[position].data_str == var){
                return "1";
            } else {
                return "0";
            }
        } else if(tree[position].type == EXV_TYPE_NUMBER){
            return "0";
        } else if(tree[position].type == EXV_TYPE_OPERATOR){
            int f1;
            int f2;
            int csw = 0;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    if(csw == 0){
                        f1 = i;
                        csw++;

                    }
                    else if(csw == 1)
                        f2 = i;
                }
            }
            char op = tree[position].data_str[0];
            switch (op)
            {
            case '+':
                return mvef::applyOpString("+", dfdx_recsortedtree(tree, tree_len, f1, var), dfdx_recsortedtree(tree, tree_len, f2, var));
                break;
            case '-':
                return mvef::applyOpString("-", dfdx_recsortedtree(tree, tree_len, f1, var), dfdx_recsortedtree(tree, tree_len, f2, var));
                break;
            case '*':
                return mvef::applyOpString("+",mvef::applyOpString("*", dfdx_recsortedtree(tree, tree_len, f1, var), MVEF_BUFFER[f2]), mvef::applyOpString("*",MVEF_BUFFER[f1], dfdx_recsortedtree(tree, tree_len, f2, var)));
                break;
            case '/':
                return mvef::applyOpString("/",mvef::applyOpString("-",mvef::applyOpString("*", dfdx_recsortedtree(tree, tree_len, f1, var), MVEF_BUFFER[f2]), mvef::applyOpString("*", MVEF_BUFFER[f1], dfdx_recsortedtree(tree, tree_len, f2, var))), mvef::applyOpString("*",MVEF_BUFFER[f2] ,MVEF_BUFFER[f2]) );
                break;
            case '^':
                return mvef::applyOpString("+", mvef::applyOpString("*", mvef::applyOpString("^", MVEF_BUFFER[f1], MVEF_BUFFER[f2]), mvef::applyOpString("*", mvef::dfdx_recsortedtree(tree, tree_len, f2, var), mvef::applyFunString("ln", MVEF_BUFFER[f1]))),  mvef::applyOpString("*", mvef::dfdx_recsortedtree(tree, tree_len, f1, var), mvef::applyOpString("*", MVEF_BUFFER[f2], mvef::applyOpString("^", MVEF_BUFFER[f1], mvef::applyOpString("-", MVEF_BUFFER[f2], "1")))) );
                break;
            }
        } else if(tree[position].type == EXV_TYPE_1VFUNCTION){
            int f1;
            for(int i=0;i<tree_len;++i){
                if(tree[i].fatherposinfun == tree[position].posinfun){
                    // it's the son of my fun
                    f1=i;
                }
            }
            std::string fct = tree[position].data_str;

            if(fct == "sin"){
                return mvef::applyOpString("*", mvef::applyFunString("cos", MVEF_BUFFER[f1]) , dfdx_recsortedtree(tree, tree_len, f1, var));
            } else if(fct == "cos") {
                return mvef::applyOpString("*", "(0-1)", mvef::applyOpString("*", mvef::applyFunString("sin", MVEF_BUFFER[f1]) , dfdx_recsortedtree(tree, tree_len, f1, var)));
            } else if(fct == "ln"){
                return mvef::applyOpString("/",  dfdx_recsortedtree(tree, tree_len, f1, var), MVEF_BUFFER[f1]);
            } else if(fct == "tan"){
                return mvef::applyOpString("/", dfdx_recsortedtree(tree, tree_len, f1, var), mvef::applyOpString("^", mvef::applyFunString("cos", MVEF_BUFFER[f1]) , "2"));
            } else if(fct == "cot"){
                return mvef::applyOpString("/",mvef::applyOpString("-", "0", dfdx_recsortedtree(tree, tree_len, f1, var)) , mvef::applyOpString("^", mvef::applyFunString("sin", MVEF_BUFFER[f1]) , "2"));
            }

        }
        return "1";
    }
    
    inline bool isNorV(int type){
        if(type == EXV_TYPE_NUMBER || type == EXV_TYPE_VARIABLE){
            return true;
        }
        return false;
    }
    /**
     * @brief ROOT node is positioned at the end!
     * 
     * @param fun 
     * @param out_tree 
     * @param tree_len 
     */
    inline void __buildfunctiontree(mve fun, nodef* out_tree, int& tree_len){
        int deleted = 0;
        tree_len = 0;
        int delta_deleted = 0;
        int next[fun.rlen + 1], prev[fun.rlen + 1];
        int pseudotypes[fun.rlen];
        for(int it=0; it< fun.rlen ;++it){
            next[it] = it+1;
            prev[it] = it-1;
            pseudotypes[it] = fun.rtypes[it];
        }
        next[fun.rlen] = 0;
        prev[fun.rlen] = fun.rlen - 1;
        mve fn = fun;
        while(fn.rlen - deleted > 1){
            delta_deleted = 0;
            for(int it=next[fn.rlen]; it<fn.rlen; it=next[it]){
                if(pseudotypes[it] == EXV_TYPE_OPERATOR){
                    if( mvef::isNorV(pseudotypes[prev[prev[it]]])  && mvef::isNorV(pseudotypes[prev[it]])){
                        pseudotypes[it] = EXV_TYPE_NUMBER;
                        pseudotypes[prev[it]] = EXV_TYPE_DELETED;
                        pseudotypes[prev[prev[it]]] = EXV_TYPE_DELETED;

                        nodef obj1;
                        nodef obj2;
                        obj1.type = fn.rtypes[prev[prev[it]]];
                        if(obj1.type == EXV_TYPE_NUMBER)
                            obj1.data_nr = fn.rlds[prev[prev[it]]];
                        else
                            obj1.data_str = fn.rstr[prev[prev[it]]];
                    
                        obj2.type = fn.rtypes[prev[it]];
                        if(obj2.type == EXV_TYPE_NUMBER)
                            obj2.data_nr = fn.rlds[prev[it]];
                        else
                            obj2.data_str = fn.rstr[prev[it]];
                        
                        obj1.posinfun = prev[prev[it]];
                        obj2.posinfun = prev[it];
                        obj1.fatherposinfun = it;
                        obj2.fatherposinfun = it;

                        out_tree[tree_len] = obj1;
                        tree_len++;
                        out_tree[tree_len] = obj2;
                        tree_len++;

                        if(it<2){
                            std::cout<<"Error2";
                            return;
                        }


                        next[prev[prev[prev[it]]]] = it;
                        prev[it] = prev[prev[prev[it]]];
                        deleted += 2;
                        delta_deleted += 2;
                    } 
                } else if(pseudotypes[it] == EXV_TYPE_1VFUNCTION){
                    if(mvef::isNorV(pseudotypes[prev[it]])){
                        pseudotypes[it] = EXV_TYPE_NUMBER;
                        pseudotypes[prev[it]] = EXV_TYPE_DELETED;

                        nodef obj;
                        obj.type = fn.rtypes[prev[it]];
                        if(obj.type == EXV_TYPE_NUMBER)
                            obj.data_nr = fn.rlds[prev[it]];
                        else 
                            obj.data_str = fn.rstr[prev[it]];
                        obj.posinfun = prev[it];
                        obj.fatherposinfun = it;

                        out_tree[tree_len] = obj;
                        tree_len++;

                        if(it<1){
                            std::cout<<"Error1";
                            return;
                        }
                        next[prev[prev[it]]] = it;
                        prev[it] = prev[prev[it]];
                        deleted += 1;
                        delta_deleted +=1;
                    }
                }
            }
            
            if(delta_deleted == 0){
                std::cout<<"Error - total del"<<deleted<<"\n"; 
                return;
            }
        }

        for(int i=0; i<fn.rlen; ++i){
            if(pseudotypes[i] != EXV_TYPE_DELETED){
                nodef obj;
                obj.type = fn.rtypes[i];
                if(obj.type == EXV_TYPE_NUMBER)
                    obj.data_nr = fn.rlds[i];
                else    
                    obj.data_str = fn.rstr[i];
                obj.posinfun = i;
                obj.fatherposinfun = -1;

                out_tree[tree_len] = obj;
                tree_len++;
            }
        }


    }
    inline std::string dfdx_string(mve fun, std::string x){
        mvef::nodef tree[DERIV_MAX_TREE_INDEX];
        int treelen = 0;
        mvef::__buildfunctiontree(fun, tree, treelen);
        int root_;
        for(int i=0;i<treelen;++i){
            if(tree[i].fatherposinfun == -1){
                root_ = i;
            }
        }
        mvef::fillBuffer(tree, treelen, root_);
        return mvef::dfdx_recsortedtree(tree, treelen, root_, x);
    }

    inline long double solvefunction(mve fun, std::vector<std::string> vars, std::vector<long double> vals){
        mvef::nodef tree[DERIV_MAX_TREE_INDEX];
        int treelen = 0;
        mvef::__buildfunctiontree(fun, tree, treelen);
        int root_;
        for(int i=0;i<treelen;++i){
            if(tree[i].fatherposinfun == -1){
                root_ = i;
            }
        }
        mvef::solve_fill_cBuffer(tree, treelen, root_, vals, vars);
        return MVEF_CFLOAT_BUFFER[treelen -1];
    }
    inline long double __hephlang_solvefunction(mve fun, std::string data){
        std::vector<long double> vals;
        std::vector<std::string> vars;
        std::string __vardef = "", __var="", __def="", __bu="";
        int q = 0;
        char delimiter = ',';
        for(int i=0;i<data.size(); ++i){
            if(data.at(i) == ' ')
                continue;
            if(data.at(i) != delimiter && i != data.size() -1)
                __vardef += data.at(i);
            else {
                q=0;
                if(i == data.size()-1) __vardef += data.at(i);
                for(int it = 0; it<__vardef.size(); ++it){
                    if(__vardef.at(it) ==' ')
                        continue;
                    if(__vardef.at(it) != ':' && it!= __vardef.size()-1)
                        __bu+=__vardef.at(it);
                    else {
                        if(it == __vardef.size()-1) __bu+= __vardef.at(it);
                        q ++;
                        if(q == 1)
                            __var = __bu;
                        else __def = __bu;
                        __bu = "";
                    }
                }
                __vardef = "";
                vars.push_back(__var);
                vals.push_back(std::stold(__def));
            }

            
        }
        

        mvef::nodef tree[DERIV_MAX_TREE_INDEX];
        int treelen = 0;
        mvef::__buildfunctiontree(fun, tree, treelen);
        int root_;
        for(int i=0;i<treelen;++i){
            if(tree[i].fatherposinfun == -1){
                root_ = i;
            }
        }
        mvef::solve_fill_cBuffer(tree, treelen, root_, vals, vars);
        return MVEF_CFLOAT_BUFFER[treelen -1];
    }
    inline std::string plain(mve fun){
        mvef::nodef tree[DERIV_MAX_TREE_INDEX];
        int treelen = 0;
        mvef::__buildfunctiontree(fun, tree, treelen);
        int root_;
        for(int i=0;i<treelen;++i){
            if(tree[i].fatherposinfun == -1){
                root_ = i;
            }
        }
        mvef::fillBuffer(tree, treelen, root_);
        std::string s = MVEF_BUFFER[treelen-1];
        return s;
    }
    inline std::string latex(mve fun){
        mvef::nodef tree[DERIV_MAX_TREE_INDEX];
        int treelen = 0;
        mvef::__buildfunctiontree(fun, tree, treelen);
        int root_;
        for(int i=0;i<treelen;++i){
            if(tree[i].fatherposinfun == -1){
                root_ = i;
            }
        }
        mvef::latex_fillBuffer(tree, treelen, root_);
        std::string s = MVEF_BUFFER[treelen-1];
        return s;
    }
    inline mve clean(mve fun){
        std::string s = mvef::plain(fun);
        return mve(s);
    }
    inline mve num(long double n){
        mve _exp("1", 0, EMPTY_STR_ARR);
        _exp.rlds[0] = n;
        return _exp;
    }
    inline bool byfather(nodef _v1, nodef _v2){
        return (_v1.fatherposinfun > _v2.fatherposinfun);
    }
     
};

#endif