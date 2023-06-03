#ifndef FCO_H
#define FCO_H

#include "exprev.h"
#include <functional>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

/**
 * @brief Types of derivatives.
 * O6 - is the less precise one
 * SL - At left
 * SR - At right
 * SLR - Left-right
 * 
 */
enum DerivType {FCO_DERIV_1VF_O6 = 0, FCO_DERIV_1VF_SL, FCO_DERIV_1VF_SR, FCO_DERIV_1VF_SLR};

/**
 * @brief Interval to be used in calculating the S-type derivative
 * 
 */
inline long double __DX = 1e-6;
/**
 * @brief Interval to be used in calculating the O6-type derivative
 * 
 */
inline long double __DXO6 = 1e-6;

/**
 * @brief O6 method derivative for 1 variable function. Isn't quite as accurate as SL, SLR and SR
 * 
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */

inline long double fco_derivativeO6_1VFC(fptrldb _fun, long double __x){
    long double dx1 = __DXO6;
    long double dx2 = dx1*2.0;
    long double dx3 = dx1*3.0;

    long double m1 = (long double)(_fun(__x + dx1) - _fun(__x - dx1))/2.0;
    long double m2 = (long double)(_fun(__x + dx2) - _fun(__x - dx2))/4.0;
    long double m3 = (long double)(_fun(__x + dx3) - _fun(__x - dx3))/6.0;

    return ((15.0 * m1 - 6.0*m2) + m3)/ (10.0 * ((__x+dx1) - (__x)));

}
/**
 * @brief Left derivative for 1 variable functions
 * 
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
inline long double fco_derivativeSL_1VFC(fptrldb _fun, long double __x){
    long double dx1 = __DX;


    long double m1 = (long double)(_fun(__x + dx1) - _fun(__x));

    return m1/((__x + dx1) - (__x));

}
/**
 * @brief Right derivative for 1 variable function
 * 
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
inline long double fco_derivativeSR_1VFC(fptrldb _fun, long double __x){
    long double dx1 = __DX;


    long double m1 = (long double)(_fun(__x ) - _fun(__x - dx1));

    return m1/((__x)  - (__x - dx1));

}
/**
 * @brief Left-right derivative for 1 variable function
 * 
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
inline long double fco_derivativeSLR_1VFC(fptrldb _fun, long double __x){
    long double dx1 = __DX;


    long double m1 = (long double)(_fun(__x + dx1) - _fun(__x - dx1))/((__x + dx1) - (__x - dx1));

    return m1;

}


/**
 * @brief O6 Derivative for Lambda
 * 
 * @tparam FLAMBDA Lambda (auto)
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
template<typename FLAMBDA>
inline long double fco_derivativeLambdaO6_1VFC(FLAMBDA &_fun, long double __x){
    long double dx1 = __DXO6;
    long double dx2 = dx1*2.0;
    long double dx3 = dx1*3.0;

    long double m1 = (long double)(_fun(__x + dx1) - _fun(__x - dx1))/2.0;
    long double m2 = (long double)(_fun(__x + dx2) - _fun(__x - dx2))/4.0;
    long double m3 = (long double)(_fun(__x + dx3) - _fun(__x - dx3))/6.0;

    return ((15.0 * m1 - 6.0*m2) + m3)/ (10.0 * ((__x+dx1) - (__x)));

}
/**
 * @brief Left Derivative for Lambda
 * 
 * @tparam FLAMBDA Lambda (auto)
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
template<typename FLAMBDA>
inline long double fco_derivativeLambdaSL_1VFC(FLAMBDA &_fun, long double __x){
    long double dx1 = __DX;


    long double m1 = (long double)(_fun(__x + dx1) - _fun(__x));

    return m1/((__x + dx1) - (__x));

}
/**
 * @brief Right Derivative for Lambda
 * 
 * @tparam FLAMBDA Lambda (auto)
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
template<typename FLAMBDA>
inline long double fco_derivativeLambdaSR_1VFC(FLAMBDA &_fun, long double __x){
    long double dx1 = __DX;


    long double m1 = (long double)(_fun(__x ) - _fun(__x - dx1));

    return m1/((__x)  - (__x - dx1));

}
/**
 * @brief Left-right Derivative for Lambda
 * 
 * @tparam FLAMBDA Lambda (auto)
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
template<typename FLAMBDA>
inline long double fco_derivativeLambdaSLR_1VFC(FLAMBDA &_fun, long double __x){
    long double dx1 = __DX;


    long double m1 = (long double)(_fun(__x + dx1) - _fun(__x - dx1))/((__x + dx1) - (__x - dx1));

    return m1;

}





/**
 * @brief Sets the precision of the derivative __DX constant 
 * @param precision The precision to be set 
 */
