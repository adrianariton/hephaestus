#ifndef HPOLY_H
#define HPOLY_H

#include<iostream>
#include<vector>
#include<string>
#include "HRational.h"
#define POLYLOG(poly) std::cout<<"\n"<<(#poly)<<":"; poly.log();

inline bool iszero(long double n){
    return (n <= (1e-10) && n>= (-1e-10));
}
inline bool iszero(HRational n){
    return n.A == 0;
}
inline bool isclose_tozero(long double n){
    return (n <= (1e-6) && n>= (-1e-6));
}
inline bool isclose_tozero(HRational n){
    return isclose_tozero((long double)n.A/(long double)n.D) ;
}
inline long double getdelta(long double _filler){
    return 0.0001;
}
inline std::string to_str(long double n){
    return std::to_string(n);
}
inline std::string to_str(HRational n){
    if(n.D == 1){
        return std::to_string(n.A);
    }
    if(n.A == 0)
        return "0";
    return "("+std::to_string(n.A)+"/"+std::to_string(n.D)+")";
}
inline HRational getdelta(HRational _filler){
    return HRational(1, 10000);
}
inline int powm1(int v){
    if(v%2 ==0) return 1;
    return -1;
}

template <typename T>
inline T powint(T num, int e){
    if(e == 0) return (T)1;
    if(e < 0) return ((T)1)/powint(num, -e);
    T pw = num;
    for(int i=0; i<e-1; ++i){
        pw = pw * num;
    }
    return (T)pw;
}

