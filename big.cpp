#ifndef BIG_H
#define BIG_H
#include "BNdecimal.h"
#include "BinaryBNInt.h"
/**Decimal big number*/
typedef BNdecimal bigreal;
/**Binary big number*/
typedef BinaryBNint bigint2;
typedef BNint bigint;
/**
 * @brief INTEGER! Iterations for finding the min max poly of trig functions.
 * Bigger => better aproximation but slower time [Said aproximation is only visible when BN_DEC_TRIGPRECISION is higher than 500-1000].
 * Works very well around 50 for ALL numbers.
 * 
 */
inline bigreal ITER_TRIG = bigreal("50");
/**
 * @brief INTEGER! Iterations for finding the min max poly of the exp functions.
 * Bigger => better aproximation but slower time [Said aproximation is only visible when BN_DEC_EXPPRECISION is higher than 5000-20000 - NOT RECOMMENDED!].
 * Works very well around 200 for ALL numbers.
 * 
 */
inline bigreal ITER_EXP = bigreal("169");
/**
 * @brief INTEGER! Max chunk size in which the exponent of the exp function should be broken into. For refference, the function uses a kinda-divide-et-impera algorithm
 * Works well for 2-10 for ALL numbers.
 * 
 * Default is 2.
 */
inline bigreal CHUNKS_EXP = bigreal("2");
/**
 * @brief INTEGER! Iterations for finding the min max poly of the ln (natural log) functions.
 * Bigger => better aproximation but slower time [Said aproximation is only visible when BN_DEC_LNPRECISION is higher than 5000-20000 - NOT RECOMMENDED!].
 * Works very well around 50 for ALL numbers.
 * 
 */
inline bigreal ITER_LN = bigreal("50");
/**
 * @brief INTEGER! Iterations for finding the min max poly of the atan (arc-tangent) function.
 * Bigger => better aproximation but slower time [Said aproximation is only visible when BN_DEC_TRIGPRECISION is higher than 5000-20000 - NOT RECOMMENDED!].
 * Works very well around 100 for ALL numbers.
 */
inline bigreal ITER_ATAN = bigreal("100");

inline bool BIG_ROUND_EXPFUNCTIONS_RESULTS_TO_RN = true;
inline int BIG_RN = 100;

/**                     CONSTANTS                      */
inline const bigreal BIG_PI = bigreal("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145");
inline const bigreal BIG_2_PI = bigreal("6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413596429617302656461329418768921910116446345071881625696223490056820540387704221111928924589790986076392885762195133186689225695129646757356633054240381829");
inline const bigreal BIG_PI_2 = bigreal("1.5707963267948966192313216916397514420985846996875529104874722961539082031431044993140174126710585339910740432566411533235469223047752911158626797040642405587251420513509692605527798223114744774651909822144054878329667230642378241168933915826356009545725");
inline const bigreal BIG_PI_4 = bigreal("0.78539816339744830961566084581987572104929234984377645524373614807695410157155224965700870633552926699553702162832057666177346115238764555793133985203212027936257102567548463027638991115573723873259549110720274391648336153211891205844669579131780047728625");
inline const bigreal BIG_SQRT_3 = bigreal("1.7320508075688772935274463415058723669428052538103806280558069794519330169088000370811461867572485756756261414154067030299699450949989524788116555120943736485280932319023055820679748201010846749232650153123432669033228866506722546689218379712270471316603678615880190");
inline const bigreal BIG_E = bigreal("2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274274663919320030599218174135966290435729003342952605956307381323286279434907632338298807531952510190115738341879307021540891499348841675092447614606680822648001684774118537423454424371075390777449920695517027618386062613313845830007520449338265602976067371132007093287091274437470472306969772093101416");

inline const bigreal BIG_1_PI = bigreal("1")/BIG_PI;
inline const bigreal BIG_2 = bigreal("2");
inline const bigreal BIG_ZERO = bigreal("0");

inline const bigreal BIG_ONE = bigreal("1");
inline const bigreal BIG_HALF = bigreal("0.5");
inline const bigreal BIG_1_9 = bigreal("1")/bigreal("9");
inline const bigreal BIG_1_72 =bigreal("1")/bigreal("72");
inline const bigreal BIG_1_1008 = bigreal("1")/bigreal("1008");
inline const bigreal BIG_1_30240 = bigreal("1")/bigreal("30240");

inline const bigreal BIG_LN10 = bigreal("2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298341967784042286248633409525465");

/**
 * @brief Some functions that are useful and are not calculating funtions per se.
 * Includes: clean, is_number, is_odd, to_binary, to_decimal, to_bigint, from_bigint, floor, abs, roundTo and roundedTo
 * 
 */
