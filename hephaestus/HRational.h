#ifndef HRATIONAL_H
#define HRATIONAL_H

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
class HRational{
    public:
        long long int A;
        long long int D;
        HRational(long long int _A, long long int _D){
            A = _A;
            D = _D;
        }

        HRational(int _A){
            A = _A;
            D = 1;
        }
        HRational reduce(){
            if(D < 0){
                D = -D;
                A = -A;
            }
            bool q = false;
            if(A < 0){
                A = -A;
                q = true;
            }
            long long int gc = std::gcd(A, D);
            A = A / gc;
            D = D / gc;
            if(q){
                A = -A;
            }
            return HRational(A, D);
        }
        friend HRational operator+(HRational lhs, HRational rhs){
            long long int SA, SD;
            SA = lhs.A * rhs.D + lhs.D * rhs.A;
            SD = lhs.D * rhs.D;
            return HRational(SA, SD).reduce();
        }
        friend HRational operator-(HRational lhs, HRational rhs){
            long long int SA, SD;
            SA = lhs.A * rhs.D - lhs.D * rhs.A;
            SD = lhs.D * rhs.D;
            return HRational(SA, SD).reduce();
        }
        friend HRational operator*(HRational lhs, HRational rhs){
            long long int SA, SD;
            SA = lhs.A * rhs.A;
            SD = lhs.D * rhs.D;
            return HRational(SA, SD).reduce();
        }
        friend HRational operator/(HRational lhs, HRational rhs){
            long long int SA, SD;
            SA = lhs.A * rhs.D;
            SD = lhs.D * rhs.A;
            return HRational(SA, SD).reduce();
        }
        friend bool operator<(HRational lhs, HRational rhs){
            lhs = lhs.reduce();
            rhs = rhs.reduce();
            auto diff = lhs - rhs;
            diff = diff.reduce();
            return (diff.A < 0);
        }
        friend bool operator>(HRational lhs, HRational rhs){
            lhs = lhs.reduce();
            rhs = rhs.reduce();
            auto diff = lhs - rhs;
            diff = diff.reduce();
            return (diff.A > 0);
        }
        friend bool operator<=(HRational lhs, HRational rhs){
            lhs = lhs.reduce();
            rhs = rhs.reduce();
            auto diff = lhs - rhs;
            diff = diff.reduce();
            return (diff.A <= 0);
        }
        friend bool operator>=(HRational lhs, HRational rhs){
            lhs = lhs.reduce();
            rhs = rhs.reduce();
            auto diff = lhs - rhs;
            diff = diff.reduce();
            return (diff.A >= 0);
        }
        friend bool operator==(HRational lhs, HRational rhs){
            lhs = lhs.reduce();
            rhs = rhs.reduce();
            auto diff = lhs - rhs;
            diff = diff.reduce();
            return (diff.A == 0);
        }
        friend std::ostream& operator <<(std::ostream& os, HRational nr){
            os<<"("<<nr.A<<"/"<<nr.D<<")";
            return os;
        }
};

#endif