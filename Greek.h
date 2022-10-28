#ifndef GREEK_H
#define GREEK_H

#include <iostream>
#include <string>


inline void get_greek_unicode(std::string s, std::string& unic, std::string& lettername){
    if(s=="alpha" || s=="a" || s=="alfa" || s=="1"){
        unic = "\u03b1";
        lettername = "alpha";
    } else
    if(s=="beta" || s=="b" || s=="2"){
        unic = "\u03b2";
        lettername = "beta";
    } else
    if(s=="gamma" || s=="g" || s=="3"){
        unic = "\u03b3";
        lettername = "gamma";
    } else
    if(s=="delta" || s=="d" || s=="4"){
        unic = "\u03b4";
        lettername = "delta;";
    } else
    if(s=="epsilon" || s=="e" || s=="5"){
        unic = "\u03b5";
        lettername = "epsilon";
    } else
    if(s=="zeta" || s=="z" || s=="6"){
        unic = "\u03b6";
        lettername = "zeta";
    } else
    if(s=="eta"  || s=="7"){
        unic = "\u03b7";
        lettername = "eta";
    } else
    if(s=="theta" || s=="th" || s=="8"){
        unic = "\u03b8";
        lettername = "theta";
    } else
    if(s=="iota" || s=="i" || s=="9"){
        unic = "\u03b9";
        lettername = "iota";
    } else
    if(s=="kappa" || s=="k" || s=="kapa" || s=="10"){
        unic = "\u03ba";
        lettername = "kappa";
    } else
    if(s=="lambda" || s=="l" || s=="11"){
        unic = "\u03bb";
        lettername = "lambda";
    } else
    if(s=="mu" || s=="miu" || s=="m" || s=="12"){
        unic = "\u03bc";
        lettername = "mu";
    } else
    if(s=="nu" || s=="niu" || s=="n" || s=="13"){
        unic = "\u03bd";
        lettername = "nu";
    } else
    if(s=="xi" || s=="x" || s=="14"){
        unic = "\u03be";
        lettername = "xi";
    } else
    if(s=="omicron" ||  s=="o" || s=="15"){
        unic = "\u03bf";
        lettername = "omicron";
    } else
    if(s=="pi" || s=="p" || s=="16"){
        unic = "\u03c0";
        lettername = "pi";
    } else
    if(s=="rho" || s=="ro" || s=="r" || s=="17"){
        unic = "\u03c1";
        lettername = "rho";
    } else
    if(s=="sigma" || s=="s" || s=="sum" || s=="18"){
        unic = "\u03c3";
        lettername = "sigma";
    } else
    if(s=="tau" || s=="t" || s=="19"){
        unic = "\u03c4";
        lettername = "tau";
    } else
    if(s=="upsilon" || s=="y" || s=="20"){
        unic = "\u03c5";
        lettername = "upsilon";
    } else
    if(s=="phi" || s=="fi" || s=="f" || s=="ph" || s=="21"){
        unic = "\u03c6";
        lettername = "phi";
    } else
    if(s=="chi" || s=="hi" || s=="h" || s=="22"){
        unic = "\u03c7";
        lettername = "chi";
    } else
    if(s=="psi" || s=="ps" || s=="trident" || s=="23"){
        unic = "\u03c8";
        lettername = "psi";
    } else
    if(s=="omega" || s=="w" || s=="24"){
        unic = "\u03c9";
        lettername = "omega";
    } else {
        throw("Unrecognised greek letter");
    }


     
}

class Greek{
    public:
        std::string unicode_value;
        std::string lettername;

        Greek(std::string __name_or_index);
        friend std::ostream& operator <<(std::ostream& os, Greek& nr);
};

#endif