inline namespace big{
    /**
     * @brief Cleans a number, gets rid of 0s after dec point. 1.50000 becomes 1.5
     * 
     * @param __n 
     */
    inline void clean(bigreal& __n){
        bigreal::clean(__n);
    }
    /**
     * @brief Checks if a string is in fact a number
     * 
     * @param s 
     * @return true 
     * @return false 
     */
    inline bool is_number(std::string s){
        if(s.at(0) == '-')
            s.pop_back();
        int cou = 0;
        for(int i=0; i<s.size();++i){
            if(s.at(i) == '.')
                cou++;
            if(!(s.at(i)>='0' && s.at(i)<='9' || s.at(i) == '.'))
                return false;
        }
        if(cou >= 2)
            return false;
        return true;
    }
    /**
     * @brief Checks if number is odd. If a real number is provided, it rounds it
     * 
     * @param number 
     * @return true 
     * @return false 
     */
    inline bool is_odd(bigreal number){
        bigreal fln = number.floor();
        return ((fln.integerPart.cvalue.at(fln.integerPart.cvalue.size()-1)-'0') % 2 == 1);
    }
    inline bool is_odd(BNint num){
        return ((num.cvalue.at(num.cvalue.size()-1)-'0') % 2 == 1);
    }
    /**
     * @brief Convert an integer to a binary integer. If a real number is provided, it gets rounded.
     * 
     * @param number 
     * @return bigint2 
     */
    inline bigint2 to_binary(bigreal number){
        bigreal fln = number.floor();
        std::string bins = "";
        BNint n;
        n = fln.integerPart;
        BNint two("2");
        BNint zero("0");
        while(n > zero){
            if(is_odd(n))
                bins.push_back('1');
            else 
                bins.push_back('0');
            n = n/two;  
        }
        std::string rbns = "";
        for(int i=0;i<bins.size(); ++i){
            rbns.push_back(bins.at(bins.size() - 1 - i));
        }
        return BinaryBNint(rbns);
    }
    /**
     * @brief Binary integer to decimal integer
     * 
     * @param binary 
     * @return bigreal 
     */
    inline bigreal to_decimal(bigint2 binary){
        bigreal powa("1"), sum("0");
        int i = binary.bits.size()-1;
        while(i>=0){
            if(binary.bits.at(i) == '1'){
                sum = sum + powa;
            }
            powa = powa*BIG_2;
            i--;
        }
        sum.isNegative = binary.isNegative;
        return sum;
    }
    inline bigreal floor(bigreal __x){
        return __x.floor();
    }
    
    inline bigreal abs(bigreal __x){
        return __x.abs();
    }
    /**
     * @brief Returns the variable rounded to "decimal" decimals
     * 
     * @param __x 
     * @param decimal 
     * @return bigreal 
     */
    inline bigreal roundedTo(bigreal __x,int decimal){
        return __x.roundToDecimal(decimal);
    }
    /**
     * @brief 
     * 
     * @param __x Gets rounded
     * @param decimal 
     */
    inline void roundTo(bigreal& __x, int decimal){
        __x = __x.roundToDecimal(decimal);
    }
    inline bigint to_bigint(bigreal __n){
        return bigint(big::floor(__n).integerPart);
    }
    inline bigreal from_bigint(bigint __n){
        return bigreal(__n.cvalue);
    }
}
/**
 * @brief Bad precision and functions take a lot, most are written without regard to performance, using taylor series centered around 0. I kept them just as an alternative, but it's best to use big_cordic:: namespace for quick fast and reliable calculations!
 * 
 */
