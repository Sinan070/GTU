#ifndef __MESH_H_
#define __MESH_H_



#include "defs.h"
#include "ray.h"
#include <string>
#include "vector"
#include "helper.h"
#include <limits>




using namespace std;
class Scene;


class Mesh{
    private:
    Scene *scene;
    public :
    Mesh(Scene * scene,int id, int matIndex, const vector<Face>& faces);	// Constructor    
    int id ;
    
    int materialIndex;
 
    vector<Face> faces;


    Hit findHit(const Ray & ray) const;
    private:
    Hit invidualHit(const Ray & ray , const Face & face, const int matIndex )  const;
    

};

#endif


    
    