template <typename T>
class HPoly
{
public:
    std::vector<T> coeffs;
    HPoly(std::vector<T> _coeffs){
        coeffs = _coeffs;
    }
    HPoly(){
        coeffs = std::vector<T>({(T)0});
    }
    HPoly(T number){
        coeffs = std::vector<T>({number});
    }
    HPoly<T> deriv(){
        if(coeffs.size() == 1)
            return HPoly<T>({T(0)});
        std::vector<T> coeffs_new;
        for(int i=0; i<coeffs.size() - 1; ++i){
            coeffs_new.push_back( coeffs.at(i+1) * (T)(i+1)   );
        }
        return HPoly<T>(coeffs_new);
    }
    int degree(){
        return coeffs.size()-1;
    }
    friend HPoly<T> operator +(HPoly<T> lhs, HPoly<T> rhs){
        HPoly<T> maxhs = (lhs.degree() > rhs.degree()) ? lhs : rhs;
        HPoly<T> minhs = (lhs.degree() <= rhs.degree()) ? lhs : rhs;
        std::vector<T> sumcoeffs;
        for(int i=0; i<minhs.coeffs.size(); ++i){
            sumcoeffs.push_back( maxhs.coeffs.at(i) + minhs.coeffs.at(i) );
        }
        for(int i=minhs.coeffs.size();i<maxhs.coeffs.size(); ++i){
            sumcoeffs.push_back(maxhs.coeffs.at(i));
        }
        while (iszero(sumcoeffs.at(sumcoeffs.size()-1)) && sumcoeffs.size() > 1)
        {
            sumcoeffs.pop_back();
        }
        return HPoly<T>(sumcoeffs);
        
    }
    HPoly<T> zero_inverse(){
        std::vector<T> _n;
        for(int i=0;i<(this->coeffs.size()); ++i){
            _n.push_back( (T)(0) - (this->coeffs.at(i)) );
        }
        return HPoly<T>(_n);
    }
    friend HPoly<T> operator -(HPoly<T> lhs, HPoly<T> rhs){
        return lhs + (rhs.zero_inverse());
    }
    friend HPoly<T> operator *(HPoly<T> lhs, HPoly<T> rhs){
        std::vector<T> _n;
        for(int i=0; i<= (lhs.degree() + rhs.degree()); ++i){
            int p=i;
            T v = (T)(0);
            int m_ = p > lhs.degree() ? lhs.degree() : p;
            int M_ = 0 > (p-rhs.degree()) ? 0 : (p-rhs.degree());
            for(int c=M_; c<=m_; ++c){
                if(c<= lhs.degree() && (p-c)<=rhs.degree()){
                v = v + ( lhs.coeffs.at(c) * rhs.coeffs.at(p-c) );
                }
            }
            _n.push_back(v);

        }
        while (iszero(_n.at(_n.size()-1)) && _n.size() > 1)
        {
            _n.pop_back();
        }
        return HPoly<T>(_n);
    }
    HPoly<T> dividebynr(T x){
        std::vector<T> _n;
        for(int i=0; i<=this->degree(); ++i){
            _n.push_back( (*this).coeffs.at(i) / x );
        }
        return HPoly<T>(_n);
    }
    HPoly<T> multiplybynr(T x){
        std::vector<T> _n;
        for(int i=0; i<=this->degree(); ++i){
            _n.push_back( (*this).coeffs.at(i) * x );
        }
        return HPoly<T>(_n);

    }
    T leading(){
        return (this->coeffs).at((this->degree()));
    }
    T coeff(int i){
        return (this->coeffs).at(i);
    }
    HPoly<T> clean(){
        auto sumcoeffs = (*this).coeffs;
        while( (iszero(sumcoeffs.at(sumcoeffs.size()-1))) && sumcoeffs.size() > 1)
        {
            sumcoeffs.pop_back();
        }
        HPoly<T> r = HPoly<T>(sumcoeffs);
        if(r.is_ganznull())
            return HPoly<T>((T)0);
        return HPoly<T>(sumcoeffs);
    }
    static HPoly<T> quot(HPoly<T> lhs, HPoly<T> rhs, HPoly<T>& rem){
        if(lhs.degree() < rhs.degree()){
            rem = lhs;
            return std::vector<T>({(T)0});
         } else {
            T leadrhs = rhs.leading();
            T leadlhs = lhs.leading();
            T multiplyer = leadlhs / leadrhs;
            int deltadeg = lhs.degree() - rhs.degree();
            std::vector<T> emp;
            for(int i=0; i<=deltadeg; ++i){
                emp.push_back( (T)(0) );
            }
            emp.at(deltadeg) = multiplyer;
            HPoly<T> ftrrem;
            HPoly<T> ftrquot;
            ftrquot= ( HPoly<T>(emp).clean() * rhs );
            //             std::cout<<"lhs/ftrqut";

            // lhs.log();
            // ftrquot.log();
            //  (lhs-ftrquot).log();
            lhs = lhs - ftrquot;
                        // std::cout<<"emp";
                        // HPoly<T>(emp).log();
                        //                 lhs.log();

                        // std::cout<<"\n----------------\n";
            lhs = lhs.clean();

            rhs = rhs.clean();
            return HPoly<T>(emp) + quot(lhs, rhs, rem);
         }
    }
    
