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
    HShape T_SHAPE({2, 3});    
    LET mytens = TENSOR(int)({1, 2, 3, 4, 2, 3}, T_SHAPE); 

    /* Use this if you also want to see the tensor dymension
    HTENS_COUT_DEPTH_DIM = true;
    */
    cout<<"T1:\n"<<mytens<<"\n\n";


    HTensor<int> myvsltens({1, 3}, VECTOR_2); 
    cout<<"T2:\n"<<myvsltens<<"\n\n";

    HTensor<int> prtens = HTensor<int>::tensor_product(mytens, myvsltens);
    std::cout<<"T1 x T2:\n"<<prtens<<"\n\n";

    LET heph_prtens = __m(mytens, myvsltens) DONE
    std::cout<<"same T1 x T2:\n"<<prtens;

    return 0;
}