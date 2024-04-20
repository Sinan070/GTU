#ifndef __RAY_H_
#define __RAY_H_


#include "defs.h"



typedef struct  Ray{
    
    Vector3f origin;
    Vector3f direction;

    bool isShadow = false;


}Ray;

#endif