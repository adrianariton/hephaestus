
#include "../hephaestus/hephaestus.cpp"
#include "../hephaestus/Heph_Utils.h"
/**
 * Use
    #include "hephaestus.cpp"
    #include "Heph_Utils.h"
 * if you work in the same folder
*/

USE_HEPHAESTUS_CPP
using namespace std;

/**
 * Complex library will soon get
 * a makeover :)
 * 
*/

int main() {
     mve a = mve("x^2 + e^x+73+pi-(23*7)");
    LOG mvef::dfdx_string(a, "x");

    LOG mvef::solvefunction(a, {"x", "e", "pi"}, {23.2, CONSTANT_E, CONSTANT_PI});
    return 0;
}

   