inline void fco_config__DX_Precision(long double precision){
    __DX = 1.0/precision;
}
/**
 * @brief Sets the precision of the derivative __DXO6 constant 
 * @param precision The precision to be set 
 */
inline void fco_config__DXO6_Precision(long double precision){
    __DXO6 = 1.0/precision;
}

/**
 * @brief Config epsilons default values
 * 
 */

inline void fco_config__Precisions(){
    fco_config__DX_Precision(1e6);
    fco_config__DXO6_Precision(1e6);
}
/**
 * @brief Increase precision by a factor of 10^factor
 * 
 */
inline void fco_increasePrecision_ln(int factor){
    __DX /= (long double)pow(10.0, (long double) factor);
    __DXO6 /=(long double)pow(10.0, (long double) factor);
}
/**
 * @brief Best default settings overall
 * 
 */
inline void fco_default__PrecisionSettings(){

    fco_config__Precisions();
    fco_increasePrecision_ln(5);
}


/**
 * @brief Error in calculation of the derivatives. Taken as the square-deviation of all 4 posiible calculations.
 * Does not represent the error in calculation!
 * 
 * @param _fun 
 * @param __x Value to be calculated at
 * @return long double 
 */
inline long double fco_calc__DerivError(fptrldb _fun, long double __x){

    long double _O6 = fco_derivativeO6_1VFC(_fun, __x);
    long double _SL = fco_derivativeSL_1VFC(_fun, __x);
    long double _SR = fco_derivativeSR_1VFC(_fun, __x);
    long double _SLR = fco_derivativeSLR_1VFC(_fun, __x);

    long double mean = 0.25*(_O6 + _SL + _SR + _SLR);

    long double _2O6 = (_O6 - mean)*(_O6 - mean);
    long double _2SL = (_SL - mean)*(_SL - mean);
    long double _2SR = (_SR - mean)*(_SR - mean);
    long double _2SLR = (_SLR - mean)*(_SLR  - mean);

    return sqrt(0.25*(_2O6 + _2SL + _2SLR + _2SR));
}
/**
 * @brief Puts in _sol_attay all numbers that are in the given interval [_BEGIN, _END] and give an absolute value less than __epsilon when passed as a parameter to the function _fun.
 * !!USE fco_calc__SolutionsForFunction for accurate and reliable solutions!!
 * @param _fun Function
 * @param _BEGIN Minimum of the interval in which solutions should be sought
 * @param _END Maximum of the interval in which solutions should be sought
 * @param __d_interval Distance at which the values are collected (step)
 * @param __epsilon Maximum tollerance
 * @param _sol_array OUT -> Solutons
 * @param _out_solnr OUT -> Number of solutions
 */
inline void fco_get_functionAproxSolutions(fptrldb _fun, long double _BEGIN, long double _END, long double __d_interval, long double __epsilon, long double _sol_array[], int &_out_solnr){
    long int  _s_it=0;
    double x_it;
    x_it = _BEGIN;
    while(x_it <= _END){
        if(std::abs(_fun(x_it)) <= __epsilon){
            
            _sol_array[_s_it] = x_it;

            _s_it++;
        }
        x_it += __d_interval;
    }
    _out_solnr = _s_it;
}
/**
 * @brief Puts in _sol_attay all numbers that are in the given interval [_BEGIN, _END] and give an absolute value less than __epsilon when passed as a parameter to the lambda function _fun.
 * !!USE fco_calc__SolutionsForLambda for accurate and reliable solutions!!
 * (Lambda alternative for fco_get_functionAproxSolutions)
 * @tparam FLAMBDA Lambda (auto)
 * @param _fun Lambda
 * @param _BEGIN Minimum of the interval in which solutions should be sought
 * @param _END Maximum of the interval in which solutions should be sought
 * @param __d_interval Distance at which the values are collected (step)
 * @param __epsilon Maximum tollerance
 * @param _sol_array OUT -> Solutons
 * @param _out_solnr OUT -> Number of solutions
 */