inline namespace brute{
    /**
     * @brief The enviroment of the brute functions
     * 
     */
    inline namespace env{
        inline void penv_reset(){
            BN_DEC_PRECISION = 300;
            BN_DEC_SQRTPRECISION = 100;
            BN_DEC_TRIGPRECISION = 100;
            BN_DEC_EXPPRECISION = 1000;
            BN_DEC_INVEXPPRECISION = 100;
            BN_DEC_LNPRECISION = 1000;
        }
        inline void penv_set_for_negative_exp(){
            BN_DEC_EXPPRECISION = 100;
            BN_DEC_INVEXPPRECISION = 100;
            BN_DEC_LNPRECISION = 100;
        }
        inline void penv_set_for_biglength_exp_exponent(){
            BN_DEC_EXPPRECISION = 100;
            BN_DEC_INVEXPPRECISION = 100;
            BN_DEC_LNPRECISION = 100;
        }
        inline void ienv_reset(){
            ITER_TRIG = bigreal("50");
            ITER_EXP = bigreal("200");
            CHUNKS_EXP = bigreal("2");
            ITER_LN = bigreal("50");
        }
        inline void ienv_set_for_chunk_10(){
            CHUNKS_EXP = bigreal("10");
        }
    }
    
    /**
     * @brief Slower sine function with high accuracy up to 100-120 decimals (accuracy can be set using BN_DEC_TRIGPRECISION = 120 for example).
     * Uses taylor series and thus is slower but much more reliable for exact calculations. For a faster but less reliable aproximation use the q and qp alternatives: qsin and qpsin.
     * 
     * @param __x 
     * @return bigreal 
     */
    inline bigreal sin(bigreal __x){
        return __x.big_sin(ITER_TRIG);
    }
    /**
     * @brief Cos function using taylor series (accuracy can be set using BN_DEC_TRIGPRECISION = 120 for example).
     * 
     * @param __x 
     * @return bigreal 
     */
    inline bigreal cos(bigreal __x){
        return __x.big_cos(ITER_TRIG);
    }
    /**
     * @brief Tan function using taylor series (accuracy can be set using BN_DEC_TRIGPRECISION = 120 for example).
     * Tan = Sin/Cos
     * @param __x 
     * @return bigreal 
     */
    inline bigreal tan(bigreal __x){
        return (brute::sin(__x)/brute::cos(__x));
    }
    /**
     * @brief Cot function using taylor series (accuracy can be set using BN_DEC_TRIGPRECISION = 120 for example).
     * Cot = Cos/Sin
     * @param __x 
     * @return bigreal 
     */
    inline bigreal cot(bigreal __x){
        return (brute::cos(__x)/brute::sin(__x));
    }
    
    /**
     * @brief Exp function using taylor series
     * 
     * @param __x 
     * @return bigreal 
     */
    inline bigreal exp(bigreal __x){
        if(BIG_ROUND_EXPFUNCTIONS_RESULTS_TO_RN){
            return __x.big_exp(CHUNKS_EXP, ITER_EXP).roundToDecimal(BIG_RN);
        }
        return __x.big_exp(CHUNKS_EXP, ITER_EXP);
    }
    /**
     * @brief Pade aproximation for exponential in 0-3. Has quite a high accuracy so it's reliable.
     * 
     * 
     * @param __x 
     * @return bigreal 
     */
    inline bigreal expdq(bigreal __x){
        bigreal x[6];
        x[0] = BIG_ONE;
        for(int i=1;i<6;++i){
            x[i] = __x*x[i-1];
        }
        bigreal A = BIG_ONE + BIG_1_9 * x[2] + BIG_1_1008 * x[4];
        bigreal B = BIG_HALF * x[1] + BIG_1_72 * x[3] + BIG_1_30240 * x[5];
        if(BN_MESSAGES)
            std::cout<<"\n\nN:"<<A+B<<"\nDEN:"<<A-B<<"\n\n";
        bigreal N = A+B;
        bigreal DEN = A-B; 
        DEN = DEN.roundToDecimal(BN_DEC_INVEXPPRECISION);
        if(BIG_ROUND_EXPFUNCTIONS_RESULTS_TO_RN){
            return (N*(BIG_ONE/DEN)).roundToDecimal(BIG_RN);
        }
        return (N*(BIG_ONE/DEN)).roundToDecimal(BN_DEC_EXPPRECISION);
    }
    inline bigreal ln(bigreal __x){
        if(__x == BIG_E){
            return bigreal("1");
        }
        return __x.big_ln(ITER_LN);
    }
    
    /**
     * @brief Pow function for natural exponents. If a non natural exponent is provided, the floor of the exponent is used. If __e < 0 an exception is thrown
     * 
     * @param __x 
     * @param __e 
     * @return bigreal 
     */
    inline bigreal pown(bigreal __x, bigreal __e){
        if(__e.isNegative){
            throw std::invalid_argument("Negative exponent provided in pown function!");
        }
        if(__e.floor().abs() == bigreal("0")){
            return bigreal("1");
        }
        return __x.big_raise_to_natural(__e);
    }
    /**
     * @brief Power function for both natural and real exponents
     * 
     * @param __x 
     * @param __e 
     * @return bigreal 
     */
    inline bigreal powf(bigreal __x, bigreal __e){
        if(__e.abs() == bigreal("0")){
            return bigreal("1");
        }
        bigreal _a = brute::ln(__x) * __e;
        if(DOUBLE_THE_FUN)
            roundTo(_a, 2*BN_DEC_INVEXPPRECISION);
        else 
            roundTo(_a, BN_DEC_INVEXPPRECISION);
        return brute::exp(_a);
    }
    /**
     * @brief Pow function, quicker than pow, also using taylor series but only for the fractional part of the number
     * 
     * @param __x 
     * @param __e 
     * @return bigreal 
     */
    inline bigreal powfq(bigreal __x, bigreal __e){
        if(__e.abs() == bigreal("0")){
            return bigreal("1");
        }
        bigreal _h = pown(__x, __e);
        bigreal _left = __e - floor(__e);

        if(BN_MESSAGES)
            std::cout<<"\nNat exp:"<<_h<<"\nleft:"<<_left<<"\n\n";
        
        bigreal aux = _left;
        if(aux.abs() == bigreal("0")){
            return _h;
        }
            
        bigreal _e2 = powf(__x, _left);
        return _h * _e2;
    }
    /**
     * @brief Pow function, quicker than pow, also using taylor series but only for the fractional part of the number and also the logarithm
     * 
     * @param __x 
     * @param __e 
     * @return bigreal 
     */
    inline bigreal powq(bigreal __x, bigreal __e){
        if(__e.abs() == bigreal("0")){
            return bigreal("1");
        }
        bigreal _h = pown(__x, __e);
        bigreal _left = __e - floor(__e);

        if(BN_MESSAGES)
            std::cout<<"\nNat exp:"<<_h<<"\nleft:"<<_left<<"\n\n";
        bigreal aux = _left;
        if(aux.abs() == bigreal("0")){
            return _h;
        }
        bigreal _expl = brute::ln(__x) * _left;

        //exp(_expl) * _h

        bigreal _hl = pown(roundedTo(BIG_E, BN_DEC_INVEXPPRECISION), _expl);
        bigreal _expll = _expl - floor(_expl);
        roundTo(_expll, BN_DEC_INVEXPPRECISION);
        if(BIG_ROUND_EXPFUNCTIONS_RESULTS_TO_RN){
            
            return (_h * _hl * brute::exp(_expll)).roundToDecimal(BIG_RN);
        }
        return _h * _hl * brute::exp(_expll);
    }
    /**
     * @brief Pow function using Pade aproximation. Is fast, but can have large error for high numbers:
     * ~ 0.00001% - Maximum error
     * 
     * @param __x 
     * @param __e 
     * @return bigreal 
     */
    inline bigreal powdq(bigreal __x, bigreal __e){
        if(__e.abs() == bigreal("0")){
            return bigreal("1");
        }
        bigreal _h = pown(__x, __e);
        bigreal _left = __e - floor(__e);

        if(BN_MESSAGES)
            std::cout<<"\nNat exp:"<<_h<<"\nleft:"<<_left<<"\n\n";
        bigreal aux = _left;
        if(aux.abs() == bigreal("0")){
            return _h;
        }

        bigreal _expl = brute::ln(__x) * _left;
        bigreal _hl = pown(roundedTo(BIG_E, BN_DEC_EXPPRECISION), _expl);
        
        bigreal _expll = _expl - floor(_expl);
       
        roundTo(_expll, BN_DEC_INVEXPPRECISION);
        if(BN_MESSAGES)
            std::cout<<"\n\nleft to calc:"<<_expll<<"\n\n";
        return (_h * _hl * expdq(_expll));
    }
    inline bigreal sqrt(bigreal __x){
        return __x.sqrt();
    }
    /**
     * @brief Returns the sign of a number. True if positive, false if negative
     * 
     * @param __x 
     * @return true -> Positive;
     * @return false -> Negative;
     */
    inline bool sgn(bigreal __x){
        return !(__x.isNegative);
    }
    /**
     * @brief Quick sine using Bhāskara I aproximation. Error can be as high as 0.05. Slower and less accurate than it's qp alternative: qpsin
     * 
     * @param __x Angle in radians.
     * @return bigreal 
     */
    inline bigreal qsin(bigreal __x){
        bigreal sixteen("16"), four("4"), five("5"), minusone("-1");
        if(__x.isNegative)
            return minusone*brute::qsin(big::abs(__x));
        bigreal x = __x - BIG_2_PI*big::floor(__x/BIG_2_PI);
        bigreal::clean(x);
        bigreal xpimx = x*(BIG_PI - x);
        bigreal::clean(xpimx);
        bigreal _e = five*BIG_PI*BIG_PI - four*xpimx;
        big::roundTo(_e, BN_DEC_TRIGPRECISION);
        if(x < BIG_PI)
            return ((sixteen*xpimx)/_e).roundToDecimal(BN_DEC_TRIGPRECISION);
        return minusone*qsin(x - BIG_PI);
    }

    /**
     * @brief Quick Sine function with higher precision than qsin. Maximum error yield is about 0.0000338.
     *
     * 
     * @param __x_deg Angle in degrees
     * @return bigreal 
     */
    inline bigreal qpsindeg(bigreal __x_deg){
        bigreal B26("26"), B15("15"), B180("180"), B8100("8100"), B1657("1657"), B930("930"), B324000("324000"),
            B19("19"), B1800("1800"), B1("1"), B360("360"), BDEN("524880000000"), B7200("7200"), B69300("69300"), B4500("4500");
        bigreal ONE("1");
        if(__x_deg.isNegative)
            return bigreal("-1")*brute::qpsindeg(big::abs(__x_deg));
        if(!(__x_deg== bigreal("0")))
            __x_deg = __x_deg - B360*big::floor(__x_deg/B360);
        if(__x_deg >bigreal("180")){
            return bigreal("-1")*qpsindeg(__x_deg - bigreal("180"));
        }
        bigreal x[8];
        x[0] = B1;
        for(int i=0;i<8;++i){
            x[i+1]=__x_deg*x[i];
        }
        // bigreal A0 = B810000 *(B1657+B930*BIG_SQRT_3);
        // bigreal A1 = B324000 *(B19 + B15*BIG_SQRT_3);
        // bigreal A2 = B1800*(B1+B15*BIG_SQRT_3);
        bigreal P = x[1]*(B180 - x[1]);
        bigreal::clean(P);
        bigreal D = B15*P*(P-B4500)*(P-B8100)*BIG_SQRT_3;
        bigreal::clean(D);
        bigreal NUM = bigreal("2") * P * (bigreal("13") * P - B69300)*(P - B7200) - B15*P*(P-B4500)*(P-B8100)*BIG_SQRT_3;
        
        bigreal::clean(NUM);
        return (NUM/BDEN).roundToDecimal(BN_DEC_TRIGPRECISION);
    }
    /**
     * @brief Quick Sine function with higher precision than qsin. Maximum error yield is about 0.0000338.
     * 
     * @param __x Angle in radians
     * @return bigreal 
     */
    inline bigreal qpsin(bigreal __x){
        return qpsindeg(__x * bigreal("180") / BIG_PI).roundToDecimal(BN_DEC_TRIGPRECISION);
    }

    /**
     * @brief High accuracy atan function using taylor series. Slower but with higher accuracy
     * 
     * @param __x 
     * @return bigreal 
     */
    inline bigreal atan(bigreal __x){

        bigreal ii("1"), two("2");
        if(__x > ii)
            return BIG_PI_2 - atan(ii/__x);
        bigreal ip = __x, x2 = __x*__x;
        bigreal s("0");
        bigreal sgn("1"), mo("-1");
        while(ii < ITER_ATAN){
            s = s + sgn*ip / ii;
            sgn = sgn * mo;
            ii = ii + two;
            ip = ip * x2;
            big::roundTo(s, BN_DEC_TRIGPRECISION);
            
            big::roundTo(ip, BN_DEC_TRIGPRECISION);
        }
        return s.roundToDecimal(BN_DEC_TRIGPRECISION);
    }
    /**
     * @brief Quick but less accuracy atan function using a quick aproximation. Error is about 0.05-0.02.
     * 
     * @param __x 
     * @return bigreal 
     */
    inline bigreal qatan(bigreal __x){
        return __x.arctan_e().roundToDecimal(BN_DEC_TRIGPRECISION);
    }
}
/**
 * @brief Namespace which includes function which should be used only on used on natural numbers
 * ; it includes : divide, gcd, mod
 */
inline namespace natural_num{
    inline bigreal divide(bigreal nat_a, bigreal nat_b){
        return big::from_bigint(big::to_bigint(nat_a)/big::to_bigint(nat_b));
    }
    inline bigreal mod(bigreal nat_a, bigreal nat_b){
        return (nat_a - divide(nat_a, nat_b)*nat_b);
    }
    
    inline bigreal gcd(bigreal nat_1, bigreal nat_2){
        nat_1 = big::floor(nat_1);
        nat_2 = big::floor(nat_2);
        bigreal t;

        while(nat_2 > BIG_ZERO){
            t =  nat_2;
            nat_2 = mod(nat_1, nat_2);
            nat_1 = t;
        }
        return nat_1;
    }
}
#endif