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

/**
 * Complex library will soon get
 * a makeover :)
 * 
*/

int main() {
    bigcomplex z(bigreal("122223"), bigreal("122223"));
    bigcomplex z1(bigreal("5"), bigreal("2"));
    cout<<z/z1<<"\n\n";
    cout<<hcomp::polar_coords(z);  
    return 0;
}