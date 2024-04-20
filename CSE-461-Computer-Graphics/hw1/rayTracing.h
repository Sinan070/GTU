#ifndef __RAY_TRACING_H
#define __RAY_TRACING_H


#include "defs.h"
#include "lightSources.h" //kalkacak
#include "ray.h"
#include "camera.h" //kalkacak
#include "scene.h"
#include <limits>
#include "mesh.h"
#include "helper.h"
const float INF = numeric_limits<float>::max();


class RayTracing {

    public : 
   
    RayTracing();
    Ray findPrimaryRay(const Camera& camera , const int i , const int j) const;



    Vector3f calculateDiffuseShading(const Vector3f& wi, const Vector3f& surfaceNormal, const Material & material , Vector3f & intensity) const;

    Hit intersect(const Ray & ray , const vector<Mesh *> & mesh) const;
    
    Vector3f calculateRadiance(const Ray & ray,  const vector <Mesh*> & objects,const vector<LightSource *> &lightSources,const Vector3f & ambientLight, const Hit & hit ,const  vector <Material*>& materials ,int maxRayTraceDepth,float shadowRayEps = 0.00001) const;
    
    Vector3f calculateAmbient(const Material& material, const Vector3f& ambientLight )const;

    bool isShadowReachToLight(const Ray & ray , const LightSource * lightSource , const vector<Mesh*>objects ) const;
    Vector3f calculateSpecularShading(const Vector3f & wo, const Vector3f& halfway , const Vector3f & irradiance , const Material & material) const;
    
};  

#endif