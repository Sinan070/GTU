#include "ContainerRepository.h"
#ifndef GtuSet_H
#define GtuSet_H

namespace GTU{

    template<typename T>
    class GtuSet : public  ContainerRepository<T>{
        
        public :
        GtuSet();
        
        void add(T value);
            
            public :
            void insert(T value);

            GtuSet<T> intersectSet(const GtuSet<T> & other);
            GtuSet<T> unionSet(const GtuSet<T> & other);

        private :
            bool checkEntity(T &value);
           

    };




}
#endif
#include "GtuSet.tpp"