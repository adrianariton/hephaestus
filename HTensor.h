#ifndef HTENSORS_H
#define HTENSORS_H

#include "Greek.h"
#include <vector>

inline bool HTENS_COUT_DEPTH_DIM = false;

template <typename T>
inline void htlog_vect(std::vector<T> _vk){
    std::cout<<"\n[";
    for(int i=0;i<_vk.size(); ++i){
        std::cout<<_vk.at(i)<<", ";
    }
    std::cout<<"]\n";
}
template<class T>
std::vector<T> insertElements_vek(std::vector<T> const& v, std::initializer_list< std::pair<std::size_t, T> > new_elements) {
    std::vector<T> u;
    u.reserve(v.size() + new_elements.size());
    auto src = v.begin();
    size_t copied = 0;
    for(auto const& element : new_elements) {
        auto to_copy = element.first - copied;
        auto src_end = src + to_copy;
        u.insert(u.end(), src, src_end);
        src = src_end;
        copied += to_copy;
        u.push_back(element.second);
    }
    u.insert(u.end(), src, v.end());
    return u;
}

template <typename TI>
inline void deleteAll_vek(std::vector<TI>& data, const std::vector<int>& deleteIndices)
{
    using namespace std;
    vector<bool> markedElements(data.size(), false);
    vector<TI> tempBuffer;
    tempBuffer.reserve(data.size()-deleteIndices.size());

    for (vector<int>::const_iterator itDel = deleteIndices.begin(); itDel != deleteIndices.end(); itDel++)
        markedElements[*itDel] = true;

    for (size_t i=0; i<data.size(); i++)
    {
        if (!markedElements[i])
            tempBuffer.push_back(data[i]);
    }
    data = tempBuffer;
}

class HShape{
    public:
        std::vector<int> axi_ilen;
        HShape(std::vector<int> _d);
        int dim();
        int signature();
};
template <typename T>
class HTensor{
    private:
        T value;
        int space_nd;
    public:
        std::vector< HTensor<T> > subTensors;
        T* __meta;
        HTensor(T _value){
            std::vector<HTensor<T> > empty;
            this->subTensors = empty;

            space_nd = 0;
            this->value = _value;
        }

        HTensor(){
            this->space_nd = 0;
            this->value = (T)(0);
        }

        HTensor(std::vector<T> _values, HShape _shape){
            if(_shape.axi_ilen.size() == 0)
                (*this) =  HTensor(_values.at(0));
            std::vector< HTensor <T> > __buffer;
            for(int i=0; i< _values.size();++i){
                __buffer.push_back(HTensor(_values.at(i)));
            }

            if(__buffer.size() != _shape.signature())
                throw std::invalid_argument("Unsufficient or too many values provided for tensor!");

            for(int i = _shape.dim()-1; i>=0; --i){
                int _len = _shape.axi_ilen.at(i);
                std::vector< HTensor <T> > __hit;

                /** Group all elems in __buffer int _len length groups*/
                if(_len != 0 ){
                    for(int bi=0; bi<__buffer.size(); bi+=_len){
                        std::vector< HTensor <T> > __group;
                        for(int t = 0; t< _len;++t){
                            __group.push_back(__buffer.at(t + bi));
                        }

                        __hit.push_back(HTensor(__group));
                    }
                    __buffer = __hit;
                }
                
            }
            *this = HTensor(__buffer).subTensors.at(0);
        }


        HTensor(std::vector< HTensor<T> > _subTensors){
            int n_dim = _subTensors.at(0).space_nd;

            for(size_t i = 0; i<_subTensors.size(); ++i){
                if(n_dim != _subTensors.at(i).space_nd)
                    throw std::invalid_argument("Conflicting Tensor shapes cannot be merged into a new Tensor");
            }
            this->space_nd = n_dim + 1;
            this->subTensors = _subTensors;
        }

        HTensor<T>& operator[] (size_t _index){
            return (this->subTensors).at(_index);
        }

