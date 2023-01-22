
/* GLOBAL FUNCTIONS*/




#include <bits/stdc++.h>
#include "GtuIterator.h"

#ifndef Global_H
#define Global_H
namespace GTU{

    /* std::find function prototype , but compatible with Gtu Containers*/
    template<typename InputIterator,typename InputValue>
        InputIterator find(InputIterator begin, InputIterator end, const InputValue& value)
        {
            while(!(begin == end)){

                if(value == *begin){
                    return begin;
                }
            ++begin; 
            }
                
            return end;
        }

        /* std::for_each function prototype , but compatible with Gtu Containers*/
        template<class InputIterator, class Function>
            void for_each(InputIterator first, InputIterator last, Function fn)
            {
            while (!(first==last)) {
                fn (first);
                ++first;
            }
            fn (first);
                  
            }
}

#endif
