#ifndef Node_h
#define Node_h
#include <memory>

/* Linled list Node that stores the data using shared pointer*/
namespace GTU{
    
    template<typename T>
    class Node{
        
        public :
            Node() {}            
            Node(T& data) : next(nullptr), _data(data){
            
            }

            std::shared_ptr<Node<T>> next;
            T _data;
           
           
            
    };

}

#endif
