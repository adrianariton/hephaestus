
#include <cmath>
#include <iostream>
#include "athena/athena.h"


#include "hephaestus/hephaestus.cpp"
#include "hephaestus/Heph_Utils.h"


/**
 * Use
    #include "hephaestus.cpp"
    #include "Heph_Utils.h"
 * if you work in the same folder
*/

USE_HEPHAESTUS_CPP
using namespace std;

int main() {
    // 2. 6. 3. 5. 15. 9. 1. 8. 8.
    LET A = TENSOR(bigreal)({1, 2, 3, 
                             4, 5, 6,
                             7, 1, 0}, MATRIX_3X3) DONE
    LET B = TENSOR(bigreal)({0, 1, 1,
                             1, 1, 1,
                             0, 1, 0}, MATRIX_3X3) DONE

    LET A_einstein = __(A, "^alpha_beta") DONE
    LET B_einstein = __(B, "^beta_gamma") DONE

    LET AxB_matrix_prod = __m(A_einstein, B_einstein) DONE
    
    LOG "Tensor matrix product:\n" DONE
    FOREACH(i, indices, IN_TENSOR, AxB_matrix_prod.tensor,
        LOG AxB_matrix_prod.at(indices) ALSO SPACE DONE
    )

    LOG_ALONE("")

    // OR JUST DO 
    AxB_matrix_prod = __m(A, "^alpha_beta", B, "^beta_gamma") DONE
    LOG "Same tensor matrix product:\n" DONE

    FOREACH(i, indices, IN_TENSOR, AxB_matrix_prod.tensor,
        LOG AxB_matrix_prod.at(indices) ALSO SPACE DONE
    )

    LOG_ALONE("")

    // OR DEFINE A PRODUCT
    DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR( matrixprod, bigreal, _x, "^alpha_beta", _y, "^beta_gamma", _x.dim() == 2 && _y.dim() == 2);
    DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR( dblmatrixprod, long double, _x, "^alpha_beta", _y, "^beta_gamma", _x.dim() == 2 && _y.dim() == 2);

    AxB_matrix_prod = DEFN_matrixprod(A, B) DONE
    LOG "Same tensor matrix product but defined:\n" DONE

    FOREACH(i, indices, IN_TENSOR, AxB_matrix_prod.tensor,
        LOG AxB_matrix_prod.at(indices) ALSO SPACE DONE
    )
    //return 0;

    LOG_ALONE("")

    srand (time(NULL));
    auto rnd = [] () -> long double {
        return rand() % 10 + 1;
    };

    LET Rando = HTensor<long double>::random_distribution(rnd, HShape({20, 20}));
    LET Rando1 = HTensor<long double>::random_distribution(rnd, HShape({20, 20}));



    time_t start, end;
    time(&start);
    ios_base::sync_with_stdio(false);

    LET Rando_sq = DEFN_dblmatrixprod(Rando, Rando1) DONE
    time(&end);
    std::cout<<double(end - start)<<"\n\n";
    LOG "Random tensor with random values\n" DONE

    FOREACH(i, indices, IN_TENSOR, Rando_sq.tensor,
        LOG Rando_sq.at(indices) ALSO SPACE DONE
    )

    return 0;
}