template<typename FLAMBDA>
inline void fco_get_functionAproxSolutionsForLambda(FLAMBDA &_fun, long double _BEGIN, long double _END, long double __d_interval, long double __epsilon, long double _sol_array[], int &_out_solnr){
    long int  _s_it=0;
    double x_it;
    x_it = _BEGIN;
    while(x_it <= _END){
        if(std::abs(_fun(x_it)) <= __epsilon){
            
            _sol_array[_s_it] = x_it;

            _s_it++;
        }
        x_it += __d_interval;
    }
    _out_solnr = _s_it;
}
/**
 * @brief Iterates newton method for each element of __aprox_sols and spits out the result in __finalArray.
 * This is used to get the aproximate solutions to a more accurate form
 * @param D_TYPE Type of derivative used - SLR reccomended for continous functions
 * @param _fun Function
 * @param __sol_num Number of elements in __aprox_sols
 * @param __aprox_sols Array of numbers for which Newton's method is applied
 * @param iterations Number of iterations
 * @param __finalArray OUT -> Resulting array (has the same length as the initial array __aprox_sols)
 */
inline void fco_get_newtonsMethod(DerivType D_TYPE, fptrldb _fun, long int __sol_num ,long double* __aprox_sols, long int iterations, long double* __finalArray){
    
    for(int it = 0; it <__sol_num; ++it){
        long double _vx = __aprox_sols[it];
        long double _vx_betterAprox = _vx;

        for(int _i = 0; _i <iterations; _i++){
            switch (D_TYPE)
            {
            case FCO_DERIV_1VF_O6:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeO6_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SL:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeSL_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SR:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeSR_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SLR:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeSLR_1VFC(_fun, _vx_betterAprox);
                break;
            
            default:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeSLR_1VFC(_fun, _vx_betterAprox);            
                break;
            }

        }
        __finalArray[it] = _vx_betterAprox;

    }

}
/**
 * @brief Does the same as fco_get_newtonsMethod but takes a lambda instead of a function pointer as parameter
 * 
 * @tparam FLAMBDA Lambda 
 * @param D_TYPE Type of derivative used - SLR reccomended for continous functions
 * @param _fun Lambda
 * @param __sol_num Number of elements in __aprox_sols
 * @param __aprox_sols Array of numbers for which Newton's method is applied
 * @param iterations Number of iterations
 * @param __finalArray OUT -> Resulting array (has the same length as the initial array __aprox_sols)
 */
template<typename FLAMBDA>
inline void fco_get_newtonsMethodForLambda(DerivType D_TYPE, FLAMBDA& _fun, long int __sol_num ,long double* __aprox_sols, long int iterations, long double* __finalArray){
    
    for(int it = 0; it <__sol_num; ++it){
        long double _vx = __aprox_sols[it];
        long double _vx_betterAprox = _vx;

        for(int _i = 0; _i <iterations; _i++){
            switch (D_TYPE)
            {
            case FCO_DERIV_1VF_O6:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeLambdaO6_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SL:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeLambdaSL_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SR:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeLambdaSR_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SLR:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeLambdaSLR_1VFC(_fun, _vx_betterAprox);
                break;
            
            default:
                _vx_betterAprox = _vx_betterAprox - _fun(_vx_betterAprox)/fco_derivativeLambdaSLR_1VFC(_fun, _vx_betterAprox);            
                break;
            }

        }
        __finalArray[it] = _vx_betterAprox;

    }

}
/**
 * @brief Iterates Newtons method for a single variable: _vx_betterAprox and then returns it.
 * 
 * @param D_TYPE Type of derivative to be used
 * @param _fun Function used
 * @param iter Number of iterations
 * @param _vx_betterAprox Variable to be iterated
 * @return long double 
 */
inline long double fco_iterateNewtonMethodForVariable(DerivType D_TYPE, fptrldb _fun, int iter, long double _vx_betterAprox){

    for(int it=0;it<iter;++it){
        switch (D_TYPE)
            {
            case FCO_DERIV_1VF_O6:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeO6_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SL:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeSL_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SR:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeSR_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SLR:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeSLR_1VFC(_fun, _vx_betterAprox);
                break;
            
            default:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeSLR_1VFC(_fun, _vx_betterAprox);            
                break;
            }
    }

    return _vx_betterAprox;
    
}
/**
 * @brief Iterates Newtons method for a single variable: _vx_betterAprox and then returns it.
 * 
 * @tparam FLAMBDA 
 * @param D_TYPE Type of derivative to be used
 * @param _fun Lambda used
 * @param iter Number of iterations
 * @param _vx_betterAprox Variable to be iterated
 * @return long double 
 */
