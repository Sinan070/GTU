#ifndef __MATERIAL_H_
#define __MATERIAL_H_
#include <string>
#include "defs.h"

using namespace std;
typedef struct Material{
    /*
<material id="someid">
<ambient>x y z</ambinet>
<diffuse>x y z</diffuse>
<specular>x y z</specular>
<phongexponent>e</phongexponent>
<mirrorreflactance>x y z</mirrorreflanctance>
</material>*/
    int id ;
    Vector3f ambient;
    Vector3f diffuse; 
    Vector3f specular;
    int phongExponent;
    Vector3f mirrorReflectance;
    inline bool hasMirror() const{
        if(mirrorReflectance.x != 0 || mirrorReflectance.y !=0 ||  mirrorReflectance.z !=0){
            return true;
        }
        return false;
    };


}Material;
#endif