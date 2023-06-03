#include "HTensor.h"


HShape::HShape(std::vector<int> _d){
    this->axi_ilen = _d;
}

int HShape::dim(){
    return (this->axi_ilen).size();
}

int HShape::signature(){
    int s=1;
    for(int i=0; i<(*this).axi_ilen.size();++i){
        s*= (*this).axi_ilen.at(i);
    }
    return s;
}