template<typename FLAMBDA>
inline long double fco_iterateNewtonMethodForVariableForLambda(DerivType D_TYPE, FLAMBDA &_fun, int iter, long double _vx_betterAprox){

    for(int it=0;it<iter;++it){
        switch (D_TYPE)
            {
            case FCO_DERIV_1VF_O6:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeLambdaO6_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SL:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeLambdaSL_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SR:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeLambdaSR_1VFC(_fun, _vx_betterAprox);
                break;
            case FCO_DERIV_1VF_SLR:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeLambdaSLR_1VFC(_fun, _vx_betterAprox);
                break;
            
            default:
                _vx_betterAprox -= _fun(_vx_betterAprox)/fco_derivativeLambdaSLR_1VFC(_fun, _vx_betterAprox);            
                break;
            }
    }

    return _vx_betterAprox;
    
}
/**
 * @brief Rounds __x to a given decimal position so that it has only dec decimals left.
 * 
 * @param dec 
 * @param __x 
 * @return long double 
 */
inline long double roundToDecimal(int dec, long double __x){
    long double _pw = pow(10.0, (long double) dec);
    long double value = std::round( __x * _pw ) / _pw;
    return value;
}
/**
 * @brief Gets rid of close values in a given array then iterates again using Newtons methos.
 * 
 * @param _D_TYPE Derivative type to be used
 * @param _fun Function used
 * @param _newton_array Initial aray - NEEDS TO BE INCREASING
 * @param _length Initial length of the array
 * @param _threshold If two values are closer than a given threshold, one is deleted
 * @param _reiterate How many tims to reiiterate Newton's method
 * @param __get_array OUT -> Resulting array
 * @param __get_lentgh OUT-> Resulting length (i misspelled :P)
 */
inline void fco_beautifyNewtonIncreasingArray(DerivType _D_TYPE, fptrldb _fun,long double* _newton_array, int _length, long double _threshold, int _reiterate, long double *__get_array, int &__get_lentgh){
    int _del = 0;
    __get_lentgh = 0;
    for(int it = 0; it<_length;++it){
        if(it>0 &&  std::abs(_newton_array[it] - _newton_array[it-1]) <= (_newton_array[it]+ + _threshold)- _newton_array[it]  ){
            //delete it - 1
            _del ++;
        } else {
            __get_array[__get_lentgh] = _newton_array[it];
            __get_lentgh++;

        }
    }

    for(int it = 0; it <__get_lentgh;++it){
        __get_array[__get_lentgh] = fco_iterateNewtonMethodForVariable(_D_TYPE, _fun, _reiterate, __get_array[__get_lentgh]);
    }
}
/**
 * @brief Gets rid of close values in a given array then iterates again using Newtons methos.
 * 
 * @tparam FLAMBDA Lambda (auto)
 * @param _D_TYPE Derivative type to be used
 * @param _fun Lambda used
 * @param _newton_array Initial aray - NEEDS TO BE INCREASING
 * @param _length Initial length of the array
 * @param _threshold If two values are closer than a given threshold, one is deleted
 * @param _reiterate How many tims to reiiterate Newton's method
 * @param __get_array OUT -> Resulting array
 * @param __get_lentgh OUT-> Resulting length (i misspelled :P)
 */
template<typename FLAMBDA>
inline void fco_beautifyNewtonIncreasingArrayForLambda(DerivType _D_TYPE, FLAMBDA &_fun,long double* _newton_array, int _length, long double _threshold, int _reiterate, long double *__get_array, int &__get_lentgh){
    int _del = 0;
    __get_lentgh = 0;
    for(int it = 0; it<_length;++it){
        if(it>0 &&  std::abs(_newton_array[it] - _newton_array[it-1]) <= (_newton_array[it]+ + _threshold)- _newton_array[it]  ){
            //delete it - 1
            _del ++;
        } else {
            __get_array[__get_lentgh] = _newton_array[it];
            __get_lentgh++;

        }
    }

    for(int it = 0; it <__get_lentgh;++it){
        __get_array[__get_lentgh] = fco_iterateNewtonMethodForVariableForLambda(_D_TYPE, _fun, _reiterate, __get_array[__get_lentgh]);
    }
}

/**Default Step used to sample values. Smaller: -> helps find more solutions*/
inline long double FCO_FSOL_PARAM_STEP = 0.001;
/**How close can initial solutions be to 0: higher -> helps find more solutions*/
inline long double FCO_FSOL_PARAM_DELTAF = 0.01;

/**Interval at which 2 values are considered the same solution.*/
inline long double FCO_FSOL_PARAM_MAXIDEN = 1e-7;
/**How many times to iterate Newton's Method*/
inline int FCO_FSOL_PARAM_NEWTONITERATIONS = 4000;

