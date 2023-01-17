#include "../hephaestus.cpp"
#include "../Heph_Utils.h"

/**
 * Use
    #include "hephaestus.cpp"
    #include "Heph_Utils.h"
 * if you work in the same folder
*/

USE_HEPHAESTUS_CPP
using namespace std;

int main() {
    bigreal number("12.3344829");
    bigreal exponent("2.10029");
    /*Use Hephaestus macros*/
    LOG big::sin(number) ALSO NEW_LINE
        ALSO big::pow(number, exponent) ALSO NEW_LINE
        ALSO big::ln(number)
        DONE
    return 0;
}