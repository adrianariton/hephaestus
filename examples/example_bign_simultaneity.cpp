#include "../hephaestus/hephaestus.cpp"
#include "../hephaestus/Heph_Utils.h"

USE_HEPHAESTUS_CPP
using namespace std;

int main() {

    bigreal cs, cc, bdqs("0.7877143603132630285025");
    bigreal ccs, ccc, catan;

    big::bin_calc_sincos(bdqs, ccs, ccc);
    cout<<"\n\nsin:"<<ccs<<"\ncos:"<<ccc<<"\n\n";

    big::calc_sinhcosh(bdqs, ccs, ccc);
    cout<<"\n\nsinh:"<<ccs<<"\ncosh:"<<ccc<<"\n\n";

    bigreal chyp;
    big::calc_arctan(bdqs, catan, chyp);
    cout<<"\n\natan:"<<catan;
    cout<<"\nhyp:"<<chyp.roundToDecimal(5);


    bigreal catanh, chyph;
    big::calc_arctanh(bigreal("0.8"), catanh, chyph);
    cout<<"\nATANH:"<<catanh<<"\nhyph:"<<chyph<<"\n";

    bigreal cln, csqrt;
    big::calc_lnsqrt(bigreal("9"), cln, csqrt);
    cout<<"\n\nLN:"<<cln<<"\nsqrt:"<<csqrt<<"\n";

}