# HEPHAESTUS++

Hephaestus++ is a mathematical tool which has many components: FCO, BN and H(eph).

## BN - Big Numbers. 
Big Numbers includes big real numbers, big ints and big binary ints and works head to toe with the **big_cordic::** namespace which contains all the trig, inverse trig and hyperbolic functions, but also a quick exponential and others. Some of the basic functions (*floor*, *abs*, *to_decimal*, *to_binary* etc) will be found in the **big::** namespace
In a future update, they will all be included in the same namespace!

Using the **BNdecimal** (aka **bigreal**) type:
```cpp
    #include "hephaestus.cpp"
    // ...
    bigreal a("3.14"), b("2.33");
    bigreal sin_a = big_cordic::sin(a);
    bigreal a_pow_b = big_cordic::pow(a, b);
    bigreal ln_a = big_cordic::ln(a);
    bigreal exp_a = big_cordic::exp(a);

    bigreal arctan_a, hyp_a;
    big_cordic::calc_arctan(a, arctan_a, hyp_a);
    bigreal floor_a = big::floor(a); // used big::, because the floor function does not need high accuracy cordic computation
    bigreal ab_sum = a + b, ab_prod = a * b, ab_div = a / b;
```

There is also a natural number namespace (**natural_num**) which contains functions that take natural numbers as inputs (still using the **bigreal** type)

```cpp
    #include "hephaestus.cpp"
    // ...
    bigreal gcd_ab = natural_num::gcd(a, b);
    bigreal a_mod_b = natural_num::mod(a, b);
    bigreal a_quot_b = natural_num::divide(a, b);
```

There are also **bigint** and **bigint2** aka **BNint** and **BinaryBNint** respectively.

```cpp
    #include "hephaestus.cpp"
    // ...
    // see if string is number
    std::cout<< (big::is_number("123.32asa")) ;
    
    bigint2 binary_a = big::to_binary(a);
    bigreal same_a = big::to_decimal(binary_a);

```

### The suffix operator _big
It can be used to easily declare **bigreal** types. You need to include the **Heph_Utils.h** header.
```cpp
    #include "hephaestus.cpp"
    #include "Heph_Utils.h"
    // ...
    auto a = 12.34_big
```

### The **brute** namespace
The **brute** namespace consists of rough estimates of functions and is only for experimental purposes. It should not be used in practice, because the **big_cordic** namespace works much faster and has much more precision (100 digits).