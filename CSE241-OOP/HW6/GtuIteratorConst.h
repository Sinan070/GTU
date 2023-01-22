#include <memory>
#include "Node.h"

#ifndef Iterator_h
#define Iterator_h
namespace GTU{

    template<typename T>
    class GtuIteratorConst{
        public :
             /* Default iterator Constructor*/
            GtuIteratorConst<T>(){};

            /* Constructor Gets shared_pointer */
            GtuIteratorConst<T>(const std::shared_ptr<Node<T>> other) : iter(other){};
            
            /* Stucture dereferencing operator*/
            T* operator->(){ return const &iter->_data; };
            
            /* The dereferencing operator*/
            T& operator*(){return const iter->_data; };
            
             /* Compare operator between two iterator*/
            bool operator==(const GtuIteratorConst& other){
                bool status =false;
                if(other.iter != nullptr && this->iter != nullptr && this->iter == other.iter) {status = true;}
                return status;
            };
             /* Compare operator between two iterator*/
            bool operator!=(const GtuIteratorConst& other){
                return !(*this== other);
            };
        
            
        public:
            const std::shared_ptr<Node<T>> iter;
    };



}
#endif