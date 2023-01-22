#include "ContainerRepository.h"
#include <iostream>
#ifndef GtuVector_h
#define GtuVector_h
namespace GTU{

    template<typename T>
    class GtuVector :  public  ContainerRepository<T>{
        public:
            GtuVector<T>(int size =0);
            T& operator[](int index);

           
           
            void insert(const GtuIterator<T> & _iter,const T& value);
            void push_back(const T& value);
                        void pop_back();
                
            
            
            private:
            void add(T value);
    };
}
#endif
#include "GtuVector.tpp"