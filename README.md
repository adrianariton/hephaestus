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
One can also declare **BNComplex** numbers (aka bigcomplex) and use the **hcomp** namespace for more complex-related functions. This namespace will soon receive an update.
```cpp
    #include "hephaestus.cpp"
    #include "Heph_Utils.h"
    // ...
    auto a = 12.34_big;
    bigcomplex z = a * I_big + 1.23_big;
```

### The **brute** namespace
The **brute** namespace consists of rough estimates of functions and is only for experimental purposes. It should not be used in practice, because the **big_cordic** namespace works much faster and has much more precision (100 digits).


## H - Hephaestus More
The H classes are new and some of them still in beta (**HSymbolic**), but provide methods that work with more abstract objects.

The classes which are the most important are **HTensor**, **HShape**, **HPoly**, **HRational**, **HSymbolic** and **MVExp**.
The last 2 will soon merge into one big class called **HSym** in a future update.

## HTensor and HShape
Tensors are very abstract (let's say matrix-like) objects. They are used in relativity. For now they are only implemented over the **long double** space, ~~but soon there will also be a **bigreal** version for more exact calculations~~. *UPDATE: **bigreal** support for tensors has been added Friday 4 November 2022. Please report any bugs!*

Example of creation of 2 *3x3* tensors (izomorph to the space of 3x3 matrices), and implementing the matrix product.

```cpp
    #include "hephaestus.cpp"
    #include "Heph_Utils.h"
    // ...

    std::vector<long double> tensor1_values = {1.1, 2.0, 3.2, 5.0, 6.2, 4.2, 8.8, 5.0, 8.3};
    std::vector<long double> tensor2_values = {-1.4, 1.0, 7.2, 5.7, 6.72, 4.62, 8.850, 7.7, 5.760};

    
    HTensor<long double> tensor1(tensor1_values, MATRIX_3X3);
    HTensor<long double> tensor2(tensor2_values, MATRIX_3X3);

    HTensor<long double> tensorproduct = HTensor<long double>::tensor_product(tensor1, tensor2);

    HEinsteinNotation<long double> einstein_notation_tensor1 = __(tensor1, "^alpha_beta");
    HEinsteinNotation<long double> einstein_notation_tensor2 = __(tensor2, "^beta_gamma");

    HEinsteinNotation<long double> einstein_notation_tensorprod = __m(einstein_notation_tensor1, einstein_notation_tensor2);

    // (*)

```

You can also use the **DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR** macro to easily define a product between 2 tensors. It declares a lambda-function which provided 2 tensors returns an indexed tensor (using Einstein's notation).

```cpp
    DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR(innerprod, REAL, _x, "_alpha", _y, "^alpha", _x.dim() == 1 && _y.dim()==1);
    DEF_TENSOR_PRODUCT_TO_INDEXED_TENSOR(matrixprod, REAL, _x, "^alpha_beta", _y, "^beta_gamma", _x.dim() == 2 && _y.dim()==2);
```

You can call them using the name preceded by **DEFN_**:

```cpp
    LET m1_mak = __(m1vals, MATRIX_3X3) DONE
    LET m2_mak = __(m2vals, MATRIX_3X3) DONE
    LET m1m2 = DEFN_matrixprod(m1_mak, m2_mak) DONE
```
[See about the __ macro [here](#The-__-and-__m-macros-and-the-HEPH-language)]


In this case Einstein notation is used and HEPHAESTUS provides an easy macro to convert from tensors to einstein notations and viceversa. It also provides an easy way to loop through array-like objects using a macro-based language included in the **Heph_Utils.h** header.

```cpp
    FOREACH(i, indices, IN_TENSOR, einstein_notation_tensorprod.tensor, 
        LOG einstein_notation_tensorprod.at(indices) NEAR "" DONE
    )
```

# The __ and __m macros and the HEPH language
#### As you saw before HEPHAESTUS++ also comes with a simplified macro-language. We will now look through the most important thigs you can do with this language.
## "__"
The __ macro is used as a converter tool. It is short for *_heph_predef_normalize*, and can be used to get the value of a tensor at some coordinates, or the conversion from a tensor to an EinsteinNotation, to build a tensor with a shape and a values-vector or to calculate the value of a **mve** function.

#### Simple example:

```cpp
    auto einstein_notation_tensor2 = __(tensor2, "^beta_gamma");
    // einstein_notation_tensor2 will be of type HEinsteinNotation<long double>
```
You can think of it as a kind of "join" function which takes some inputs and returns 
what it thinks you wanted to say.

More such oveloads will be added in a future release.

## "__m"

#### __m is used in a similar way, only it multiplies the entries

For example the [(*)](#HTensor-and-HShape) codebox is the same as

```cpp
    HEinsteinNotation<long double> einstein_notation_tensorprod = __m(tensor1, "^alpha_beta", tensor2, "^beta_gamma");
```
