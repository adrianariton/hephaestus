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

int main() {
    // QPOLY := HPoly<FRAC> 
    QPOLY PF = multipleroot(5_frac, 3) * multipleroot(1_frac, 4)  * multipleroot(3_frac, 1) ;
    QPOLY PG = QPOLY({-3, 0, 1});
    LOG QPOLY::integrate_polyfrac(PG, PF) DONE
    return 0;
}