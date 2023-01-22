#include "Iterable.h"
#include "GtuIterator.h"
#include <memory>
#include <iostream>

#ifndef Container_h
#define Container_h

namespace GTU{
    template<typename T>
    class ContainerRepository: public Iterable<T>{
        public:
            
            ContainerRepository<T>(); 
            

            ContainerRepository<T>(const ContainerRepository<T>& other); 

            ContainerRepository<T>(ContainerRepository&& other);
            
            ContainerRepository<T>& operator=(const ContainerRepository<T>& other);
            
            ContainerRepository<T>& operator=(ContainerRepository<T>&& other);
                
            
            bool empty() const;
            
            int size() const;
            
            void erase(const GtuIterator<T>& a);
            
            void clear();
                
    
            GtuIterator<T> begin();
            GtuIterator<T> end();
            
            const GtuIterator<T> cbegin();
            const GtuIterator<T> cend();
        
            std::shared_ptr<Node<T>> createNode(T  value=0);
            void print();
                
            
            ~ContainerRepository<T>();
        protected:
            int Size;
            int maxSize;
            std::shared_ptr<Node<T>> root;
            std::shared_ptr<Node<T>> iter;
            

            void setSize(int maxSize);
    };


}
#include "ContainerRepository.tpp"
#endif
