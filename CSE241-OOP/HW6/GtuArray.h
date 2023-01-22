#include "ContainerRepository.h"
#ifndef GtuArray_h
#define GtuArray_h

namespace GTU{

    template<typename T,int size>
    class GtuArray : public ContainerRepository<T>{
        public :
        GtuArray();
        
        GtuIterator<T> rbegin();
        GtuIterator<T> rend();
        T& operator[](int index);
        void fill(T data);
        T & back();
        T & front();


    };



}
#endif
#include "GtuArray.tpp"