    static HPoly<T> quot(HPoly<T> lhs, HPoly<T> rhs){
        if(rhs.degree() == 0){
            //std::cout<<"\nONENUMBERED!";
            return lhs.dividebynr(rhs.coeff(0));
        } else
        if(lhs.degree() < rhs.degree()){
            return std::vector<T>({(T)0});
         } else {
            T leadrhs = rhs.leading();
            T leadlhs = lhs.leading();
            T multiplyer = leadlhs / leadrhs;
            int deltadeg = lhs.degree() - rhs.degree();
            std::vector<T> emp;
            for(int i=0; i<=deltadeg; ++i){
                emp.push_back( (T)(0) );
            }
            emp.at(deltadeg) = multiplyer;
            HPoly<T> ftrrem;
            HPoly<T> ftrquot;
            ftrquot= ( HPoly<T>(emp).clean() * rhs );
            //             std::cout<<"lhs/ftrqut";

            // lhs.log();
            // ftrquot.log();
            // (lhs-ftrquot).log();
            lhs = lhs - ftrquot;
                        // std::cout<<"emp";
                        // HPoly<T>(emp).log();
                        //                 lhs.log();

                        // std::cout<<"\n----------------\n";
            lhs = lhs.clean();
            rhs = rhs.clean();
            return HPoly<T>(emp) + quot(lhs, rhs);
         }
    }
    HPoly<T> mod(HPoly<T> rhs){
        HPoly<T> lhs = (*this), r;
        if(lhs.degree() < rhs.degree())
            return lhs;
        HPoly<T> q = HPoly<T>::quot(lhs, rhs, r);
        return r;
    }
    friend bool operator == ( HPoly<T> p1, HPoly<T> p2)
    {
    if(p1.coeffs == p2.coeffs)
        return true;
    else
        return false;
    }
    bool is_ganznull(){
        for(int i=0; i<= (this->degree()); ++i){
            if(!( iszero(this->leading()) ))
                return false;
        }
        return true;
    }
    static void extended_gcd(HPoly<T> a, HPoly<T> b, HPoly<T>& gcd, HPoly<T>& t_, HPoly<T>& s_, HPoly<T>& bez1, HPoly<T>& bez2){
        if(a.degree() < b.degree()){
            std::swap(a, b);
        } 
        if((a.degree() == b.degree()) && (a.leading() < b.leading())){
                        std::swap(a, b);

        }
        T ca = a.leading(), cb = b.leading();

        HPoly<T> old_r = a, r = b;
        HPoly<T> old_s = HPoly<T>((T)1), s =  HPoly<T>((T)0);
        HPoly<T> old_t =  HPoly<T>((T)0), t =  HPoly<T>((T)1);
        HPoly<T> aux;
        // if(a.degree() == 0){
        //     gcd = a;
        //     t_ = HPoly<T>::quot(b, a);
        //     s_ = old_s;
        //     return;
        // }
        int i=0;
        while(! r.is_ganznull()){
            i++;
            if(i>50) {throw std::invalid_argument("OVERLOOP");}
           // std::cout<<"BHBHBHB\n";
            if(r.is_ganznull()) break;
           // std::cout<<" "<<i;
           // std::cout<<"QUOT\n";
            HPoly<T> quotient = HPoly<T>::quot(old_r, r);
     //    std::cout<<"REREREEEE\n";
            
            
            aux = old_r;
            old_r = r;
            r = aux - quotient * r;
            // POLYLOG(old_r)
            // POLYLOG(r)
            //  std::cout<<"STSTS\n";
            //  POLYLOG(r)

            //  POLYLOG(old_r)
            // POLYLOG(quotient)

             //std::cout<<r.coeff(0)<<" "<<((T)0)<<" "<<(r.degree()==0)<<" "<<(r.coeff(0) == (T)0) <<"\n";
             //std::cout<<"rrrrr\n";
            
            aux = old_s;
            old_s = s;
            s = aux - quotient * s;
                  //      std::cout<<"STSTS\n";

            aux = old_t;
            old_t = t;
            t = aux - quotient * t;
            // POLYLOG(old_r)
            // POLYLOG(r)
            // POLYLOG(quotient)
            if(r.is_ganznull()) break;

        
                //        std::cout<<"STSTS\n";
        };

        bez1 = old_s;
        bez2 = old_t;
        t_ = t;
        s_ = s;
        gcd = old_r;

    }
     HPoly<T> to_monicp(){
        HPoly<T> D = (*this);
        if(D+D == D)
            return D;
        return D.dividebynr(D.leading());
    }
    static HPoly<T> gcd(HPoly<T> a, HPoly<T> b){
        HPoly<T> gcd_, t, s, bez1, bez2;
        HPoly<T>::extended_gcd(a, b, gcd_, t, s, bez1, bez2);
        return gcd_.to_monicp();
    }
    
    static HPoly<T> sqfactorization_D1(HPoly<T> D){
        //POLYLOG(D.deriv())
        HPoly<T> R = HPoly<T>::gcd( D, D.deriv() );
       //POLYLOG(R)
        HPoly<T> DpR = HPoly<T>::quot(D, R);
        //POLYLOG(DpR)
        HPoly<T> den = HPoly<T>::gcd(R, DpR);
        //POLYLOG(den)
        return HPoly<T>::quot(DpR, den).to_monicp();
    }
   
