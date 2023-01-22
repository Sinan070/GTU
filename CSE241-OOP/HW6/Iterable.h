
/* PURE VIRTUAL FUNCTION IMPLEMENTED IN CONTAINER REPOSITORY CLASS*/

#include "GtuIterator.h"
#ifndef Iterable_h
#define Iterable_h
namespace GTU{
    template <typename T>
    class Iterable{

        virtual bool empty() const=0;
        virtual int size() const =0 ;
        virtual void erase(const GtuIterator<T>&) =0;
        virtual void clear() =0;
        virtual   GtuIterator<T> begin() = 0;
        virtual  GtuIterator<T> end() =0;
        virtual const GtuIterator<T> cbegin() = 0;
        virtual const GtuIterator<T> cend() =0;

    };





}
#endif