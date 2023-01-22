
/* I CAN NOT SUCCES TO SEPERATE IMPLEMENTATION this part but I will LEARN HOW TO DO IT*/


#include <memory>
#include "Node.h"

#ifndef Iterator_h
#define Iterator_h
namespace GTU{

    template<typename T>
    class GtuIterator{
        public :
            /* Default iterator Constructor*/
            GtuIterator<T>(){};
            
            /* Constructor Gets shared_pointer */
            GtuIterator<T>(const std::shared_ptr<Node<T>> other) : iter(other){};
            
            /* Pre Increment Operator for Iterator*/
            GtuIterator<T>& operator++() {
                
                this->iter = iter->next;
                return (*this); //PRE
            }
            /* Post increment operator for Iterator*/
            GtuIterator<T> operator++(int){
                GtuIterator temp;

                temp.iter = this->iter->next;
                return temp;
            }; 
            
            /* Pre decrement operator for iterator*/
            GtuIterator<T>& operator--(){}; //PRE
            /* Post decrement operator for iterator*/
            GtuIterator<T> operator--(int){}; //Post
            
            /* Stucture dereferencing operator*/
            T* operator->(){ return &iter->_data; };
            
            /* The dereferencing operator*/
            T& operator*(){return iter->_data; };

            /* Compare operator between two iterator*/
            bool operator==(const GtuIterator& other){
                bool status =false;
                if(other.iter != nullptr && this->iter != nullptr && this->iter == other.iter) {status = true;}
                return status;
            };

            /* Nullptr Check operator*/
            bool operator == (const std::nullptr_t ptr){
                if(this->iter == nullptr) return true;
                return false;
            }

            /* Compare operator between two iterator*/
            bool operator!=(const GtuIterator& other){
                return !(*this== other);
            };
        
            
        public:
            std::shared_ptr<Node<T>> iter;
    };


}
#endif
