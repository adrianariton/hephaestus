/**
 Copy Right Ariton Adrian!
 © Ariton Adrian!
*/



#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include <chrono>

#include "hephaestus.cpp"
#include "Heph_Utils.h"


using namespace std;
using namespace std::chrono;

USE_HEPHAESTUS_CPP

long double my_fun(long double x){
    return std::pow(x, 6.0) - 4;
}

long double beautiful(long double __x){
    long double sgn = 1;
    if(std::abs(__x) != __x)
        sgn = -1;
    return sgn * floor(abs(__x) * 10000.0) / 10000.0;
}

char expr[] = "x^2-7*x+3+3*x_n + x_n";

int main() {

    cout<<"\n\n\n-----------------Math evaluator using long double-----------------\n";

    /**Derivatives solved by fco*/
    long double _var = 1.5l;

    /**Config initial precisions*/
    fco_config__Precisions();
    /**Increase precision by a factor of 10^5*/
    fco_increasePrecision_ln(5);

    cout<<"\n\nDerivative of the function at "<<_var<<": "<<fco_derivativeSR_1VFC(my_fun, _var)<<" "<<fco_derivativeSL_1VFC(my_fun, _var)<<" "<<fco_derivativeO6_1VFC(my_fun, _var)<<" "<<fco_derivativeSLR_1VFC(my_fun, _var);
    cout<<"\nDelta error in derivative: "<<fco_calc__DerivError(my_fun, _var)<<"\n";
    
    fco_config__Precisions(); 
    fco_increasePrecision_ln(0);

    cout<<"\nf': "<<fco_calc__NthDerivativeSLR( my_fun, _var, 1)<<"\n";
    cout<<"\nf'': "<<fco_calc__NthDerivativeSLR( my_fun, _var, 2)<<"\n\n\n";
    cout<<"\nf''': "<<fco_calc__NthDerivativeSLR( my_fun, _var, 3)<<"\n\n\n";

    /**Get Solutions by fco */    
    int beautifulSolsNumber = 0;
    long double beautifulSols[MAX];
    fco_calc__SolutionsForFunction(FCO_DERIV_1VF_SLR, my_fun, -4, 4, beautifulSols, beautifulSolsNumber);
    cout<<"Solutions fr f=0: ";
    for(int it = 0; it < beautifulSolsNumber; ++it){
        long double rez = beautifulSols[it];
        cout<<roundToDecimal(10, rez)<<"  ";
    }

    /** Remez min-max polynomial method */
    long double out_polyarr[MAX];
    int out_len;
    long double remez_err;
    // - for fixed degree
    // - fco_calc__RemezPolyArray(false ,my_fun, 0, 50, 15, 0.1, out_polyarr, out_len, remez_err);   <-- this can also be used to calculate for a given error and iterations
    fco_calc__optimalMinMaxPoly(my_fun, -2, 2, 1e-7, 21, out_polyarr, out_len, remez_err);
    cout<<"\n\nRemez polynomial:\n";
    for(int i=0;i<out_len;++i){
        if(beautiful(abs(out_polyarr[i])) > 0){
            cout<<beautiful(out_polyarr[i])<<"*x^"<<i<<" + ";

        }
    }
    cout<<"\nError in calculation: "<<remez_err<<"\n\n";


    //error_verify
    long double __v = 1.3l;
    cout<<"f / P -- "<<my_fun(__v)<<" / "<<fco_calc__PolyValAt(__v, out_polyarr, out_len)<<"\n\n";

    long double derivArr[N_MAX];
    fco_calc__PolyDerivativeArray(out_polyarr, out_len, derivArr);

    cout<<"f' - from poly ~Not reliable for remez:(~  "<<fco_calc__PolyValAt(__v, derivArr, out_len -1);

    
    cout<<"\n\n"<<"-----------------------Binary and CORDIC----------------------"<<"\n\n";

    bigreal cs, cc, bdqs("0.7877143603132630285025");
    bigreal ccs, ccc, catan;

    auto start = high_resolution_clock::now();
    big_cordic::bin_calc_sincos(bdqs, ccs, ccc);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function SIN-COS: "
            << duration.count() << " microseconds\n\n" << endl;
    cout<<"\n\nsin:"<<ccs<<"\ncos:"<<ccc<<"\n\n";

    start = high_resolution_clock::now();
    big_cordic::calc_sinhcosh(bdqs, ccs, ccc);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function SINH-COSH: "
            << duration.count() << " microseconds\n\n" << endl;
    cout<<"\n\nsinh:"<<ccs<<"\ncosh:"<<ccc<<"\n\n";

    bigreal chyp;
    start = high_resolution_clock::now();
    big_cordic::calc_arctan(bdqs, catan, chyp);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function ATANH: "
            << duration.count() << " microseconds\n\n" << endl;
    cout<<"\n\natan:"<<catan;
    cout<<"\nhyp:"<<chyp.roundToDecimal(5);


    bigreal catanh, chyph;
    big_cordic::calc_arctanh(bigreal("0.8"), catanh, chyph);
    cout<<"\nATANH:"<<catanh<<"\nhyph:"<<chyph<<"\n";

    bigreal cln, csqrt;
    big_cordic::calc_lnsqrt(bigreal("9"), cln, csqrt);
    cout<<"\n\nLN:"<<cln<<"\nsqrt:"<<csqrt<<"\n";


    cout<<"\n\n";

    cout<<"\n\n"<<"-----------------------Math S    ymbolic String expression evaluator-----------------------";

    EXV_COUT_TYPES = true;
    mve myexp = mve("u^(u+6*x)+ln(x*u)");
    cout<<mvef::solvefunction(myexp, {"x", "u"}, {2.4, 1.2})<<"\n\n";

    cout<<"\n\n--------FIRST DERIV--------\n\n";
    std::string __G = mvef::dfdx_string(myexp, "u");
    cout<<__G<<"\n";
    cout<<mvef::latex(mve(__G))<<"\n";

    // -LATEX SUPPORT- []
    mvef::empty_buffer();
    cout<<mvef::latex(myexp)<<"\n";
    cout<<mvef::plain(myexp)<<"\n";

    cout<<"\n\n--------NATURAL NUMBERS--------\n\n";

    cout<<natural_num::gcd(bigreal("9"), bigreal("6"));

    cout<<"\n\n--------COMPLEX NUMBERS+IEEE--------\n\n";

    BNcomplex z(bigreal("122223"), bigreal("122223"));
    BNcomplex z1(bigreal("5"), bigreal("2"));
    cout<<z/z1<<"\n\n";
    cout<<hcomp::polar_coords(z);     
    cout<<"\n\n"<<big_cordic::pow(bigreal("3"), bigreal("2"));
    cout<<"\n\n"<<big_cordic::exp(bigreal("0.7"));
    cout<<"\n\nIEEE check: "<<big_cordic::pow(bigreal("10.12122"), bigreal("30.3421"));
    

    cout<<"\n\n--------GREEK--------\n\n";

    Greek _alpha("mu");
    cout<<(_alpha.unicode_value);


    cout<<"\n\n--------TENSORS--------\n\n";

    HShape T_SHAPE({2});
    vector<int> t_values;
    for(int i=0;i<2;++i)
        t_values.push_back(i);
    
                 
    LET mytens = TENSOR(int)(t_values, T_SHAPE); 

    // HTENS_COUT_DEPTH_DIM = true;
    cout<<mytens<<"\n";

    for(int i=0;i<mytens.measures().size(); ++i){
        std::cout<<" "<<mytens.measures(i);
    }
    std::cout<<"\n";
    std::cout<<"\n\n";

    HTensor<int> myvsltens(5); 


    HTensor<int> prtens = HTensor<int>::tensor_product(mytens, myvsltens);
    std::cout<<prtens;

    cout<<"\n\n--------HEPH LANG TRIAL--------\n\n";

    USE_RELEASE_MODE()

    LET mytens2 = TENSOR(int)(t_values, T_SHAPE) DONE 
    LET prodtensor = TENSOR(int) _ tensor_product(mytens, myvsltens) DONE
    LOG SPACER ALSO prodtensor ALSO NEW_LINE DONE

    LET h_n1 = REAL100(2.312) DONE
    LET h_n2 = REAL100(2.171771798797139873298312078382093219317803273) DONE

    LET prod = REAL100_FNS _ sin(h_n1 * h_n2) DONE
    LOG SPACER ALSO prod DONE

    LET myfunction = FUNC(u^(u+6*x)+ln(x*u)+x^(-1)) DONE
    LET result = __(myfunction, {"x", "u"}, {1.2, 2.4}) DONE
    LOG SPACER ALSO result ALSO NEW_LINE DONE

    LET derivative_str = FUNC_FNS _ dfdx_string(myfunction, "x") DONE

    LET fun2 = TO_FUNC(derivative_str) DONE 

    LOG derivative_str ALSO NEW_LINE DONE

    LET a = REAL100(2.1231222) DONE
    LOG REAL100_FNS _ sin(a) ALSO SPACER DONE
    
    DEBUG(
    FOREACH(i, elem, IN_INTERVAL, 2:34:1, 
        LOGVAR(elem)
    ))

    LET vek = VECTOR(REAL)({2.3, 4.5, 1.2}) DONE
    LOG SPACER DONE
    FOREACH(i, elem, IN_VECTYPE, vek, 
        elem++;
    )
    FOREACH(i, elem, IN_VECTYPE, vek, 
        SKIP_IF(elem == 5.5)
        LOGVAR(elem)
        LET mybignr = TO_REAL100(elem) DONE
        LOG REAL100_FNS _ sin(mybignr) ALSO NEW_LINE DONE
    )
    LOG SPACER DONE

    LET cube = SHAPE({3,3,3}) DONE
    LET vek_ = VECTOR(REAL)({}) DONE
    FOREACH(it, nr, IN_INTERVAL, 1:27:1, 
        vek_.push_back((REAL)nr) DONE
    )
    LET cube_tensor = __(vek_, cube) DONE

    FOREACH(i, indices, IN_TENSOR, cube_tensor,
        cube_tensor TENSOR_AT(indices) += 0.43 DONE
    )
    FOREACH(i, indices, IN_TENSOR, cube_tensor,
        LOG_VECTYPE(indices)
        LOG cube_tensor.at(indices) ALSO NEW_LINE DONE
    )
    DEBUG_LOG("HELLO" ALSO " NOTHELLO")
    LET _mystrstr = STRING("alllallllla") DONE
    NEW_LOG_SECTION
    FOREACH(i, elem, IN_VECTYPE, _mystrstr, 
        elem = elem + 1 DONE
    )
    FOREACH(i, elem, IN_VECTYPE, _mystrstr, 
        LOG elem DONE
    )
    DEBUG(
        IF vek.size() == 3 THEN
            LOG "Weeeeeeeee" DONE
            LOG "HHAHHHAHA" DONE
        ELIF vek.size() == 2 THEN
            LOG "WOOOOO" DONE
        ELSE LOG "WTEIEIE" DONE
        END_IF
    )


    LET clambda = LAMBDA(REAL _X){
        RETURN(std::pow(_X, 6)-4.0 )
    } DONE

    LET clsolnr = 0 DONE
    REAL clsols[MAX] = {} DONE
    FUNC __a = FUNC(a-b+c*d+5) DONE
    fco_calc__SolutionsForLambda(FCO_DERIV_1VF_SLR, clambda, -4, 4, clsols, clsolnr) DONE
    NEW_LOG_SECTION
    LOG_PTR(clsols, clsolnr)


    cout<<"\n\n--------EINSTEIN NOTATION--------\n\n";
    NEW_LOG_SECTION

    LET four_vek_vek = VECTOR(REAL)({1, 2, 2, 1}) DONE
    LET four_shape = SHAPE({4}) DONE
    LET four_vec = __(four_vek_vek, four_shape) DONE
    NEW_LOG_SECTION

    FOREACH(i, indices, IN_TENSOR, cube_tensor,
        LOG_VECTYPE(indices)
        LOG __(cube_tensor, indices) ALSO NEW_LINE DONE
        LOG __(cube_tensor, "_alpha^beta^gamma", indices) DONE
        LOG NEW_LINE DONE
    )
        LOG four_vec DONE

    DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR(innerprod, REAL, _x, "_alpha", _y, "^alpha", _x.dim() == 1 && _y.dim()==1);
    DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR(matrixprod, REAL, _x, "^alpha_beta", _y, "^beta_gamma", _x.dim() == 2 && _y.dim()==2);

    NEW_LOG_SECTION
    LOG "------------------------------------\n" DONE

    LET m1vals = VECTOR(REAL)({1, 2, 1, 2, 6, 7, 1, 2, 0});
    LET m2vals = VECTOR(REAL)({2, -2, 1, 0, -2, 0, 1, 2, -6});
    LET vec3vals = VECTOR(REAL)({2,1,-2});
    LET vec3_1vals = VECTOR(REAL)({-1,0,-3});


    LET matrix3x3_shape = SHAPE({3, 3});
    LET vec3_shape = SHAPE({3});

    LET m1_mak = __(m1vals, MATRIX_3X3) DONE
    LET m2_mak = __(m2vals, matrix3x3_shape) DONE
    LET vek3_v = __(vec3vals, vec3_shape) DONE
    LET vek3_1_v = __(vec3_1vals, vec3_shape) DONE
    

    LET m1m2 = DEFN_matrixprod(m1_mak, m2_mak) DONE
    LET v3v31 = __m( m1_mak, "_alpha^beta", vek3_1_v, "^alpha") DONE
    NEW_LOG_SECTION
    LOG m1m2.tensor ALSO NEW_LINE DONE
    LOG m1_mak ALSO NEW_LINE DONE
    LOG v3v31.tensor ALSO NEW_LINE DONE

    LET vek31up = __(vek3_1_v, "_alpha");

    FOREACH(i, ind, IN_TENSOR, m1_mak,
        LOG __(m1_mak, "_alpha_beta").at(ind) ALSO SPACE DONE
    )
    LOG NEW_LINE DONE
    LET m1up = __(m1_mak, "^beta^alpha");

    FOREACH(i, indices, IN_TENSOR, m1m2.tensor, 
        LOG m1m2 AT(indices) ALSO SPACE DONE
        LOG __(m1_mak, "^alpha_beta").at(indices) DONE
        LOG_VECTYPE(indices)
        LOG NEW_LINE DONE
    )

    DEBUG(
        LET tpr = __m( DEFN_innerprod(four_vec, four_vec) , (REAL)2.33) DONE
        NEW_LOG_SECTION
    )

    LOG_SECTION("POLYNOMIALS")
    HPoly<REAL> adi(std::vector<REAL>{-6, 13, -7, -1, 1});
    HPoly<REAL> andu(std::vector<REAL>{-6, 1, 1});
    (andu  - adi).log();

    HPoly<REAL> rem, quot;
    quot = HPoly<REAL>::quot(adi, andu, rem);
    LOG_SECTION("REM")

    rem.log();
    quot.log();

    POLY<REAL> gcd, t, s, bez1, bez2;
    adi.deriv().log();
    polyextendedgcd(adi, andu, gcd, t, s, bez1, bez2);
   // HPoly<REAL>::extended_gcd(adi, eadi.deriv(), gcd, t, s, bez1, bez2);

    LOG_SECTION("EXGCD")

    gcd.log();
    t.log();
    s.log();
    bez1.log();
    bez2.log();
    LOG_SECTION("DERIV")
    adi.deriv().log();
     
    LOG_SECTION("HERMITE")

    QPOLY PF( {1, -2, 1}), PG({-3, 0, 1});
    QPOLY DF( {18, -12, 2}), DG({5, -6, 1});
    PF = multipleroot((FRAC)5, 3) * multipleroot((FRAC)1, 4)  * multipleroot((FRAC)3, 1) ;
    POLYLOG(polygcd(DF, DG))
    LOG_SECTION("H2")
    POLYLOG(resultant(PF, PG))
    LET vkt = hermite_reduction(PG, PF);

    FOREACH(i, elem, IN_VECTYPE, vkt,
        vkt AT(i) .log();
        IF i%2==0 THEN
            LOG "-----------------" DONE
        END_IF
    )     
    
    POLYLOG(PG)
    POLYLOG(PF)
    //LOG PG.to_string() DONE
    LET solvkt = QPOLY::sqfree_solutions(PF);
    LOG_VECTYPE(solvkt)
    // LOG PF.calc_at((FRAC)5);
    LOG_SECTION("INTEGRATION")
    PF = multipleroot(5_frac, 3) * multipleroot(1_frac, 4)  * multipleroot(3_frac, 1) ;
    PG = QPOLY({-3, 0, 1});
    LOG QPOLY::integrate_polyfrac(PG, PF) DONE
    LOG_SECTION("OPS")
    LET numerouno = -123.243_big;
    LOG numerouno DONE
    LOG_SECTION("COMPLEX OPS")
    LET a_com = (2_big * I_big + 3_big - I_big * I_big + 6_big) / I_big;
    LOG a_com DONE
    LOG_SECTION("SYMBOLIC MATH")
        LOG "aaaaa" DONE

        LET b_sym = HSymbolic("b") DONE
    LOG "aaaaa" DONE

    LET x_sym = HSymbolic("x") DONE
    (x_sym + x_sym).llog();
    LOG SYM _ to_clean_string(x_sym + x_sym) DONE
    LOG (x_sym + x_sym - (2*x_sym)) ALSO NEW_LINE DONE
    LOG (3_sym * sqrt(x_sym)  - x_sym - sqrt(x_sym) + 3_sym * x_sym * 3_sym * x_sym) - sqrt(x_sym) + x_sym*x_sym + x_sym ALSO NEW_LINE DONE
    LOG (2_sym * 5_sym * x_sym * x_sym + sqrt(x_sym)) ALSO NEW_LINE DONE
    LOG_SECTION("SYMBOLIC MATH 2")
    LOG ((x_sym + sin(x_sym))*(1_sym - cos(x_sym)) - x_sym + sin(x_sym)*cos(x_sym)) ALSO NEW_LINE DONE
    LOG (sin(x_sym) - x_sym * cos(x_sym)) DONE
    LOG_SECTION("SYMBOLIC MATH 3")
    LET q_sym = ((cos(x_sym) + sin(x_sym))*(cos(x_sym) + sin(x_sym))) DONE
    q_sym.logmap();
    LOG simplify((cos(x_sym) + sin(x_sym))*(cos(x_sym) + sin(x_sym)) + x_sym*3_sym + 6_sym) ALSO NEW_LINE DONE
    LOG_SECTION("SYMBOLIC MATH 4")
    LOG simplify(5 * cos(x_sym) * cos(x_sym) + sin(x_sym)*sin(x_sym)) NEAR 5 * cos(x_sym) * cos(x_sym) + sin(x_sym)*sin(x_sym) DONE
    LOG_SECTION("SYMBOLIC MATH 5")
    LOG (sqrt(3_sym) + 5)*x_sym - x_sym * 2 * sqrt(3_sym) - (3 - sqrt(3_sym))*x_sym DONE
        LOG_SECTION("SYMBOLIC MATH 6")

    LOG replacevar(x_sym, {"x", "a"}) ALSO NEW_LINE DONE
    LET r_sym = x_sym*4*2*(3*x_sym*b_sym);
    r_sym.logmap();
        LOG_SECTION("rRSYM")

    LET rr_sym = 2_sym*x_sym*x_sym*3*4*b_sym;

    rr_sym.logmap();
    LOG_SECTION("RSYM")
    LOG r_sym ALSO NEW_LINE ALSO rr_sym  NEAR (x_sym*(x_sym*x_sym*x_sym)* (x_sym * b_sym)) NEAR (x_sym*x_sym*x_sym*x_sym* (x_sym * b_sym))  NEAR (x_sym * b_sym) ALSO NEW_LINE DONE
    LOG x_sym*1_sym*1_sym END_LINE
    (x_sym*1_sym*1_sym).logmap();
    LOG_SECTION("1")
        (x_sym * b_sym).logmap();
            LOG_SECTION("7")

(x_sym*x_sym*x_sym*x_sym* (x_sym * b_sym)).logmap();
// sin((x_sym*x_sym*x_sym*x_sym* (x_sym * b_sym)).strip().strip()).logmap();

// (5_sym* (x_sym * b_sym)).logmap();

// (x_sym * 2_sym).logmap();


    LOG sin(2 * x_sym + cos(x_sym)) ALSO NEW_LINE DONE
    LOG 2 * x_sym + cos(x_sym) ALSO NEW_LINE DONE
    LOG ( (x_sym * b_sym) + (2_sym * 3_sym) + (2_sym * x_sym) + (x_sym * 7_sym) + (x_sym * 2_sym * b_sym + 5_sym)) ALSO NEW_LINE DONE

    LOG (x_sym + x_sym*x_sym).ring_elements.begin()->first.func DONE
    LOG_SECTION("SYMM")
    LET w_sym = (x_sym * x_sym) ;
    w_sym.logmap();
    LOG (x_sym * x_sym)*(b_sym) ALSO NEW_LINE DONE
    LOG_SECTION("KJGJGKJGKJHKJFKJHG")
    HSymbolic g_sym = (x_sym * x_sym)*(b_sym);
     LOG "ksym";
        LOG g_sym ALSO NEW_LINE DONE
    LOG_SECTION("HEYYYAYY")
    LOG SYM _ to_clean_string((x_sym)*(cos(b_sym)*(cos(b_sym)) + sin(b_sym)*sin(b_sym))) END_LINE
    LOG SYM _ to_clean_string(x_sym + b_sym + g_sym) END_LINE
    LOG (g_sym + b_sym + x_sym) END_LINE
    LOG ((x_sym ) / (x_sym* b_sym)) END_LINE
    (x_sym + w_sym + g_sym + b_sym).logmap();
    LOG (x_sym + w_sym + g_sym + b_sym) END_LINE
    LOG (x_sym).inv() NEAR (x_sym * b_sym * x_sym).inv() ENDL
    LOG (x_sym * x_sym).inv() NEAR x_sym.inv() ENDL
    LOG_SECTION("AJJAJA")
    LOG (3_sym * 2_sym + x_sym * g_sym )/(x_sym) ENDL
    LOG (6_sym * g_sym)/(x_sym * x_sym * g_sym * (x_sym+b_sym)) * x_sym + g_sym ENDL
    LOG (x_sym + b_sym).inv() ENDL
    (x_sym + b_sym).inv().logmap();

    (x_sym * x_sym * g_sym * (x_sym+b_sym)).inv().logmap();
    (x_sym * x_sym * g_sym * (x_sym+b_sym)).logmap();
    LOG (x_sym * x_sym * g_sym * (x_sym+b_sym)) ENDL
    LET e_sym = (x_sym + b_sym) * (x_sym + b_sym) ;
    LOG e_sym NEAR SYM _ to_string(e_sym.inv()) NEAR e_sym.inv().inv() ENDL
    (e_sym).logmap();
    (e_sym).inv().logmap();
    (e_sym).inv().inv().logmap();
    (e_sym).inv().inv().inv().logmap();
    (e_sym).inv().inv().inv().inv().logmap();
     // LOG (mvef _ plain) (SYM _ to_mve(e_sym.inv())) ENDL
    //  LOG (x_sym * x_sym).strip()*(x_sym*x_sym).strip() ENDL
    LOG_SECTION("JKJKJKKJK")
 
    LOG SYM _ to_clean_string((x_sym * b_sym * x_sym) / (e_sym)) ENDL
    LOG SYM _ to_clean_string((x_sym*x_sym)/e_sym * (b_sym + x_sym ) ) ENDL
    LOG (x_sym*x_sym)/e_sym ENDL
    LOG x_sym.inv() * x_sym.inv().inv() ENDL
    // x_sym = x_sym * b_sym;
        LOG_SECTION("JKJKJKKJK")

    LOG x_sym ENDL
    LOG x_sym.inv() ENDL
    x_sym.logmap();
    LOG x_sym.ismultiply_ring() NEAR x_sym.val() NEAR "Lol" ENDL
    x_sym.logmap();
    x_sym.inv().logmap();

    x_sym.inv().inv().logmap();
    LOG x_sym.inv().inv() + x_sym ENDL
    x_sym.inv().inv().inv().logmap();
    x_sym.inv().inv().inv().inv().logmap();

    (x_sym.inv().inv().inv() + x_sym).logmap();
    LOG (x_sym + b_sym)*(x_sym + b_sym) - 2*x_sym * b_sym ENDL
    LOG PLAIN(sin(x_sym + x_sym) * (b_sym + e_sym)) ENDL
    LOG sin(x_sym + x_sym).ismultiply_ring() NEAR b_sym.ismultiply_ring() ENDL
    LOG PLAIN(sin (x_sym + x_sym) * b_sym) ENDL
    LOG PLAIN(sin (x_sym + b_sym) * b_sym - (b_sym + x_sym)*sin(b_sym + x_sym)) ENDL
    //(sin (x_sym + x_sym) * b_sym - (b_sym + x_sym)*sin(b_sym + x_sym)).logmap();
    LOG PLAIN((b_sym + x_sym)*sin(b_sym + x_sym)) ENDL
    LOG PLAIN((b_sym * x_sym + x_sym * x_sym)/x_sym/(b_sym + x_sym)) ENDL
    LOG PLAIN(x_sym + x_sym * g_sym / b_sym + (b_sym + g_sym)/b_sym + 1 - (x_sym + 1 + x_sym*(x_sym + 1)*x_sym)) ENDL
    LOG PLAIN(x_sym + 1 + x_sym*(x_sym + 1)*x_sym) ENDL
    // LOG x_sym.inv() ENDL
    // LOG x_sym ENDL
    // (2_sym * x_sym * x_sym).logmap();
    // (x_sym * x_sym).logmap();
    // LOG (x_sym * x_sym * 2_sym).strip().f("").hug()/(b_sym + x_sym) ENDL
    // ((x_sym*x_sym)/e_sym * (b_sym._getv())).strip().logmap();
    // LOG SYM _ to_clean_string ((2_sym *x_sym*x_sym)/e_sym * (b_sym + x_sym) ) ENDL
    //  // LOG SYM _ to_clean_string((e_sym.inv() * (x_sym * x_sym)).inv()) ENDL
    // LOG (2* x_sym * x_sym)*x_sym/x_sym ENDL
    //     LOG (2 * x_sym * x_sym)*(b_sym + x_sym) ENDL

    // LOG (2 * x_sym * x_sym) ENDL

    LOG_SECTION("PLAY")
    LET y_ =  REAL100(2.31222);
    LET y2_ = REAL100(1.233333);
    LOG REAL100_FNS _ sin(y_) ENDL

    LOG PLAIN(x_sym + 2 - x_sym * x_sym + (x_sym + b_sym)*(b_sym - x_sym)) ENDL


    LOG_SECTION("TESTING AAAAAAAAAAAA")

    HSymbolic maria_sym = HSymbolic("x");
    LOG PLAIN(maria_sym + 2 * maria_sym * (maria_sym + 1) - 3 * maria_sym) ENDL

    std::vector<long double> tensor1_values_db = {1.1, 2.0, 3.2, 5.0, 6.2, 4.2, 8.8, 5.0, 8.3};
    std::vector<long double> tensor2_values_db = {-1.4, 1.0, 7.2, 5.7, 6.72, 4.62, 8.850, 7.7, 5.760};

    
    HTensor<long double> tensor1_db(tensor1_values_db, MATRIX_3X3);
    HTensor<long double> tensor2_db(tensor2_values_db, MATRIX_3X3);

    HTensor<long double> tensorproduct_db = HTensor<long double>::tensor_product(tensor1_db, tensor2_db);

    std::vector<REAL100> tensor1_values = {1.1_big, 2.0_big, 3.2_big, 5.0_big, 6.2_big, 4.2_big, 8.8_big, 5.0_big, 8.3_big};
    std::vector<REAL100> tensor2_values = {-1.4_big, 1.0_big, 7.2_big, 5.7_big, 6.72_big, 4.62_big, 8.850_big, 7.7_big, 5.760_big};

    
    HTensor<REAL100> tensor1(tensor1_values, MATRIX_3X3);
    HTensor<REAL100> tensor2(tensor2_values, MATRIX_3X3);

    HTensor<REAL100> tensorproduct = HTensor<REAL100>::tensor_product(tensor1, tensor2);


    FOREACH(i, indices, IN_TENSOR, tensorproduct, 
        LOG tensorproduct.at(indices) NEAR tensorproduct_db.at(indices) NEAR "" DONE
    )


    HEinsteinNotation<REAL100> einstein_notation_tensor1 = __(tensor1, "^alpha_beta");
    HEinsteinNotation<REAL100> einstein_notation_tensor2 = __(tensor2, "^beta_gamma");

    HEinsteinNotation<REAL> einstein_notation_tensor1_db = __(tensor1_db, "^alpha_beta");
    HEinsteinNotation<REAL> einstein_notation_tensor2_db = __(tensor2_db, "^beta_gamma");


    LOG_SECTION("REAL100-TENS-PRODS");

    //std::cout<<(bigreal("0") * 2.3_big)<<"\n";

    // FOREACH(i, indices, IN_TENSOR, einstein_notation_tensorprod_db.tensor, 
    //     LOG einstein_notation_tensorprod_db.at(indices) NEAR "real_" DONE
    //     if(i > 9) break;
    // )
    HEinsteinNotation<REAL> einstein_notation_tensorprod_db = __m(einstein_notation_tensor1_db, einstein_notation_tensor2_db);
    HEinsteinNotation<REAL100> einstein_notation_tensorprod = einstein_notation_tensor1 * einstein_notation_tensor2;

    printf("done\n");

    //HEinsteinNotation<REAL100> einstein_notation_tensorprod = __m(einstein_notation_tensor1, einstein_notation_tensor2);

    FOREACH(i, indices, IN_TENSOR, einstein_notation_tensorprod_db.tensor, 
        LOG einstein_notation_tensorprod_db.at(indices) ALSO " " DONE
        if(i%3 == 2) LOG "\n" DONE
    )
     return 0;

}


 