/**How many times to reiterate Newton's Method after beautifying the solution-array*/
inline int FCO_FSOL_PARAM_NEWTONREITERATIONS = 1200;
/**
 * @brief Calculates solutions of _fun in a given interval. Can give more solutions close to S when the function is flat in the vecinity of S. For example at x^2 you can get -3.0009e-5 and 0.
 * 
 * @param _D_TYPE Type of derivative to be used in calculations. Recommended: SLR
 * @param _fun Function 
 * @param range_min Min of the interval (range)
 * @param range_max Max of the interval (range)
 * @param solutions OUT -> Solutions
 * @param sol_nr OUT -> Number of solutions
 */
inline void fco_calc__SolutionsForFunction(DerivType _D_TYPE, fptrldb _fun, long double range_min, long double range_max, long double* solutions, int& sol_nr){
    long double aproxSols[MAX];
    int aproxSolsNumber;
    fco_get_functionAproxSolutions(_fun, range_min, range_max, FCO_FSOL_PARAM_STEP, FCO_FSOL_PARAM_DELTAF, aproxSols, aproxSolsNumber);
    
    long double sols[MAX]; //Un-beautified
    fco_get_newtonsMethod(FCO_DERIV_1VF_SLR, _fun, aproxSolsNumber, aproxSols, FCO_FSOL_PARAM_NEWTONITERATIONS, sols);

    fco_beautifyNewtonIncreasingArray(FCO_DERIV_1VF_SLR, _fun, sols, aproxSolsNumber, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArray(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArray(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArray(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArray(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);

}
/**
 * @brief Calculates solutions in a given interval. Can give more solutions close to S when the function is flat in the vecinity of S. For example at x^2 you can get -3.0009e-5 and 0.
 * Lambda alternative to fco_calc__SolutionsForFunction
 * @tparam FLAMBDA Lambda (auto)
 * @param _D_TYPE Type of derivative to be used in calculations. Recommended: SLR
 * @param _fun Lambda
 * @param range_min Min of the interval (range)
 * @param range_max Max of the interval (range)
 * @param solutions OUT -> Solutions
 * @param sol_nr OUT -> Number of solutions
 */
template<typename FLAMBDA>
inline void fco_calc__SolutionsForLambda(DerivType _D_TYPE, FLAMBDA &_fun, long double range_min, long double range_max, long double* solutions, int& sol_nr){
    long double aproxSols[MAX];
    int aproxSolsNumber;
    fco_get_functionAproxSolutionsForLambda(_fun, range_min, range_max, FCO_FSOL_PARAM_STEP, FCO_FSOL_PARAM_DELTAF, aproxSols, aproxSolsNumber);
    
    long double sols[MAX]; //Un-beautified
    fco_get_newtonsMethodForLambda(FCO_DERIV_1VF_SLR, _fun, aproxSolsNumber, aproxSols, FCO_FSOL_PARAM_NEWTONITERATIONS, sols);

    fco_beautifyNewtonIncreasingArrayForLambda(FCO_DERIV_1VF_SLR, _fun, sols, aproxSolsNumber, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArrayForLambda(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArrayForLambda(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArrayForLambda(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);
    fco_beautifyNewtonIncreasingArrayForLambda(FCO_DERIV_1VF_SLR, _fun, solutions, sol_nr, FCO_FSOL_PARAM_MAXIDEN, FCO_FSOL_PARAM_NEWTONREITERATIONS, solutions, sol_nr);

}

/**
 * @brief Nth derivative of _fun calculated at value _x. TODO: Add a lambda alternative
 * 
 * @param _D_TYPE Type of derivative. O6 - not accepted
 * @param _fun 
 * @param _x 
 * @param n 
 * @return long double 
 */
inline long double fco_calc__NthDerivative(DerivType _D_TYPE, fptrldb _fun, long double _x, int n){
    

    long double x1 = _x - __DX;
    long double x2 = _x + __DX;

    switch (_D_TYPE)
    {
    case FCO_DERIV_1VF_O6:
        throw std::invalid_argument("Type O6 is not supported for this function, try using 'fco_derivativeO6_1VFC'");
        break;
    case FCO_DERIV_1VF_SL:
        x1 = _x;
        break;
    case FCO_DERIV_1VF_SR:
        x2 = _x;
        break;
    case FCO_DERIV_1VF_SLR:
        break;
    default:
        break;
    }

    if(n == 1){
        long double y1 = _fun(x1);
        long double y2 = _fun(x2);

        return (y2 - y1) / (x2 - x1);
    } else {


        long double y1 = fco_calc__NthDerivative(_D_TYPE ,_fun, x1, n - 1);

        long double y2 = fco_calc__NthDerivative(_D_TYPE ,_fun, x2, n - 1);
     //   std::cout<<"f'>"<<n-1<<": "<<y1<<" "<<y2<<" -= "<<y2-y1<<"\n";

        return (y2 - y1) / (x2 - x1);
    }
}
/**
 * @brief Nth derivative of _fun calculated at _x
 * 
 * @param _fun 
 * @param _x 
 * @param n 
 * @return long double 
 */
inline long double fco_calc__NthDerivativeSLR(fptrldb _fun, long double _x, int n){
    fco_config__Precisions();
    fco_increasePrecision_ln(0);

    long double x1 = _x - __DX*(long double)n;
    long double x2 = _x + __DX*(long double)n;


    if(n == 1){
        long double y1 = _fun(x1);
        long double y2 = _fun(x2);

        return (y2 - y1) / (x2 - x1);
    } else {


        long double y1 = fco_calc__NthDerivativeSLR(_fun, x1, n - 1);

        long double y2 = fco_calc__NthDerivativeSLR(_fun, x2, n - 1);
     //   std::cout<<"f'>"<<n-1<<": "<<y1<<" "<<y2<<" -= "<<y2-y1<<"\n";

        return (y2 - y1) / (x2 - x1);
    }
}

/** Remez poly*/
/**Maximum degree of the remez polynomial and remez A-Matrix*/
#define N_MAX 100

/**
 * @brief Minor matrix of a matrix (A)
 * NOT USABLE!
 * @deprecated Slow and does not work :(
 * @param A 
 * @param temp 
 * @param p 
 * @param q 
 * @param n 
 */
inline void fco_matrsq__getMinorMatrix(long double A[N_MAX][N_MAX], long double temp[N_MAX][N_MAX], int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j] = A[row][col];
                j++;
                if (j == n )
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 


/**
 * @brief Returns the inverse of A
 * 
 * @param A 
 * @param inverse 
 * @param n dimension of the matrix A
 */
inline void fco_matrsq__inverse(long double A[N_MAX][N_MAX], long double inverse[N_MAX][N_MAX], int n)
{
    // std::cout<<"\nBegin\n";
    long double x[N_MAX], ratio;
    /*Create Augmented matrix*/
    long double AUG[N_MAX][N_MAX*2];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            AUG[i][j] = A[i][j];
            if(i==j){
                AUG[i][j+n] = 1;
            }
            else{
                AUG[i][j+n] = 0;
            }
        }
    }

    /*Gauss Jordan*/
    for(int i=0;i<n;++i){
        if(AUG[i][i] == 0.0){
            throw std::invalid_argument("Error");
        }
        for(int j=0;j<n;++j){
            if(i!=j){
                ratio = AUG[j][i]/AUG[i][i];
                for(int k=0;k<2*n;++k){
                    AUG[j][k] -=ratio*AUG[i][k];
                }

            }
        }
    }

    /*Diag* = I_n*/

    for(int i=0;i<n;++i){
        for(int j=n; j<2*n;++j){
            AUG[i][j] = AUG[i][j]/AUG[i][i];
        }
    }

    for(int i=0;i<n;++i){
        for(int j=n; j<2*n;++j){
            inverse[i][j-n] = AUG[i][j];
        }
    }

}
/**
 * @brief Calculates the Remez polynomial aof a function in a given interval [a,b] and stores it in an array (out_polyarr)
 * 
 * @param second_it If true: it runs for a second iteration. TAKES A LOT. Set it to false <- recommended. The second iteration does not yet work properly
 * @param _fun Function
 * @param a Interval min
 * @param b Interval max
 * @param n Degree the polynomial should be. Recommended: ~20-25
 * @param err_threshold This param is not yet used!
 * @param out_polyarr OUT -> Remez Polynomial array
 * @param length OUT -> Length of the polyarray
 * @param calc_err OUT -> error in calculation
 */
inline void fco_calc__RemezPolyArray(bool second_it ,fptrldb _fun, long double a, long double b, const int n,  long double err_threshold, long double* out_polyarr, int& length, long double& calc_err){
    long double initialerror = 0;
    //Calculate cauchy nodes
    long double cebyshevNodes[n+2];
    // std::cout<<"\nCebyshev: \n";
    for(int i=1; i<= n+2; ++i){
        cebyshevNodes[i-1] = 0.5* ((a+b) + (b-a)*cos(CONSTANT_PI*(2*i-1)/((long double)2*(n+2))));
        // std::cout<<cebyshevNodes[i-1]<<"  ";
    }
    long double mak[N_MAX][N_MAX], inv[N_MAX][N_MAX];
    for(int j=0;j <= n+1; ++j){
        long double p=1;
        for(int i=0;i<=n+1; ++i){
                mak[j][i] = p;
                p*=cebyshevNodes[j]; 
            
        }
    }
    long double p=1;
    for(int i=0;i<=n+1;++i){
        mak[i][n+1] = p;
        p=-p;
    }
   

    fco_matrsq__inverse(mak, inv, n+2);

    

    /*INV * _FUN(x((i)))^ */

    long double coeffs[n+2];

    /**coeffs[n+1] will be E*/
    for(int i=0;i<=n+1; i++){
        coeffs[i] = 0;
    }
    for(int i=0;i<=n+1; i++){
        for(int j=0;j<=n+1;++j){
            
            coeffs[i] +=_fun(cebyshevNodes[j]) * inv[i][j];
        }
    }
    for(int i=0;i<=n+1; i++){
        out_polyarr[i] = coeffs[i];
    }
    length = n+1;
    calc_err = coeffs[n+1];
    initialerror = calc_err;

    /*SEGNIO*/

    if(!second_it){
        return;
    }

    auto POLY = [&](long double _v){
        long double res=0.0l, p=1.0l;
        for(int it = 0; it<n+1;it++){
            res+=p*coeffs[it];
            p*=_v;
        }
        return res;
    };

    auto ERROR_FUNCTION = [&](long double _v){
        return _fun(_v)- POLY(_v);
    };

    auto ERROR_FUNCTION_DERIV = [&](long double _v){
        return fco_derivativeLambdaSLR_1VFC(ERROR_FUNCTION, _v);
    };


    /*Binary find solutions for ERROR_FUNCTION*/

    long double newCoeffs[N_MAX], zet[N_MAX], highpoints[N_MAX];

    int zetnr = 0, highnr = 0;
    
    zet[zetnr] = b;
    zetnr++;

    std::cout<<"\n";
    // For each pair of cebyshev nodes
    for(int it = 1; it<=n+1;++it){
        FCO_FSOL_PARAM_STEP = 0.001;
        int local_solnr;
        long double local_solarr[MAX];
        fco_calc__SolutionsForLambda(FCO_DERIV_1VF_SLR, ERROR_FUNCTION, cebyshevNodes[it], cebyshevNodes[it-1], local_solarr, local_solnr);
        /*We're sure we only have one sol, so we take the mean of all*/
        long double s=0;
        for(int j = 0; j<local_solnr;++j){
            s+=local_solarr[j];
        }
        long double SOLUTION = s/local_solnr;

        std::cout<<local_solnr<<" ";

        zet[zetnr] = SOLUTION;
        zetnr++;
    }
    zet[zetnr] = a;
    zetnr++;

    // For each pair of zets nodes
    __DX = 0.00001;
    FCO_FSOL_PARAM_DELTAF = 0.1;
    for(int it = 1; it<zetnr;++it){
        FCO_FSOL_PARAM_STEP = 0.001;
        
        int local_solnr;
        long double local_solarr[MAX];
        fco_calc__SolutionsForLambda(FCO_DERIV_1VF_SLR, ERROR_FUNCTION_DERIV, zet[it], zet[it-1], local_solarr, local_solnr);
        /*We're sure we only have one sol, so we take the mean of all*/
        long double s=0;
        for(int j = 0; j<local_solnr;++j){
            s+=local_solarr[j];
        }
        long double SOLUTION = s/local_solnr;

        // std::cout<<local_solnr<<" ";

        highpoints[highnr] = SOLUTION;
        highnr++;
    }

    highpoints[0] = cebyshevNodes[0];
    highpoints[highnr -1] = cebyshevNodes[highnr -1];

    // std::cout<<"\n\nCebychev nodes: \n";
    // for(int i=0;i<=n+1;++i){
    //     std::cout<<cebyshevNodes[i]<<"  ";
    // }

    // std::cout<<"\n\nInRemez fct: \nSols zets:"<< zetnr<<" Values zets: \n";

    // for(int i=0;i<zetnr;++i){
    //     std::cout<<zet[i]<<"  ";
    // }
    // std::cout<<"\n\nInRemez fct: \nSols higha:"<< highnr<<" Values highs: \n";

    // for(int i=0;i<highnr;++i){
    //     std::cout<<highpoints[i]<<"  ";
    // }
    // std::cout<<"\n\n --IT 1 DONE--\n\n";


    // std::cout<<"\n\n\n\n------ ITERATION 2 ------\n\n\n\n";


    for(int i=0;i<highnr;++i){
        cebyshevNodes[i] = highpoints[i];
    }


    //IT 2 *DA CAPO AL SEGNIO

    for(int j=0;j <= n+1; ++j){
        long double p=1;
        for(int i=0;i<=n+1; ++i){
                mak[j][i] = p;
                p*=cebyshevNodes[j]; 
            
        }
    }
    p=1;
    for(int i=0;i<=n+1;++i){
        mak[i][n+1] = p;
        p=-p;
    }
   

    fco_matrsq__inverse(mak, inv, n+2);

    

    /*INV * _FUN(x((i)))^ */


    /**coeffs[n+1] will be E*/
    for(int i=0;i<=n+1; i++){
        coeffs[i] = 0;
    }
    for(int i=0;i<=n+1; i++){
        for(int j=0;j<=n+1;++j){
            
            coeffs[i] +=_fun(cebyshevNodes[j]) * inv[i][j];
        }
    }
    for(int i=0;i<=n+1; i++){
        out_polyarr[i] = coeffs[i];
    }
    length = n+1;
    calc_err = coeffs[n+1];

    // std::cout<<"\n\n --IT 2 DONE, FCT DONE--\n\n" <<"Err Initial:"<<initialerror<<"\n\n";


}

/**
 * @brief Caculates the optimal Remez polynomial in a given interval [rangemin, rangemax] starting from a given degree that yields an error less than err_thres
 * 
 * @param _fun Function
 * @param rangemin Interval min
 * @param rangemax Interval max
 * @param err_thres Error threshold. Reccomended : 1e-7
 * @param miniterations Minimum degree of polynomial. Recommended: 20   
 * @param out_minmaxArray OUT -> Remez array
 * @param out_degree OUT -> Length of the Remez array (degree of the polynomial)
 * @param _err OUT -> The minimal error. If it's higher than err_thres, something went wrong, meaning that either the function gets to high or to flat in said interval which result in weird approximation errors.
 */
inline void fco_calc__optimalMinMaxPoly(fptrldb _fun, long double rangemin, long double rangemax, long double err_thres, int miniterations, long double* out_minmaxArray, int& out_degree, long double& _err){
    long double __e;
    int n = miniterations;
    int i=1;
    while(abs(__e) > abs(err_thres)){
        int __len = 0;
        fco_calc__RemezPolyArray(false, _fun, rangemin, rangemax, n, err_thres, out_minmaxArray, __len, __e );
        out_degree = __len;
        n++;
        i++;
        if(i == 50){
            _err = __e;
            return;
        }
    }
    _err = __e;
}   
/**
 * @brief Calculates polynomial given the polyarray that stores the coefficients
 * 
 * @param x Value to be calculated at
 * @param polyarr 
 * @param len 
 * @return long double 
 */
inline long double fco_calc__PolyValAt(long double x, long double* polyarr, int len){
    long double p=1.0, s=0.0;
    for(int it=0;it<len;++it){
        s+=p*polyarr[it];
        p*=x;
    }
    return s;
}
/**
 * @brief Calculates polynomial derivative given the polyarray that stores the coefficients
 * 
 * @param x Value to be calculated at
 * @param polyarr 
 * @param len 
 * @return long double 
 */
inline void fco_calc__PolyDerivativeArray(long double* in_pollyArr, int len ,long double* out_polyArr){
    for(int i=1;i<len;++i){
        out_polyArr[i-1] = i*in_pollyArr[i];
    }
    out_polyArr[len-1] = 0.0l;
}
/**
 * @brief Calculates polynomial second derivative given the polyarray that stores the coefficients
 * 
 * @param x Value to be aproxi at
 * @param polyarr 
 * @param len 
 * @return long double 
 */
inline void fco_calc__PolySecondDerivativeArray(long double* in_pollyArr, int len ,long double* out_polyArr){
    for(int i=2;i<len;++i){
        out_polyArr[i-2] = (i-1)*i*in_pollyArr[i];
    }
    out_polyArr[len-1] = 0.0l;
    out_polyArr[len-2] = 0.0l;

}
/**
 * @brief Calculates polynomial third derivative given the polyarray that stores the coefficients
 * 
 * @param x Value to be calculated at
 * @param polyarr 
 * @param len 
 * @return long double 
 */
inline void fco_calc__PolyThirdDerivativeArray(long double* in_pollyArr, int len ,long double* out_polyArr){
    for(int i=3;i<len;++i){
        out_polyArr[i-3] = (i-2)*(i-1)*i*in_pollyArr[i];
    }
    out_polyArr[len-1] = 0.0l;
    out_polyArr[len-2] = 0.0l;
    out_polyArr[len-3] = 0.0l;

}

#endif