#ifndef HSYM_H
#define HSYM_H

#include "big.cpp"

enum VARIABLE_TYPES {SCALAR, TENSOR, INDEX, FUNCTION, LIMIT, SERIES, EXPRESSION, CONSTANT_SCALAR};
enum VARIABLE_PROPERTIES {SYMMETRIC, ANTISYMMETRIC, NILL, DEPENDANT, CONSTANT, LINEAR, QUADRATIC, MONOTONE, INCREASING, DECREASING};
enum PROCESS_TYPE {RECCURSIVE, FIRST_LEVEL, DEFAULT, SIMPLIFY};
enum OPERATION_TYPE {DISTRIBUTE, INVERT_DIVISION};
enum VALUE_AFFECTED_STAT{NOT_AFFECTED = 1, AFFECTED = 0, MAYBE_AFFECTED = 2};

#define _NILL "_"

class HSym {
    public:
        static VALUE_AFFECTED_STAT VALUE_AFFECTED; // if value of object was affected
        static HSym last;
        VARIABLE_TYPES type;
        bigreal number_value;
        std::string name;

        /*Every expression is a sum of (product over other (an expression to a power))*/
        std::vector < std::pair < std::vector< std::pair< std::vector< std::pair<HSym, HSym> >, HSym > >, HSym > > sumprodpow_matrix;
        /*\sum(\prod(a^p)^p)^p*/
        std::vector < std::pair < std::vector< std::pair< std::vector< std::pair<HSym, HSym> >, HSym > >, HSym > > original_sumprodpow_matrix;

        std::string latex_expression;
        std::vector<HSym> dependencies;
        std::vector<HSym> tensor_indices;
        std::vector<bool> tensor_indices_position;
        std::vector<VARIABLE_PROPERTIES> properties; // true if up, false if down

        HSym(VARIABLE_TYPES, std::string);
        HSym(bigreal);

        bool is_addition_leaf();
        bool is_addition_and_product_leaf();
        bool is_leaf();

        HSym tensor_indices_up(std::vector<HSym> indices);
        HSym tensor_indices_down(std::vector<HSym> indices);
        HSym attach_properties(std::vector<VARIABLE_PROPERTIES> props);

        HSym derivate(HSym wrt);
        HSym distribute(HSym expression);
        HSym replace(HSym exp1, HSym exp2, PROCESS_TYPE ptype = DEFAULT);

        HSym add_toexp(HSym exp1, HSym exp2, PROCESS_TYPE ptype = DEFAULT);
        HSym multiply_toexp(HSym exp1, HSym exp2, PROCESS_TYPE ptype = DEFAULT);

        HSym clean(PROCESS_TYPE ptype = DEFAULT);

        static void log(HSym a);
        

};

#endif