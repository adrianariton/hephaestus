#include "HSym.h"

HSym::HSym(VARIABLE_TYPES _type, std::string _name){
    this->type = _type;
    this->name = _name;
}

HSym::HSym(bigreal a){
    this->type = CONSTANT_SCALAR;
    this->properties = std::vector<VARIABLE_PROPERTIES>({CONSTANT});
}

HSym HSym::attach_properties(std::vector<VARIABLE_PROPERTIES> props){
    for(int i = 0; i < props.size(); ++i){
        (this->properties).push_back(props.at(i));
    }
}

HSym HSym::tensor_indices_down(std::vector<HSym> indices){
    for(int i = 0; i < tensor_indices.size(); ++i){
        (this->tensor_indices).push_back(tensor_indices.at(i));
        (this->tensor_indices_position).push_back(false);
    }
}

HSym HSym::tensor_indices_up(std::vector<HSym> indices){
    for(int i = 0; i < tensor_indices.size(); ++i){
        (this->tensor_indices).push_back(tensor_indices.at(i));
        (this->tensor_indices_position).push_back(true);
    }
}

/**
 * sum(prod(sum(prod(a ^ p) ^ p) ^ p, sum(prod(b ^ q) ^ q) ^ q) ^ 1) ^ 1
*/

HSym HSym::multiply_toexp(HSym exp1, HSym exp2, PROCESS_TYPE ptype){
    if(ptype != SIMPLIFY){
        HSym expr(EXPRESSION, _NILL);
        auto pair_1 = std::pair<HSym, HSym>(exp1, HSym(bigreal("1")));
        auto pair_2 = std::pair<HSym, HSym>(exp2, HSym(bigreal("1")));

        auto vector_12 = std::vector< std::pair<HSym, HSym> >({pair_1, pair_2});
        // vector of pairs (products)
        auto prod_pair = std::pair< std::vector< std::pair<HSym, HSym> >, HSym >({vector_12, bigreal("1")});

        auto sum_pair = std::vector< std::pair< std::vector< std::pair<HSym, HSym> >, HSym > >({prod_pair});

        auto sum_pair_at_pow = std::pair< std::vector< std::pair< std::vector< std::pair<HSym, HSym> >, HSym > > , HSym >(sum_pair, bigreal("1"));

        auto final_vek = std::vector< std::pair< std::vector< std::pair< std::vector< std::pair<HSym, HSym> >, HSym > > , HSym > >({sum_pair_at_pow});

        expr.sumprodpow_matrix = final_vek;
        expr.original_sumprodpow_matrix = final_vek;

        return expr;
    }
}


void HSym::log(HSym a) {
    
}