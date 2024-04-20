#ifndef __SCENE_H_
#define __SCENE_H_


#include "defs.h"
#include "camera.h"
#include "lightSources.h"
#include "material.h"
#include <vector>
#include "image.h"

// Forward declaration

class Mesh;

using namespace std;


class Scene{
    
    
    public :

    Scene(const char *xmlPath);
    int maxraytracedepth; // This is positive integer which defines the maximum recursive ray tracing depth
    Vector3f backgroundColor; //r, g, b values for the pixel in a no-hit case.
    Camera camera; // This defines a camera in the scene.
    vector<LightSource *> lightSources; // vector of light sources
    Vector3f ambientLight; 
    vector<Material *> materials; // materials in scene	
    vector<Vector3f> vertexDatas; // vertexdatas
    vector<Mesh* > objects; // vector of mesh pointers is objects.
    void render(Image & image, const char* name); // render function
};

#endif