        // HTensor<T>& operator[] (std::vector<int> _position){
        //     if(_position.size() == 1)
        //         return this[_position.at(0)];
        //     else {
        //         int first = _position.at(0);
        //         _position.erase(_position.begin());
        //         return this[first][_position];
        //     }
        // }
        HTensor<T> operator[] (std::vector<int> _position){
            HTensor<T> __buff = (*this);
            for(int i=0;i<_position.size(); ++i){
                __buff = __buff[_position.at(i)];
            }
            return __buff;
        }
        HTensor<T>& at (std::vector<int> _position){
            if(_position.size() == 0){
                return *this;
            }
            if(_position.size() == 1){
                return (this->subTensors).at(_position.at(0));
            } else {
                int q = _position.at(_position.size() -1);
                _position.pop_back();
                return ((this->at(_position)).subTensors).at(q);
            }
        }
        int dim(){
            return this->space_nd;
        }

        T& val(){
            if(this->space_nd != 0)
                throw std::invalid_argument("Tensors which are not constant have no value! If you are using trees, use meta instead");
            return this->value;
        }

        std::vector< HTensor<T> > children(){
            return this->subTensors;
        }

        HTensor<T> first_child(){
            return (this->children()).at(0);
        }

        friend std::ostream& operator <<(std::ostream& os, HTensor<T> _tensor){
            if(_tensor.dim() == 0)
                os<<" "<<_tensor.val()<<" ";
            else
                for(int i=0; i<_tensor.children().size(); ++i){
                    os<<" [";
                    os<<_tensor.children().at(i);
                    os<<"] ";
                }
            if(HTENS_COUT_DEPTH_DIM)
                os<<":"<<_tensor.dim();
            return os;
        }

        std::vector<int> measures(){
            std::vector<int> ms;
            HTensor<T> __buff = (*this);
            while(__buff.dim() > 0){
                ms.push_back(__buff.children().size());
                __buff = __buff.first_child();
            }
            return ms;
        }

        int measures(size_t axis){
            return (*this).measures().at(axis);
        }

        int coord_on_axis_i(int i, int nthpos, std::vector<int> __measures){
            int __pim1 = 1;
            for(int it=0; it< (i); ++it){
                __pim1 *= __measures.at(it);
                
            }
            int __pi = __measures.at(i);
            return ( (nthpos % (__pim1 * __pi)) / (__pim1) );
        }

        std::vector<int> coords_forindex(int index, std::vector<int> __measures){
            if(__measures.size() == 0)
                return std::vector<int>({});
            std::vector<int> __bar;
            for(int i=0; i< (*this).dim(); ++i){
                __bar.push_back(coord_on_axis_i(i, index, __measures));
            }
            return __bar;
        }

        // HTensor<T>& slice_valat(int axis, size_t pos, std::vector<int> _pos_v){
        //     _pos_v.insert(_pos_v.begin() + axis, pos);
        //     return this[_pos_v];
        // }

        // HTensor<T>& slice(int axis, size_t pos){
            
        // }

        // static void fill_tpr( HTensor<T>& _th , HTensor<T> __X, HTensor<T> __Y, int __xsz){
        //     if(_th.dim() == 0){
        //         _th = __X.val() * __Y.val();
        //     } else {
        //         for(int j = 0; j<__X.subTensors.size(); ++j){
        //             for(int k = 0; k< __Y.subTensors.size(); ++k){
        //                 fill_tpr(_th[j][k], __X[j], __Y[k], __xsz);
        //             }
        //         }
                
        //     }
        // }

