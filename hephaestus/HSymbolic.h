#ifndef HSYMBOLIC_H
#define HSYMBOLIC_H
#include <iostream>
#include <string>
#include <map>
#define NO_FUNC ""
#define NO_VAL ""
#include "big.cpp"
#include <unordered_map>
#include "mvex.cpp"
inline bool M_OPEN = true;

inline void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
{
    size_t pos = std::string::npos;
    // Search for the substring in string in a loop untill nothing is found
    while ((pos  = mainStr.find(toErase) )!= std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}
inline void eraseAllSubStr(std::string & mainStr, const std::string & toErase, const std::string & notPercBy)
{
    size_t pos = std::string::npos;
    // Search for the substring in string in a loop untill nothing is found
    while ((pos  = mainStr.find(toErase) )!= std::string::npos)
    {
        // If found then erase it from string
        
        char _c;
        if(pos > 1)
            _c = mainStr.at(pos - 1);
        else _c = '_';
        if(!( (notPercBy.find(_c) )!= std::string::npos )) // if not perceded by notpercby chars
        mainStr.erase(pos, toErase.length());
    }
}
class HSymbolic{
    private:
        bool base;
        std::string value;
    public: 
        std::string func;
        std::map<HSymbolic, long double> ring_elements;
        static std::vector< std::pair<HSymbolic, HSymbolic> > RULES;

        HSymbolic(){
            ring_elements={};
            base = false;
            func = NO_FUNC;
            value = NO_VAL;
        }
        HSymbolic(std::map<HSymbolic, long double> ring){
            ring_elements=ring;
            base = false;
            func = NO_FUNC;
            value = NO_VAL;
        }
        HSymbolic(std::map<HSymbolic, long double> ring, bool _b){
            ring_elements=ring;
            base = _b;
            func = NO_FUNC;
            value = NO_VAL;
        }
        HSymbolic(std::map<HSymbolic, long double> ring, std::string _function){
            ring_elements=ring;
            base = false;
            func = _function;
            value = NO_VAL;
        }
        HSymbolic(std::map<HSymbolic, long double> ring, bool _b, std::string _function){
            ring_elements=ring;
            base = _b;
            func = _function;
            value = NO_VAL;
        }
        HSymbolic(std::string val, bool _q){
            ring_elements={};
            base = true;
            func = NO_FUNC;
            value = val;
        }
        HSymbolic(std::string val){
            ring_elements={};
            base = true;
            func = NO_FUNC;

            if(big::is_number(val) && val != "1"){
                long double _n = std::stold(val);
                ring_elements = {{HSymbolic("1"), _n}};
                base = false;

            } else {
                ring_elements = {{HSymbolic(val, true), (long double)1}};

            }
            *this = (*this)._getv();
        }
        HSymbolic(long double _n){
            ring_elements={};
            base = true;
            func = NO_FUNC;

                ring_elements = {{HSymbolic("1"), _n}};
                base = false;

        }
        static void rule(HSymbolic a, HSymbolic b){
            HSymbolic::RULES.push_back({a, b});
        }
        void set(HSymbolic _index, long double _value){
            HSymbolic _root = _index.ring_elements.begin()->first;
            if(_index.ring_elements.size()  > 1)
                throw std::invalid_argument("Expression could not be converted to ring element!");
            if(_index.ring_elements.begin()->second != 1){
                throw std::invalid_argument("Expression could not be converted to ring element! Get rid of multiplier! Replace n*(exp) by exp.");
            }
            _index = _root;
            if((this->ring_elements).count(_index) > 0){
                (this->ring_elements).at(_index) = _value;
            } else {
                (this->ring_elements).insert({_index, _value});
            }
        }
        void erase(HSymbolic _index){
            HSymbolic _root = _index.ring_elements.begin()->first;
            if(_index.ring_elements.size()  > 1)
                throw std::invalid_argument("Expression could not be converted to ring element!");
            if(_index.ring_elements.begin()->second != 1){
                throw std::invalid_argument("Expression could not be converted to ring element! Get rid of multiplier! Replace n*(exp) by exp.");
            }
            _index = _root;
            if((this->ring_elements).count(_index) > 0){
                (this->ring_elements).at(_index) = 0;
            }
        }
        void inc(HSymbolic _index, long double _value){
            HSymbolic _root = _index.ring_elements.begin()->first;
            if(_index.ring_elements.size()  > 1)
                throw std::invalid_argument("Expression could not be converted to ring element!");
            if(_index.ring_elements.begin()->second != 1){
                throw std::invalid_argument("Expression could not be converted to ring element! Get rid of multiplier! Replace n*(exp) by exp.");
            }
            _index = _root;
            if((this->ring_elements).count(_root) > 0){
                (this->ring_elements).at(_root) += _value;
            } else {
                (this->ring_elements).insert({_root, _value});
            }
        }
        long double get(HSymbolic _index){
            HSymbolic _root = _index.ring_elements.begin()->first;
            if(_index.ring_elements.size()  > 1)
                throw std::invalid_argument("Expression could not be converted to ring element!");
            if(_index.ring_elements.begin()->second != 1){
                throw std::invalid_argument("Expression could not be converted to ring element! Get rid of multiplier! Replace n*(exp) by exp.");
            }
            if((this->ring_elements).count(_root) > 0){
                return (this->ring_elements).at(_root);
            } else {
                return 0;
            }
        }
        std::string val(){
            long double _c;
             return this->strip(_c).strip(_c).strip(_c).value;
        }
        HSymbolic f(std::string _f){
            HSymbolic _x = (*this);
            _x.func = _f;
            return _x;
        }
        HSymbolic strip(){
            if((this->ring_elements).size() != 1)
                return (*this);
            if((this->ring_elements).size() == 1 && (this->ring_elements).begin()->second == 1)
            return (this->ring_elements).begin()->first;
            else return (*this);
        }
        HSymbolic strip(long double& _c){
            _c = 1.0;
            if((this->ring_elements).size() != 1)
                return (*this);
            if((this->ring_elements).size() == 1){
                            _c = (this->ring_elements).begin()->second;

            return (this->ring_elements).begin()->first;

            }
            else return (*this);
        }
        HSymbolic hug(){
            return HSymbolic({{(*this), 1}});
        }
        HSymbolic hug(std::string f){
            return HSymbolic({{(*this), 1}}, f);
        }
        void logmap(){

            if(this->value != NO_VAL && this->value != ""){
                std::cout<<"\n{ <VAR/CONST> \n    "<<(this->value)<<"\n }\n";
                return;
            }
            std::cout<<"\n{  <"<<(this->func)<<", "<<(this->ring_function())<<", "<<(this->strip().func)<<">\n";
            for(auto it = this->ring_elements.begin(); it!=(this->ring_elements.end()); ++it){
                std::cout<<"    { "<<(it->first)<<": "<<(it->second)<<" },\n";
            }
            std::cout<<"}\n";
        }
        static std::string to_string(HSymbolic _x, std::vector< std::string >& vars){
            if(_x.ring_elements.size() == 0){
                if(std::find(vars.begin(), vars.end(), _x.value) == vars.end() && _x.value!="1")
                vars.push_back(_x.value);
                return (_x.value);
            } else if(_x.func == "*" || _x.func == "/"){
                std::map<HSymbolic, long double>::iterator xitr, yitr;

                int q = 0;
                std::string s="";
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first, vars)+"))");
                    if(q==1)
                        s+=(_x.func);
                    if(q==2)
                        break;
                }
                if(q==1){
                    xitr = _x.ring_elements.begin();
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first, vars)+"))");

                }
                return s;
            } else if(_x.func != NO_FUNC){
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                std::string s="";

                int q = 0;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;

                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first, vars)+"))");
                    if(q==1)
                        break;
                }
                return s;
            } else {
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                                    std::string s="";

                int q = 0;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first, vars)+"))");
                    if(q==_x.ring_elements.size())
                        break;
                    s+=" + ";
                }
                return s;
            } 
        }
        static std::string to_string(HSymbolic& _x, std::vector< std::string >& vars, std::pair< std::string, std::string > p){
            if(_x.ring_elements.size() == 0){
                if(_x.value == p.first){
                    _x.value = p.second;
                }
                if(std::find(vars.begin(), vars.end(), _x.value) == vars.end() && _x.value!="1")
                vars.push_back(_x.value);
                return (_x.value);
            } else if(_x.func == "*" || _x.func == "/"){
                std::map<HSymbolic, long double>::iterator xitr, yitr;

                int q = 0;
                std::string s="";
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string((HSymbolic&)(xitr->first), vars, p)+"))");
                    if(q==1)
                        s+=(_x.func);
                    if(q==2)
                        break;
                }
                if(q==1){
                    xitr = _x.ring_elements.begin();
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string((HSymbolic&)(xitr->first), vars, p)+"))");

                }
                return s;
            } else if(_x.func != NO_FUNC){
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                std::string s="";

                int q = 0;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;

                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string((HSymbolic&)(xitr->first), vars, p)+"))");
                    if(q==1)
                        break;
                }
                return s;
            } else {
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                                    std::string s="";

                int q = 0;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string((HSymbolic&)(xitr->first), vars, p)+"))");
                    if(q==_x.ring_elements.size())
                        break;
                    s+=" + ";
                }
                return s;
            } 
        }
        std::vector< std::string > vars(){
            std::vector< std::string > v={};
            std::string s =  HSymbolic::to_string(*this, v);
            return v;
        }
        HSymbolic tosame_denominator(){
            
        }
        HSymbolic clean(){
            HSymbolic _x = (*this);
            if(_x.strip().ismultiply_ring() && _x.ring_elements.begin()->second == 0 && _x.ring_elements.size() == 0)
                return HSymbolic("1");
            bool k = false;
            if(_x.ismultiply_ring()){
               for(auto xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    if( (xitr->second) == 1 && ( (xitr->first) == HSymbolic("1")  ||  (xitr->first) == HSymbolic(1) )){
                        _x.ring_elements.erase(xitr);
                    }
                } 
                k=true;
                if(_x.ring_elements.size() == 0)
                    return HSymbolic("1");
            } 
            for(auto xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                if( (xitr->second) == 0 ){
                    _x.ring_elements.erase(xitr);
                }
            }
            if(_x.ring_elements.size() == 0 && k)
                return HSymbolic("1");
            return _x;
        }

        static HSymbolic add(HSymbolic _x, HSymbolic _y, long double _px, long double _py){
            std::map<HSymbolic, long double>::iterator xitr, yitr;
            for(yitr = _y.ring_elements.begin(); yitr != _y.ring_elements.end(); ++yitr){
                (yitr->second) = (yitr->second) * _py;
                //std::cout<<"{"<<(yitr->first)<<", "<<(yitr->second)<<"}\n";
            }
            for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                //std::cout<<"{"<<(xitr->first)<<", "<<(xitr->second)<<"}\n";

                if(_y.ring_elements.count((xitr->first)))
                _y.ring_elements.at((xitr->first)) += (xitr->second) * _px;
                else 
                _y.ring_elements.insert({(xitr->first), (xitr->second) * _px});
            }
            
            return _y.clean();
        }
        static HSymbolic subs(HSymbolic _x, HSymbolic _y, long double _px, long double _py){
            return HSymbolic::add(_x, _y, _px , (-_py)).clean();
        }
        static HSymbolic applyfunc(std::string _func, HSymbolic _x, bool open){
            if(!open){
                _x.func = _func;
               
                return HSymbolic({{_x, (long double)1}}).clean();
            }
            else {
                throw std::invalid_argument("Open paranthesys not yet supported for fcts!");
                // std::map<HSymbolic, long double>::iterator itr;

                // for (itr = _x.ring_elements.begin(); itr != _x.ring_elements.end(); ++itr) {
                    
                // }
                return _x.clean();
            }     
        }
        static HSymbolic applyfunc(std::string _func, HSymbolic _x){
            bool open = false;
            if(!open){
                _x.func = _func;
                return HSymbolic({{_x, (long double)1}});
            }
            else {
                throw std::invalid_argument("Open paranthesys not yet supported for fcts!");
                // std::map<HSymbolic, long double>::iterator itr;

                // for (itr = _x.ring_elements.begin(); itr != _x.ring_elements.end(); ++itr) {
                    
                // }
                return _x.clean();
            }     
        }
        bool ismultiply_ring(){
            auto  _x = (*this);
            if(_x.value != NO_VAL)
                return false;
            if(_x.func == "*")
                return true;
            if(_x.func != "*" && _x.ring_elements.size() != 1)
                return false;
            return (_x.ring_elements.begin()->first.func == "*");
        }
        bool isvar_or_multiply_ring(){
            if(this->value != NO_VAL)
                return true;
            return this->strip().ismultiply_ring();
        }
        bool is_normal(){
            return (this->func == NO_FUNC);
        }
        HSymbolic _getv(){
            return this->hug("*").hug();
        }
        std::string ring_function(){
            auto  _x = (*this);
            return (_x.ring_elements.begin()->first.func);
        }
        HSymbolic multiply_pushroot(HSymbolic rootf){
            auto _x = (*this);
            
            HSymbolic _y = _x.ring_elements.begin()->first;
             
            if(_x.func == "*"){
                _y =  _x;
            }           
            // std::cout<<"\nrootf bef: "<<rootf;
        //   rootf.logmap();
            if(rootf.value != NO_VAL){
                auto sd = rootf.value;
                rootf = HSymbolic({{rootf, 1}});
                if(sd == "1")
                    rootf = HSymbolic(1);
            }
                    //   std::cout<<"_Ybef:";
                    //     std::cout<<_y;
                    //     std::cout<<"\nrootf: ";
            // rootf.logmap();
            HSymbolic l = rootf.ring_elements.begin()->first ;
            // std::cout<<"   -l: "<<l<<"\n\n";
        //    _y.logmap();
             if(_y.ring_elements.count(rootf.ring_elements.begin()->first) > 0){
                _y.ring_elements.at( rootf.ring_elements.begin()->first ) += 1;
            } else {
                _y.ring_elements.insert( {rootf.ring_elements.begin()->first, 1} );
            }
        //                            std::cout<<"_Yaf:";
        //                std::cout<<_y;

        //    _y.logmap();

            _x = HSymbolic({{_y, 1}});
            _x = ((HSymbolic)(_y.ring_elements.begin()->first));
            if(_y.func !="*" && _y.ring_function() != "*")
                return _x.clean();
        //    std::cout<<"_X:";
        //    std::cout<<_x;
        //    _x.logmap();
            return _y.clean();
        }
        HSymbolic multiply_pushroot(HSymbolic rootf, int _nd){
            auto _x = (*this);
            
            HSymbolic _y = _x.ring_elements.begin()->first;
             
            if(_x.func == "*"){
                _y =  _x;
            }           //std::cout<<"\nrootf bef: "<<rootf;
          //  rootf.logmap();
            if(rootf.value != NO_VAL){
                auto sd = rootf.value;
                rootf = HSymbolic({{rootf, 1}});
                if(sd == "1")
                    rootf = HSymbolic(1);
            }
                    //   std::cout<<"_Ybef:";
                    //     std::cout<<_y;
                    //     std::cout<<"\nrootf: ";
            // rootf.logmap();
            HSymbolic l = rootf.ring_elements.begin()->first ;
            // std::cout<<"   -l: "<<l<<"\n\n";
         //  _y.logmap();
             if(_y.ring_elements.count(rootf.ring_elements.begin()->first) > 0){
                _y.ring_elements.at( rootf.ring_elements.begin()->first ) += _nd;
            } else {
                _y.ring_elements.insert( {rootf.ring_elements.begin()->first, _nd} );
            }
        //                            std::cout<<"_Yaf:";
        //                std::cout<<_y;

        //    _y.logmap();

            _x = HSymbolic({{_y, 1}});
        //    std::cout<<"_X:";
        //    std::cout<<_x;
        //    _x.logmap();
            return _x;
        }
        static HSymbolic multiply(HSymbolic _x, HSymbolic _y, bool open){
            if((_x == HSymbolic("1") || _x==HSymbolic(1))){
                            // std::cout<<"p:"<<_y;
                            // _y.logmap();
                                                                //    std::cout<<"2-------------------------------------------------\n ";

                            return _y;
                        }
                        if((_y == HSymbolic("1") || _y==HSymbolic(1))){
                        // std::cout<<"p:"<<_x;
                            // _x.logmap();
                                                                //    std::cout<<"2-------------------------------------------------\n ";

                            return _x;
                        }
            if(!open){
                //  std::cout<<"\n\nMULTIPLYING {{{  "<<_x<<"  --AND--  "<<_y<<"  }}}:\n\n";
                auto _p = _x;
                auto _q = _y;
                if(_y.ismultiply_ring()){
                    _p = _y;
                    _q = _x;
                } else {
                    _p = _x;
                    _q = _y;
                }
                if(_q.func != NO_FUNC)
                    _q = _q.hug();
        //        std::cout<<"\nP, Q: "<<_p<<"\n"<<_q<<"\n------\n\n";
            //     std::cout<<_p.ismultiply_ring()<<"  "<<_q.ismultiply_ring()<<"  \n";
            //     std::cout<<"[[p:   "<<_p<<"\n q:   "<<_q<<"]]\n\n";
            //     std::cout<<"-----pq";
            //     _p.logmap();
            //     _q.logmap();
            //    std::cout<<"--------\n\n Result// \n";
               if(_p.ismultiply_ring() && !_q.ismultiply_ring()){
                  // std::cout<<_q<<"   _q\n";
                    
                    _p = _p.multiply_pushroot(_q);
                   //                     _p = HSymbolic({{_p, 1}});
                
            //        std::cout<<"p:"<<_p;
            //        _p.logmap();
            //   std::cout<<"1-------------------------------------------------\n ";
                } else if(!_p.ismultiply_ring() && !_q.ismultiply_ring()){
                   // std::cout<<"AHA!";
                        HSymbolic _n = HSymbolic({{_y, (long double)1}, {_x, (long double)1}}, (std::string)"*");
                        if((_x == HSymbolic("1") || _x==HSymbolic(1))){
                            // std::cout<<"p:"<<_y;
                            // _y.logmap();
                                                                //    std::cout<<"2-------------------------------------------------\n ";

                            return _y;
                        }
                        if((_y == HSymbolic("1") || _y==HSymbolic(1))){
                        // std::cout<<"p:"<<_x;
                            // _x.logmap();
                                                                //    std::cout<<"2-------------------------------------------------\n ";

                            return _x;
                        }
                        if(_n.ring_elements.size() == 2)
                        _p =  HSymbolic({{_x, (long double)1}, {_y, (long double)1}}, (std::string)"*").clean();
                        else _p =  HSymbolic({{_x, (long double)2}}, (std::string)"*").clean();
                        //  std::cout<<"p:"<<_p;
                        // _p.logmap();
                        //                std::cout<<"2-------------------------------------------------\n ";

                } else if(_p.ismultiply_ring() && _q.ismultiply_ring()){
                 //   std::cout<<_q.is_normal();
                    HSymbolic _qq = _q.ring_elements.begin()->first;
                 //   _qq.logmap();
                    if(_q.is_normal()) _q = _qq;
                   //     std::cout<<"p: "<<_p<<"\nq:"<<_q<<"\n";
                 //   _q.logmap();

              //   std::cout<<"±±±±±\n";
                     for(auto it = _q.ring_elements.begin(); it != _q.ring_elements.end(); ++it){
                     //  std::cout<<(it->first)<<" it->first _q\n";

                        _p = _p.multiply_pushroot(((HSymbolic)(it->first)).hug(), (int)(it->second));
                    }
                           //             _p = HSymbolic({{_p, 1}});
                //    std::cout<<_p<<"---\n";
                    //  std::cout<<"p:"<<_p;
                    // _p.logmap();
                    //                std::cout<<"3-------------------------------------------------\n ";

                }
                // std::cout<<"\n"<< _p <<"   \n"<<_p.strip()<<" ... |";
                // std::cout<<_p.func<<"|  //  |"<<_p.ring_function()<<"|\n\n";
                if(_p.func != "*")
                    return _p.strip().clean();
                return _p.clean();
            }
            else {
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                std::map<HSymbolic, long double> newmap;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    for(yitr = _y.ring_elements.begin(); yitr != _y.ring_elements.end(); ++yitr){
                        if(newmap.count( HSymbolic::multiply(xitr->first, yitr->first, false) ) != 1)
                        newmap.insert({HSymbolic::multiply(xitr->first, yitr->first, false),  (long double)(xitr->second) * (long double)(yitr->second)});
                        else 
                        newmap.at(HSymbolic::multiply(xitr->first, yitr->first, false)) +=  (long double)(xitr->second) * (long double)(yitr->second);


                    }
                }
                return HSymbolic(newmap).clean();
            }
        }
        
        HSymbolic _inv(){
            HSymbolic _x = (*this);
            if(_x.ismultiply_ring()){
                //dacapo
                auto _xstrip = _x;
                long double _c;
                 _xstrip = _x.strip(_c);
                for(auto it = _xstrip.ring_elements.begin(); it != _xstrip.ring_elements.end(); ++it){
                    _xstrip.ring_elements.at(it->first) = -(it->second);

                }
                return _xstrip.hug() * HSymbolic(1 /_c);
    
            } else {
                if(_x.strip().value != NO_VAL)
                   return _x.hug("*")._inv().strip(); 
                return _x.hug("*").hug()._inv();
            }
            return HSymbolic(0);
        }
        HSymbolic inv(){
            HSymbolic _x = (*this);
            if(_x.strip().value != NO_VAL)
                return _x._inv().hug("*");
            return _x._inv();
        }
        static HSymbolic multiply_divide(HSymbolic _x, HSymbolic _y, bool open){
            
            if((_y == HSymbolic("1") || _y==HSymbolic(1))){
                return _x;
            }
             if(_y == HSymbolic("1") || _y == HSymbolic(1)){
                    return _x;
                }
                if(_x == _y){
                    return HSymbolic("1");
                }
                if(_y.inv() == HSymbolic(0)){
                    return HSymbolic({{_x, (long double)1}, {_y, (long double)1}}, (std::string)"/").clean();
                }
                // _y.inv().strip().strip().strip().logmap();
                // _y.inv().logmap();
            if(_x.ismultiply_ring() && !_y.ismultiply_ring()){
                 return HSymbolic::multiply(_x.inv(), _y, open).clean().inv().clean();
            }
            return HSymbolic::multiply(_x, _y.inv(), open).clean();
            if(!open){
                           //     std::cout<<"\n ___ y;"<<_y<<"   "<<_x<<"\n"; 
              //  _y.logmap();
                 if(_y == HSymbolic("1") || _y == HSymbolic(1)){
                    return _x;
                }
                if(_x == _y){
                    return HSymbolic("1");
                }
                if(_y.inv() == HSymbolic(0)){
                    return HSymbolic({{_x, (long double)1}, {_y, (long double)1}}, (std::string)"/");
                }
                _y = _y.inv();
               // std::cout<<"yinv:";
             //   _y.logmap();
                //  std::cout<<"\n\nMULTIPLYING {{{  "<<_x<<"  --AND--  "<<_y<<"  }}}:\n\n";
                auto _p = _x;
                auto _q = _y;
                if(_y.ismultiply_ring()){
                    _p = _y;
                    _q = _x;
                } else {
                    _p = _x;
                    _q = _y;
                }
            //     std::cout<<_p.ismultiply_ring()<<"  "<<_q.ismultiply_ring()<<"  \n";
            //     std::cout<<"[[p:   "<<_p<<"\n q:   "<<_q<<"]]\n\n";
            //     std::cout<<"-----pq";
            //     _p.logmap();
            //     _q.logmap();
            //    std::cout<<"--------\n\n Result// \n";
               if(_p.ismultiply_ring() && !_q.ismultiply_ring()){
                  // std::cout<<_q<<"   _q\n";

                    _p = _p.multiply_pushroot(_q);
                   //                     _p = HSymbolic({{_p, 1}});
                
            //        std::cout<<"p:"<<_p;
            //        _p.logmap();
            //   std::cout<<"1-------------------------------------------------\n ";
                } else if(!_p.ismultiply_ring() && !_q.ismultiply_ring()){
                   // std::cout<<"AHA!";
                        HSymbolic _n = HSymbolic({{_y, (long double)1}, {_x, (long double)1}}, (std::string)"*");
                        if((_x == HSymbolic("1") || _x==HSymbolic(1))){
                            // std::cout<<"p:"<<_y;
                            // _y.logmap();
                                                                //    std::cout<<"2-------------------------------------------------\n ";

                            return _y;
                        }
                        if((_y == HSymbolic("1") || _y==HSymbolic(1))){
                        // std::cout<<"p:"<<_x;
                            // _x.logmap();
                                                                //    std::cout<<"2-------------------------------------------------\n ";

                            return _x;
                        }
                        if(_n.ring_elements.size() == 2)
                        _p =  HSymbolic({{_x, (long double)1}, {_y, (long double)1}}, (std::string)"*");
                        else _p =  HSymbolic({{_x, (long double)2}}, (std::string)"*").clean();
                        //  std::cout<<"p:"<<_p;
                        // _p.logmap();
                        //                std::cout<<"2-------------------------------------------------\n ";

                } else if(_p.ismultiply_ring() && _q.ismultiply_ring()){
                 //   std::cout<<_q.is_normal();
                    HSymbolic _qq = _q.ring_elements.begin()->first;
                 //   _qq.logmap();
                    if(_q.is_normal()) _q = _qq;
                 //   _q.logmap();
                     for(auto it = _q.ring_elements.begin(); it != _q.ring_elements.end(); ++it){
                       // std::cout<<(it->first)<<" it->first _q\n";
                    
                        _p = _p.multiply_pushroot(it->first, (int)(it->second));
                    }
                           //             _p = HSymbolic({{_p, 1}});

                    //  std::cout<<"p:"<<_p;
                    // _p.logmap();
                    //                std::cout<<"3-------------------------------------------------\n ";

                }
                // std::cout<<"\n"<< _p <<"   \n"<<_p.strip()<<" ... |";
                // std::cout<<_p.func<<"|  //  |"<<_p.ring_function()<<"|\n\n";
                if(_p.func != "*")
                    return _p.strip();
                return _p;
            }
            else {
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                std::map<HSymbolic, long double> newmap;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    for(yitr = _y.ring_elements.begin(); yitr != _y.ring_elements.end(); ++yitr){
                        if(newmap.count( HSymbolic::multiply_divide(xitr->first, yitr->first, false) ) != 1)
                        newmap.insert({HSymbolic::multiply_divide(xitr->first, yitr->first, false),  (long double)(xitr->second) * (long double)(yitr->second)});
                        else 
                        newmap.at(HSymbolic::multiply_divide(xitr->first, yitr->first, false)) +=  (long double)(xitr->second) * (long double)(yitr->second);


                    }
                }
                return HSymbolic(newmap).clean();
            }
        }

        static HSymbolic divide(HSymbolic _x, HSymbolic _y, bool open){
            if(!open){
                std::cout<<"\nx, y:";
                _x.logmap();
                _y.logmap();
                if(_y == HSymbolic("1") || _y == HSymbolic(1)){
                    return _x;
                }
                if(_x == _y){
                    return HSymbolic("1");

                }
                
                return HSymbolic({{_x, (long double)1}, {_y, (long double)1}}, (std::string)"/");
            }
            else {
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                std::map<HSymbolic, long double> newmap;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    newmap.insert({HSymbolic::divide(((HSymbolic)(xitr->first)).hug(), _y, false),  (long double)(xitr->second)});
                    
                }
                return HSymbolic(newmap).clean();
            }
        }
        friend bool operator <(const HSymbolic x, const HSymbolic y){
            using namespace std;
            hash<string> hasher;
            size_t hashx = hasher(HSymbolic::to_string(x));
            size_t hashy = hasher(HSymbolic::to_string(y));

            return (hashx < hashy);
        }
        friend bool operator ==(const HSymbolic x, const HSymbolic y){
            using namespace std;
            hash<string> hasher;
            size_t hashx = hasher(HSymbolic::to_string(x));
            size_t hashy = hasher(HSymbolic::to_string(y));

            return (hashx == hashy);
        }
        
        static std::string to_string(HSymbolic _x){
            if(_x.ring_elements.size() == 0){
                
                return (_x.value);
            } else if(_x.func == "*" || _x.func == "/"){
                std::map<HSymbolic, long double>::iterator xitr, yitr;

                int q = 0;
                std::string s="";
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    if(_x.func == "*"){
                        // if((int)(xitr->second) > 0){
                        //     for(int _r = 0 ; _r < (int)(xitr->second); ++ _r){
                        //         s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first)+"))");
                        //         if(_r == (int)(xitr->second) - 1) break;
                        //         s+=" * ";
                        //     }
                        // } else {
                        //     int xitrsec = -(xitr->second);
                        //     for(int _r = 0 ; _r < (int)(xitrsec); ++ _r){
                        //         s+=((std::string)"(("+std::to_string(xitrsec)+")*("+ HSymbolic::to_string(xitr->first)+")^(-1))");
                        //         if(_r == (int)(xitrsec) - 1) break;
                        //         s+=" * ";
                        //     }
                        // }
                        if( (int)(xitr->second) != 1 ){
                            s+=((std::string)"(("+ HSymbolic::to_string(xitr->first)+")^("+std::to_string(xitr->second)+"))");

                        } else s+=((std::string)"("+ HSymbolic::to_string(xitr->first)+")");

                    
                    if(q != _x.ring_elements.size()){
                                                s+=(_x.func);

                    }
                    }
                    else {
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first)+"))");
                    if(q==1)
                        s+=(_x.func);
                    if(q==2)
                        break;
 
                    }
                    
                }
                if(q==1 && _x.func != "*"){
                    xitr = _x.ring_elements.begin();
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first)+"))");

                }
                return s;
            } else if(_x.func != NO_FUNC){
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                std::string s=(_x.func)+"( ";

                int q = 0;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    
                    s+=( (std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first)+"))");
                    if(q==_x.ring_elements.size())
                        break;
                    s+=" + ";
                }
                s+=")";
                return s;
            } else {
                std::map<HSymbolic, long double>::iterator xitr, yitr;
                                    std::string s="";

                int q = 0;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    s+=((std::string)"(("+std::to_string(xitr->second)+")*("+ HSymbolic::to_string(xitr->first)+"))");
                    if(q==_x.ring_elements.size())
                        break;
                    s+=" + ";
                }
                return s;
            } 
        }
        void llog(){
            std::cout<<(HSymbolic::to_clean_string((*this)))<<"\n\n";

        }
        friend std::ostream& operator <<(std::ostream& os, HSymbolic _x){
            if(_x.ring_elements.size() == 0){
                os<<(_x.value);
                return os;
            } else if(_x.func == "*" || _x.func == "/" || _x.func == "m*"){
                std::map<HSymbolic, long double>::iterator xitr, yitr;

                int q = 0;
                //std::cout<<(_x.ring_elements.size())<<"\n";
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    if(_x.func == "*"){
                        // if((int)(xitr->second) > 0){
                            // for(int _r = 0 ; _r < (int)(xitr->second); ++ _r){
                            //     os<<"(("<<(1)<<")*( v["<<(xitr->first)<<"] ))";
                            //     if(_r == (int)(xitr->second) - 1) break;
                            //     os<<" * ";
                            // }

                        // } else {
                        //     int xitrsec = -(int)(xitr->second);
                        //     for(int _r = 0 ; _r < (int)(xitrsec); ++ _r){
                        //         os<<"(("<<(1)<<")*( v["<<(xitr->first)<<"^(-1)] ))";
                        //         if(_r == (int)(xitrsec) - 1) break;
                        //         os<<" * ";
                        //     }
                        // }
                        if((int)(xitr->second) != 1)
                        os<<"(("<<(1)<<")*(v["<<(xitr->first)<<"])^"<<(int)(xitr->second)<<")";
                        else os<<"(("<<(1)<<")*(v["<<(xitr->first)<<"])"<<")";

                    
                    if(q != _x.ring_elements.size()){
                                                os<<(_x.func);

                    }
                    }
                    else {
                        os<<"(("<<(xitr->second)<<")*(v["<<(xitr->first)<<"]))";
                    if(q==1)
                        os<<(_x.func);
                    if(q==2)
                        break;
                    }
                    
                    
                }
                if(q==1 && _x.func != "*"){
                    xitr = _x.ring_elements.begin();
                    os<<(std::string)"(("<<(xitr->second)<<")*(v["<<(xitr->first)<<"]))";

                }
                return os;
            } else if(_x.func != NO_FUNC){
                std::map<HSymbolic, long double>::iterator xitr, yitr;

                int q = 0;
                os<<(_x.func)<<"(";
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    os<<"(("<<(xitr->second)<<")*(v["<<(xitr->first)<<"]))";
                    if(q==_x.ring_elements.size())
                        break;
                    os<<" + ";
                }
                os<<")";
                return os;
            } else {
                std::map<HSymbolic, long double>::iterator xitr, yitr;

                int q = 0;
                for(xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                    q++;
                    os<<"(("<<(xitr->second)<<")*(v["<<(xitr->first)<<"]))";
                    if(q==_x.ring_elements.size())
                        break;
                    os<<" + ";
                }
                return os;
            } 
        }
        static mve to_mve(HSymbolic x){
            mve ex(HSymbolic::to_string(x));
            return ex;
        }

        static std::string to_clean_string(HSymbolic x){
            mve ex2(mvef::plain(HSymbolic::to_mve(x)));
            mve ex3(mvef::plain(ex2));
            std::string _s = mvef::plain(ex3);
            eraseAllSubStr(_s, "1*", "0123456789");
            return _s;
        }
        friend HSymbolic operator+(HSymbolic x, HSymbolic y){
            return HSymbolic::add(x, y, 1, 1);
        }
        friend HSymbolic operator-(HSymbolic x, HSymbolic y){
            return HSymbolic::add(x, y, 1, -1);
        }
        friend HSymbolic operator*(HSymbolic x, HSymbolic y){
            return HSymbolic::multiply(x, y, M_OPEN);
        }
        friend HSymbolic operator/(HSymbolic x, HSymbolic y){
            return HSymbolic::multiply_divide(x, y, M_OPEN);
        }
};
inline std::vector< std::pair<HSymbolic, HSymbolic> > HSymbolic::RULES = {};
inline HSymbolic sin(HSymbolic x){
    return HSymbolic::applyfunc("sin", x, false);
}
inline HSymbolic cos(HSymbolic x){
    return HSymbolic::applyfunc("cos", x, false);
}
inline HSymbolic sqrt(HSymbolic x){
    return HSymbolic::applyfunc("sqrt", x, false);
}
inline HSymbolic diff(HSymbolic x){

}
inline HSymbolic replacevar(HSymbolic&x, std::pair< std::string, std::string > p){
    std::vector< std::string > vars;
    HSymbolic::to_string(x, vars, p);
    return x;
}
inline HSymbolic replacevar(HSymbolic&x, std::pair< HSymbolic, HSymbolic > p){
    std::vector< std::string > vars;
    std::pair< std::string, std::string > q = { p.first.vars().at(0), p.first.vars().at(1) };
    HSymbolic::to_string(x, vars, q);
    return x;
}
inline HSymbolic SYM_TEMPL_VAR_1 = HSymbolic("_Sym_templ_var_1");
inline HSymbolic simplify(HSymbolic _x){
 
            if(_x.ring_elements.size() == 0 || _x.func != NO_FUNC)
                return _x;
            /** sin^2 + cos^2 */
            auto vars = _x.vars();
            // for(auto i=0; i<vars.size(); ++i){
            //     std::cout<<vars.at(i)<<" ";
            // }
            for(auto i=0; i<vars.size(); ++i){
                std::string vname = vars.at(i);
                if(vname == "1") continue;
                auto x_sym = HSymbolic(vname);

                //M_OPEN = false;

                // std::cout<<x_sym<<" -- "<<i<<"\n"<<HSymbolic::applyfunc("cos", x_sym, false);
                // std::cout<<"\ncos2"<<"   "<<HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym)<<"\n\n";
                // std::cout<<"\ncossin"<<"   "<<HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("cos", x_sym)<<"\n\n";
                // std::cout<<"\nsin2"<<"   "<<HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym)<<"\n\n";
                // std::cout<<"\nx"<<"   "<<x_sym<<"\n\n";
                // std::cout<<"\nx(x+1)"<<"   "<<x_sym*(x_sym + 1)<<"\n\n";

                long double _cos2 = _x.get( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) );
                long double _sin2 = _x.get(HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) );
                //                 std::cout<<"\nHQQQQ\n";

                // std::cout<<"\n\n"<<_cos2<<"  --  "<<( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) )<<"\n\n";
                //     std::cout<<"\n\n"<<_sin2<<"  --  "<<( HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) )<<"\n\n";

                if(_cos2 == _sin2){
                    // this->logmap();
                    // HSymbolic("1").logmap();
                    // (HSymbolic("1")+HSymbolic("1")+HSymbolic(1)).logmap();
                    _x = _x + _cos2;
                    
                    _x.erase( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) );
                    _x.erase( HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) );
                } else {
                    long double m = _cos2;
                    // m(sum) + (_sin2-m)(sin^2)
                    long double n = _sin2 - m;
                    _x = _x + m;
                    _x.erase( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) );
                    _x.set( HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) , n);

                }
                //M_OPEN = true;
            }
            for(int ruleid = 0 ;ruleid < HSymbolic::RULES.size(); ++ruleid){
                auto rulepair = HSymbolic::RULES.at(ruleid);

                for(auto i=0; i<vars.size(); ++i){
                    std::string vname = vars.at(i);
                    if(vname == "1") continue;
                    auto x_sym = HSymbolic(vname);
                    auto rp1 = rulepair.first;
                    auto rp2 = rulepair.second;
                    replacevar(rp1, {SYM_TEMPL_VAR_1, x_sym});
                    replacevar(rp2, {SYM_TEMPL_VAR_1, x_sym});
                    
                    long double _cos2 = _x.get( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) );
                    long double _sin2 = _x.get(HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) );
                    //                 std::cout<<"\nHQQQQ\n";

                    // std::cout<<"\n\n"<<_cos2<<"  --  "<<( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) )<<"\n\n";
                    //     std::cout<<"\n\n"<<_sin2<<"  --  "<<( HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) )<<"\n\n";

                    if(_cos2 == _sin2){
                        // this->logmap();
                        // HSymbolic("1").logmap();
                        // (HSymbolic("1")+HSymbolic("1")+HSymbolic(1)).logmap();
                        _x = _x + _cos2;
                        
                        _x.erase( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) );
                        _x.erase( HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) );
                    } else {
                        long double m = _cos2;
                        // m(sum) + (_sin2-m)(sin^2)
                        long double n = _sin2 - m;
                        _x = _x + m;
                        _x.erase( HSymbolic::applyfunc("cos", x_sym) * HSymbolic::applyfunc("cos", x_sym) );
                        _x.set( HSymbolic::applyfunc("sin", x_sym) * HSymbolic::applyfunc("sin", x_sym) , n);

                    }
                    //M_OPEN = true;
                }
            }

            for(auto xitr = _x.ring_elements.begin(); xitr != _x.ring_elements.end(); ++xitr){
                if( (xitr->second) == 0 ){
                    _x.ring_elements.erase(xitr);
                }
            }
                   // _x.logmap();

            return _x;
        }
#endif