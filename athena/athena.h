#ifndef ATHENA_H
#define ATHENA_H

#include <stack>

template<typename FLAMBDA, typename D>
inline long double ath_quads_adaptive(FLAMBDA &f, D a, D b, D TOL){
    std::stack< std::pair<D, D> > S;
    S.push(std::make_pair(a, b));

    D I = 0;

    while (S.size() > 0) {
        std::pair<D, D> p = S.top();
        S.pop();
        D a = p.first;
        D b = p.second;

        D m = (a + b)/((D)2);

        D I1 = ((b - a)/((D)2)) * (f(a) + f(b));

        D I2 = ((b - a)/((D)4)) * (f(a) + (D)2 * f(m) + f(b));

        if ((I1 > I2 ? (I1 - I2) : (I2 - I1)) < (D)3 * (b - a) * TOL || (b - a) < TOL) {
            I = I + I2;
        } else {
            S.push(std::make_pair(a, m));
            S.push(std::make_pair(m, b));
        }
    }
    return I;
}


#endif