        static HTensor<T> tensor_product(HTensor<T> __X, HTensor<T> __Y){
            std::vector<int> __prodshape_vec = __X.measures();
            std::vector<int> __Xshape_vec = __X.measures();
            std::vector<int> __Yshape_vec = __Y.measures();
            for(int yit = 0; yit < __Yshape_vec.size(); ++yit){
                __prodshape_vec.push_back(__Yshape_vec.at(yit));
            }

            HShape __prodshape(__prodshape_vec);
            std::vector<T> _repl, _donc;
            
            for(int i=0; i< __prodshape.signature(); ++i){
                _repl.push_back( (T)(0) );
            }

            HTensor<T> __buff(_repl, __prodshape);
            int __XDIM = __X.dim(), __YDIM = __Y.dim();
            std::vector<int> __m = __buff.measures();
            //std::cout<<"\n"<<__buff<<"\n";
            for(int i=0; i< __prodshape.signature(); ++i){
                std::vector<int> __coords_ofi = __buff.coords_forindex(i , __m);
                std::vector<int> __Xcds, __Ycds;
                for(int _j = 0; _j < __XDIM; ++ _j)
                    __Xcds.push_back(__coords_ofi.at(_j));
                for(int _j = 0; _j < __YDIM; ++ _j)
                    __Ycds.push_back(__coords_ofi.at(__XDIM + _j));
                _donc.push_back( __X[__Xcds].val() * __Y[__Ycds].val() );
            }
            HTensor<T> __ret(_donc, __prodshape);
            return __ret;
        }


        // HTensor<T>& operator=(const HTensor<T>& other){
        //     std::cout<<other.space_nd<<" "<<(*this).space_nd<<" ";
        //     if(other.space_nd != (*this).space_nd )
        //         throw std::invalid_argument("Cannot assign different dimensions Tensors to oneanother");
        //     this->space_nd = other.space_nd;
        //     this->subTensors = other.subTensors;
        //     this->value = other.value;
        //     this->__meta = other.__meta;

        //     return *this;
        // }

};
inline auto METRIC_LAMBDA = [](int x, int y) {  return int(x==y); };

template <typename T>
class HEinsteinNotation{
    public:
    HTensor<T> tensor;
    std::vector<std::string> indices;
    std::vector<bool> is_up;
    HEinsteinNotation(HTensor<T> tensss, std::vector<std::string> _indices, std::vector<bool> _s_status){
        tensor = tensss;
        indices = _indices;
        is_up = _s_status;
    }
    int dim(){
        return this->tensor->dim();
    }
    HEinsteinNotation lower_index(std::string to_lower, std::string new_name){
        HEinsteinNotation _h = (*this);
        for(int i=0; i<_h.indices.size(); ++i){
            if(_h.indices.at(i) == to_lower && _h.is_up.at(i) == true){
                _h.is_up.at(i) = false;
                _h.indices.at(i) = new_name;
            }
        }
        return _h;
    }
    HEinsteinNotation raise_index(std::string to_raise, std::string new_name){
        HEinsteinNotation _h = (*this);
        for(int i=0; i<_h.indices.size(); ++i){
            if(_h.indices.at(i) == to_raise && _h.is_up.at(i) == false){
                _h.is_up.at(i) = true;
                _h.indices.at(i) = new_name;
            }
        }
        return _h;
    }