    static HPoly<T> sqfactorization_D1(HPoly<T> D, HPoly<T> &R){
        //POLYLOG(D.deriv())
        R = HPoly<T>::gcd( D, D.deriv() );
       // POLYLOG(R)
        HPoly<T> DpR = HPoly<T>::quot(D, R);
       // POLYLOG(DpR)
        HPoly<T> den = HPoly<T>::gcd(R, DpR);
        //POLYLOG(den)
        HPoly<T> D1 = HPoly<T>::quot(DpR, den);
        return D1.to_monicp();
    }

    static std::vector< HPoly<T> > sqfactiorization_Di(HPoly<T> D){
        std::vector< HPoly<T> > out_Di = { HPoly<T>((T)1) }; // D0 is 1 --  and also not used
        HPoly<T> R;            
        // POLYLOG(D)
        // std::cout<<"DDDDDDDDDDD";
        HPoly<T> Di = HPoly<T>::sqfactorization_D1(D, R);
        int i=0;
        while(! (D.degree() == 0)){
            i++;
            //POLYLOG(D)
            out_Di.push_back(Di.to_monicp());
            D = R;
            if(D.degree() == 0) break;
            Di = HPoly<T>::sqfactorization_D1(D, R);
            // POLYLOG(D);
            // POLYLOG(Di); 
            if(i > 50){
                throw std::invalid_argument("OVERLOOP");
            }

        }
        return out_Di;
    }

