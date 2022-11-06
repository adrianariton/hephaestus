#include "HSym.h"

HSym::HSym(VARIABLE_TYPES _type, std::string _name){
    this->type = _type;
    this->name = _name;
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