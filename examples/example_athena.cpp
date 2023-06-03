
#include <cmath>
#include <iostream>
#include "../athena/athena.h"


#include "../hephaestus/hephaestus.cpp"
#include "../hephaestus/Heph_Utils.h"


/**
 * Use
    #include "hephaestus.cpp"
    #include "Heph_Utils.h"
 * if you work in the same folder
*/


using namespace std;

int main() {
    // QPOLY := HPoly<FRAC> 
    auto y = [] (long double x)
    {
        return 14 * x * exp(x - 2) - 12 * exp(x - 2) - 7 * x *x*x+ 20 * x*x - 26 * x + 12;
    };

    long double t = ath_quads_adaptive(y, (long double)10., (long double)20., (long double)0.0001);
    cout << t;
    return 0;
}