    static HPoly<T> linear_wroot(T root){
        std::vector<T> p;
        p.push_back((T)(0) - root);
        p.push_back((T)1);
        return HPoly<T>(p);
    }
    static HPoly<T> poly_wmultipleroot(T root, int times){
        HPoly<T> p = linear_wroot(root);
        for(int i=0;i<times-1; ++i){
            p = p * linear_wroot(root);
        }
        return p;
    }
    static HPoly<T> resultant(HPoly<T> F, HPoly<T> G){
        HPoly<T> FA[100], R[100];
        FA[1] = F;
        FA[2] = G;
        int i=2;
        R[1] = HPoly<T>( (T)1 );
        while( FA[i].degree() > 0 ){
            FA[i+1] = FA[i-1].mod( FA[i] );
            // FA[i+1].log();
            // std::cout<<(FA[i].degree() * FA[i-1].degree() )<<"\n";
            R[i] = powm1( FA[i].degree() * FA[i-1].degree() ) * powint( FA[i].leading(), FA[i-1].degree() - FA[i+1].degree() ) * R[i-1];
            i++;
            if(i==100){
                throw std::invalid_argument("OVERLOOP");
            }
        }
        if(!FA[i].is_ganznull())
            return R[i-1] * powint( FA[i].leading(), FA[i-1].degree() );
        else return HPoly<T>( (T)0 );
    }
    bool is_squarefree(){
        if(HPoly<T>::sqfactiorization_Di((*this)).size() == 2) // 0 , 1
            return true;
        return false;
    }
    static std::vector< HPoly<T> > hermite_redADfact(HPoly<T>& A, std::vector< HPoly<T> >& Dfact, HPoly<T>& D){
        int m = Dfact.size() - 1;
        //std::cout<<"\n\n"<<m<<"yeet\n";
        HPoly<T> Adiv = A.dividebynr(1-m), V = Dfact.at(m), Vm = HPoly<T>((T)1);
        for(int i=1;i<=m; ++i){
            Vm = Vm * V;
        }
        //std::cout<<"\n\nm:"<<m<<"\n";
        // POLYLOG(D)
        //  POLYLOG(V)
        //  POLYLOG(Vm)
        HPoly<T> U = HPoly<T>::quot(D, Vm);
        HPoly<T> UVd = U * V.deriv();
        // POLYLOG(V)

        // POLYLOG(V.deriv())
        HPoly<T> _gcd ,_t , _s, B, C;
        // POLYLOG(U)
        // POLYLOG(UVd)
        // POLYLOG(V)
        HPoly<T>::extended_gcd(UVd, V, _gcd, _t, _s, B, C);
        // HPoly<T> DF( {18, -12, 2}), DG({5, -6, 1});
        // POLYLOG( HPoly<T>::gcd(DF, DG) )
        // std::cout<<(DF == UVd)<<" "<<(DG == V)<<"\n";
        // POLYLOG(DF) POLYLOG(DG) POLYLOG(UVd)
        // POLYLOG(V) POLYLOG((DF - UVd)) POLYLOG((DG - V))
        // if((DF - UVd).is_ganznull() && (DG - V).is_ganznull()){
        //     HPoly<T>::extended_gcd(DF, DG, _gcd, _t, _s, B, C);

        // }
        // POLYLOG( HPoly<T>::gcd(UVd, V) )

        // POLYLOG(_gcd);
        //  POLYLOG(B) POLYLOG(C) 
        B = B * Adiv;
        C = C * Adiv;
        B = B.dividebynr(_gcd.leading());
        C = C.dividebynr(_gcd.leading());
    //   POLYLOG(B) POLYLOG(C) 

        if(B.degree() >= V.degree()){
            //POLYLOG(B) POLYLOG(C) POLYLOG(_t) POLYLOG(_s)
            HPoly<T> r;
            //POLYLOG(B) POLYLOG(V)
            HPoly<T> q = HPoly<T>::quot(B, V, r);
            //POLYLOG(q) POLYLOG(r)
            B = r;
            C = C + q*UVd;
        }
       // POLYLOG(B)
        D = HPoly<T>::quot(D, V);
        Dfact.pop_back();
        Dfact.at( Dfact.size() - 1 ) = Dfact.at( Dfact.size() - 1 ) * V;
        // POLYLOG(U)
        // POLYLOG( (C.multiplybynr(1-m) - ( B.deriv() * U )) )
        A = C.multiplybynr(1-m) - U * B.deriv();

        return std::vector< HPoly<T> >({B,  HPoly<T>::quot(Vm, V) });

    }
    static std::vector< HPoly<T> > hermite_redAD(HPoly<T>& A,  HPoly<T>& D){
        std::vector< HPoly<T> > Dfact = HPoly<T>::sqfactiorization_Di(D);
        // std::cout<<"  \n";
        // for(int i=0; i< Dfact.size(); ++i) Dfact.at(i).log();
        //         std::cout<<"  \n";

        return HPoly<T>::hermite_redADfact(A, Dfact, D);
    }
    HPoly<T> integral(){
        if((*this).is_ganznull())
            return HPoly<T>((T)0);
        if(coeffs.size() == 1)
            return HPoly<T>({(T)0, (*this).coeff(0)});
        std::vector<T> coeffs_new = {(T)0};
        for(int i=0; i<coeffs.size(); ++i){
            coeffs_new.push_back( coeffs.at(i) / (T)(i+1)   );
        }
        return HPoly<T>(coeffs_new);
    }
    static std::vector< HPoly<T> > hermite_reduction(HPoly<T>& A,  HPoly<T>& D){
        std::vector< HPoly<T> > Dfact = HPoly<T>::sqfactiorization_Di(D);
        std::vector< HPoly<T> > _ret;
        std::vector< HPoly<T> > _hAD ;
        int m = Dfact.size() - 1;
        for(int i=1; i<=m-1; ++i){
            // std::cout<<"ALALLALA";
            // POLYLOG(D)
            Dfact = HPoly<T>::sqfactiorization_Di(D);
            // std::cout<<"\n\nDFACT: ";
            // for(int j=0; j< Dfact.size(); ++j){
            //     Dfact.at(j).log();
            // }
            // std::cout<<"\n\n ";

            _hAD = HPoly<T>::hermite_redADfact(A, Dfact, D);
            HPoly<T> r;
            HPoly<T> q = HPoly<T>::quot(A, D, r);
            A = r;
            
            // integrate q;
            HPoly<T> ia = _hAD.at(0);
            HPoly<T> id = _hAD.at(1);
            // POLYLOG(ia)
            // POLYLOG(id)

            ia = ia + id * q.integral();
             A = A.clean();
            ia = ia.clean();
            D = D.clean();
            id = id.clean();
            _ret.push_back(ia);
            _ret.push_back(id);
           
            //  POLYLOG(A)
            //  POLYLOG(D)
            //  POLYLOG(ia.clean())
            //  POLYLOG(id.clean())
           // std::cout<<"\n"<<i<<"----------------------------------------------\n\n";

            //POLYLOG(A)
        }
        //POLYLOG(D) POLYLOG(A)
        

        return _ret;

    }
    T calc_at(T x){
        T one = T(1), v = T(0);
        for(int i=0; i<=(*this).degree(); ++i){
            v = v + one * (*this).coeff(i);
            one = one * x;
        }
        return v;
    }
    static std::vector<T> sqfree_solutions(HPoly<T> P){
        std::vector<T> vk;
        T a = T(-20), b=T(20);
        T delta = getdelta(a);
        for(T i = a; i <= b; i = i + delta){
            if( isclose_tozero( P.calc_at(i) ) ){
                vk.push_back(i);
                
            }
            if(vk.size() == P.degree())
                break;
        }
        if(vk.size() != P.degree())
            throw std::invalid_argument("Compex polys solutions not yet supported!");
        return vk;
    }
    std::string to_string(){
        std::string s="";
        for(int i=0; i<= this->degree(); ++i){
            s+= to_str((*this).coeff(i)) +"*x^"+ std::to_string(i)+ " + ";
        }
        s.pop_back();
        s.pop_back();
        s.pop_back();
        return s;
    }
    static std::string integrate_polyfrac(HPoly<T> X, HPoly<T> D){
        HPoly<T> A;
        HPoly<T> P = HPoly<T>::quot(X, D, A);
        std::string s="";
        if( ! P.is_ganznull() )
            s+="(" + P.integral().to_string() + ") + ";
        auto vkt = HPoly<T>::hermite_reduction(A, D);
        for(int i=0; i<vkt.size(); ++i){
            s+="(" + vkt.at(i).to_string() + ")";
            if(i%2==0) s+="/";
            else s+=" + ";
        }
        std::vector<T> sols = HPoly<T>::sqfree_solutions(D);
        auto dD = D.deriv();
        for(int i=0; i<sols.size(); ++i){
            s+=to_str(A.calc_at(sols.at(i)) / dD.calc_at(sols.at(i)))+"*ln(x-"+ to_str(sols.at(i)) +") + ";
        }
        s.pop_back();
        s.pop_back();
        s.pop_back();    
        return s; 
    }
    void log(){
        std::cout<<"\n";
        for(int i=0; i<= this->degree(); ++i){
            std::cout<< (*this).coeff(i) <<"*"<<"x^"<<i<<" + ";
        }
        std::cout<<"|\n";
    }
    friend std::ostream& operator <<(std::ostream& os, HPoly nr){
        for(int i=0; i<= nr.degree(); ++i){
            os<< (nr).coeff(i) <<"*"<<"x^"<<i<<" + ";
        }
        return os;
    }
};


// - EDUCATIA // - SMART CITIES // - HEALTHCARE // - ENABLING TECHNOLOGIES

// - - \\

template <typename T>
inline HPoly<T> multipleroot(T root, int n){
    return HPoly<T>::poly_wmultipleroot(root, n);
}

template <typename T>
inline std::vector< HPoly<T> > hermite_reduction(HPoly<T>& A, HPoly<T>& D){
    return HPoly<T>::hermite_reduction(A, D);
}
template <typename T>
inline HPoly<T> polygcd(HPoly<T> A, HPoly<T> B){
    return HPoly<T>::gcd(A, B);
}

template <typename T>
inline void polyextendedgcd(HPoly<T> a, HPoly<T> b, HPoly<T>& gcd, HPoly<T>& t_, HPoly<T>& s_, HPoly<T>& bez1, HPoly<T>& bez2){
    return HPoly<T>::extended_gcd(a, b, gcd, t_, s_, bez1, bez2);
}
template <typename T>
inline HPoly<T> resultant(HPoly<T> a, HPoly<T> b){
    return HPoly<T>::resultant(a, b);
}
#endif