    HEinsteinNotation fix_index_to_index(size_t to_fix_ind, size_t to_index_ind){
       
        HShape tensor_shape = HShape(tensor.measures());

        if(to_fix_ind == -1 || to_index_ind == -1) throw std::invalid_argument("Indices not found");
        std::vector<bool> is_up_ = (*this).is_up;
        std::vector<std::string> indices_of_new = (*this).indices;

        deleteAll_vek(is_up_, {(int)to_fix_ind,(int)to_index_ind});


        // is_up_.erase(is_up_.begin() + to_fix_ind);
        // is_up_.erase(is_up_.begin() + to_index_ind);
        //std::cout<<"\nerased\n";


        deleteAll_vek(indices_of_new, {(int)to_fix_ind, (int)to_index_ind});

        // indices_of_new.erase(indices_of_new.begin() + to_fix_ind);
        // indices_of_new.erase(indices_of_new.begin() + to_index_ind);
         //       std::cout<<"\nerased2\n";

        std::vector<int> vek_tensorshape = tensor_shape.axi_ilen;
        int size_of_contracted_dim = -1;
        if(vek_tensorshape.at(to_fix_ind) != vek_tensorshape.at(to_index_ind))
            throw std::invalid_argument("Cannot contract non-symmetric portions of tensor!");
        else size_of_contracted_dim = vek_tensorshape.at(to_fix_ind);
        
        //for(int kk=0; kk < vek_tensorshape.size(); ++kk) std::cout<<vek_tensorshape.at(kk);
        //std::cout<<"\n\n";


        deleteAll_vek(vek_tensorshape, {(int)to_fix_ind, (int)to_index_ind});

        // vek_tensorshape.erase(vek_tensorshape.begin() + to_fix_ind);
        // vek_tensorshape.erase(vek_tensorshape.begin() + to_index_ind);
         //       std::cout<<"\nerased3\n";

        std::vector<T> vals_for_res;
        for(int i=0; i<HShape(vek_tensorshape).signature(); ++i){
            vals_for_res.push_back( (T)(0) );
        }
        //std::cout<<"\ngot to bigfor\n";
        HTensor<T> _res_tensor(vals_for_res, HShape(vek_tensorshape) );
        //std::cout<<_res_tensor<<"RESTENS";
        for(int i=0; i<HShape(vek_tensorshape).signature(); ++i){
            //std::cout<<"\n"<<i<<" of "<<HShape(vek_tensorshape).signature()<<"\n";
            std::vector<int> coords_in_res = _res_tensor.coords_forindex(i, vek_tensorshape);
           // std::cout<<coords_in_res.size()<<"\n";
            std::vector<int> coords_in_old = coords_in_res;

            if(to_fix_ind > to_index_ind){
                std::swap(to_fix_ind, to_index_ind);
            }
             if(to_fix_ind > coords_in_old.size())
                 coords_in_old.push_back(0), to_fix_ind = coords_in_old.size()-1;
             else
                 coords_in_old.insert(coords_in_old.begin() + to_fix_ind, 0);
        
             if(to_index_ind > coords_in_old.size())
                 coords_in_old.push_back(0), to_index_ind = coords_in_old.size() - 1;
             else
                 coords_in_old.insert(coords_in_old.begin() + to_index_ind, 0);
            //     std::cout<<"\nvects:";
            // htlog_vect(coords_in_old);
            // htlog_vect(coords_in_res);
            // std::cout<<"\n";
            //std::cout<<"size_contr_dim: "<<size_of_contracted_dim<<"\n";
            if(_res_tensor.at(coords_in_res).val() == (T)(0))
            for(int _si = 0; _si<size_of_contracted_dim; ++_si){
                coords_in_old.at(to_fix_ind) = _si;
                coords_in_old.at(to_index_ind) = _si;
       
                T _thisval = (*this).at(coords_in_old);
                HTensor<T> _aux = HTensor<T>(_res_tensor.at(coords_in_res).val() + (*this).at(coords_in_old));
                
                _res_tensor.at(coords_in_res) = _aux;
            }
        }
        // - std::cout<<"AOOAOA  ";
        return HEinsteinNotation(_res_tensor, indices_of_new, is_up_);

    }
    static HEinsteinNotation tens_product(HEinsteinNotation lhs, HEinsteinNotation rhs){
        HTensor<T> tns_prd = HTensor<T>::tensor_product(lhs.tensor, rhs.tensor);
        std::vector<std::string> _indices = lhs.indices;
        std::vector<bool> _ups = lhs.is_up;
        for(int i=0; i<rhs.indices.size(); ++i){
            _indices.push_back(rhs.indices.at(i));
            _ups.push_back(rhs.is_up.at(i));
        }
        return HEinsteinNotation(tns_prd, _indices, _ups);
    }
    static HEinsteinNotation reduce(HEinsteinNotation tens_en){
        int sw=0;
        for(int i=0; i< tens_en.indices.size(); ++i){
                for(int j=0; j< tens_en.indices.size(); ++j){
                    if(tens_en.is_up.at(i) && !tens_en.is_up.at(j) && tens_en.indices.at(i) == tens_en.indices.at(j)){
                        std::cout<<"\n"<<tens_en.indices.at(i)<<" "<<i<<" "<<j<<"\n";
                        sw=1;
                    }
                }
            
        }
        //std::cout<<sw;
        if(sw == 0) return tens_en;
        int qi=-1, qj=-1;
        for(int i=0; i< tens_en.indices.size(); ++i){
                for(int j=0; j< tens_en.indices.size(); ++j){
                    if( tens_en.is_up.at(i) && !tens_en.is_up.at(j) && tens_en.indices.at(i) == tens_en.indices.at(j)){
                      //  std::cout<<"\nshallreturn\n";
                        qi = i;
                        qj=j;
                    }
                }

           
        }
        return HEinsteinNotation::reduce( tens_en.fix_index_to_index(qi, qj) );

    }
    static HEinsteinNotation to_upper(HEinsteinNotation entens, std::vector<int>& indices_to_lower){
        indices_to_lower = {};
        for(int i=0; i<entens.indices.size(); ++i){
            if(!entens.is_up.at(i)){
                entens.raise_index( entens.indices.at(i) , entens.indices.at(i));
                indices_to_lower.push_back(i);
            }
        }
        return entens;
    }
    
    
    static T value_at_gd( HEinsteinNotation entens, std::vector<int> corresp_coord, std::vector<int> ms){
        std::vector<int> indices_to_lwr = {};
        HEinsteinNotation uppd = HEinsteinNotation::to_upper(entens, indices_to_lwr);
        
        if(indices_to_lwr.size() == 0) return entens.tensor.at(corresp_coord).val();
        T val = 0;
        for(int i=0; i<indices_to_lwr.size(); ++i){
            int index_to_lwr = indices_to_lwr.at(i);
            std::string index_name = entens.indices.at(index_to_lwr);
            int cc_ind = corresp_coord.at(index_to_lwr);
            for(int di = 0; di<ms.at(index_to_lwr); ++di){
                HEinsteinNotation _raisedone = entens.raise_index(index_name, index_name);
                std::vector<int> cc = corresp_coord;
                cc.at(index_to_lwr) = di;
                val += (T)(METRIC_LAMBDA(cc_ind, cc.at(index_to_lwr))) * HEinsteinNotation::value_at_gd(_raisedone, cc, ms);
            }
            return val;
        }
        // SOLVED --  BUG
    }

    T at(std::vector<int> coords){
        return HEinsteinNotation::value_at_gd( (*this) , coords, (*this).tensor.measures() );
    }

    HShape shape(){
        return HShape((*this).tensor.measures());
    }

    void log(){
        std::cout<<"\ntens_up(";
        for(int i=0; i<(*this).indices.size(); ++i){
            if((*this).is_up.at(i))
                std::cout<<(*this).indices.at(i)<<",";
            else std::cout<<"--,";
        }
        std::cout<<")down(";
        for(int i=0; i<(*this).indices.size(); ++i){
            if(!(*this).is_up.at(i))
                std::cout<<(*this).indices.at(i)<<",";
            else std::cout<<"--,";
        }
        std::cout<<")\n";
    }

    static HEinsteinNotation tens_multiply(HEinsteinNotation lhs, HEinsteinNotation rhs){
        HEinsteinNotation tprod = HEinsteinNotation::tens_product(lhs, rhs);
        return HEinsteinNotation::reduce(tprod);
    }

    friend HEinsteinNotation operator * (HEinsteinNotation lhs, HEinsteinNotation rhs){
        return HEinsteinNotation::tens_multiply(lhs, rhs);
    }
    // friend HTensor<T> operator * (HEinsteinNotation lhs, HEinsteinNotation rhs){
    //     int __uldr_eq = 0, __uldr_pair_u1 = -1, __uldr_pair_d2 = -1;
    //     for(int __ui = 0; __ui < lhs.up_indices.size(); ++__ui){
    //         for(int __di = 0; __di < rhs.down_indices.size(); ++__di)
    //             if(lhs.up_indices(__ui) == rhs.down_indices(__di)){
    //                 __uldr_eq++;
    //                 __uldr_pair_u1 = __ui;
    //                 __uldr_pair_d2 = __di;
    //             }
                    
    //     }
    //     //^^ not like this!, Add Metric and a contract or swap indices  fn;        
    // }
};

#endif