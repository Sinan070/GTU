#include "rayTracing.h"
#include <iostream>
#include <utility>


Vector3f reflect(const Vector3f &direction, const Vector3f & normal);

RayTracing::RayTracing(){
    
}






Ray RayTracing::findPrimaryRay(const Camera& camera , const int row , const int col) const{

	/* m = e + (-w) * distance */
    /* q = m + l * u + t * v */
    /* s = q + s_u * u - s_v * v */
    /* d = s - e */    

    float left = camera.imagePlane.left;
    float right = camera.imagePlane.right;
    float top = camera.imagePlane.top;
    float bottom = camera.imagePlane.bottom;
   // std::cerr << "ImagePlane"<<left << right << top << bottom << std::endl;     

    Vector3f m = (camera.gaze*camera.imagePlane.nearDistance) + camera.position;
    Vector3f u = crossProduct(camera.gaze ,camera.up);
    normalize(u);
    Vector3f q = m + (u*left) + (camera.up*top);

    float su = (right-left)*(col+0.5)/camera.imagePlane.nx;
    float sv = (top-bottom)*(row+0.5)/camera.imagePlane.ny;

    Vector3f s = q + (u*su) - (camera.up*sv);

    //std::cerr <<"Origin " << camera.position.x <<  camera.position.y << camera.position.z << std::endl;
    // std::cerr<<"su " << su << "sv " << sv<<"row " <<row <<"col " << col <<std::endl;
    

    //std::cerr << q.x << q.y << q.z << std::endl;
    Ray ray;
    ray.origin = camera.position;
    ray.direction = normalize( s - camera.position);
    

    ray.isShadow = false;
    return  ray;


}


Vector3f RayTracing::calculateDiffuseShading(const Vector3f & wi, const Vector3f& surfaceNormal ,const Material & material, Vector3f & intensity )const{
    


    float cos_teta = dotProduct(surfaceNormal,wi);
    if(cos_teta < 0) cos_teta = 0;
   
    Vector3f diffuse;
    diffuse.r = material.diffuse.r * (intensity.r*cos_teta);
    diffuse.g = material.diffuse.g * (intensity.g*cos_teta);
    diffuse.b = material.diffuse.b * (intensity.b*cos_teta);
    
    return diffuse;

}

Vector3f RayTracing::calculateAmbient(const Material& material, const Vector3f& ambientLight ) const{
    return {material.ambient.r * ambientLight.r,
            material.ambient.g * ambientLight.g,
            material.ambient.b * ambientLight.b};
}

 Hit RayTracing::intersect(const Ray & ray , const vector<Mesh *> & objects) const{

     /* Calculate the nearest intersection point calling Shape's intersect with given ray */

    Hit minIntersection = {INF, {}, -1};
    // For each object in the scene Intersect ray with all the shapes in scene and get the nearest one
    for (auto object : objects) {
        Hit tempIntersection = object->findHit(ray); // calling object's own intersect method
        if (tempIntersection.t != INF) {
            if (minIntersection.t > tempIntersection.t) {
                minIntersection = tempIntersection;
            }
          
        }
    }
    
    return minIntersection;
 }

Vector3f RayTracing::calculateRadiance(const Ray & ray, const vector <Mesh*> & objects, const vector<LightSource *> &lightSources, const Vector3f & ambientLight,
                 const Hit & hit ,const  vector <Material*>& materials  , const int maxRayTraceDepth,float shadowRayEps) const{

    Vector3f color ;
    Material &material = *materials[hit.materialID-1];
    // calcualte ambient
    color = calculateAmbient(material, ambientLight);

    Vector3f intersectionPoint = ((ray.direction * hit.t) + ray.origin);
    Vector3f irradiance;
    Vector3f wo = normalize( ray.origin - intersectionPoint );
    
    for(int i = 0 ; i < lightSources.size(); ++i){
        //compute shadow
        
        const DirectionalLightSource* dirLight = dynamic_cast<const DirectionalLightSource*>(lightSources[i]);
        const PointLightSource* pointLight = dynamic_cast<const PointLightSource*>(lightSources[i]);
        const AreaLightSource* areaLight = dynamic_cast<const AreaLightSource*>(lightSources[i]);


        Vector3f lightDirection; 
        if (dirLight) {
            
            lightDirection = dirLight->getDirection();
        } else if (pointLight) {
            lightDirection = pointLight->getDirection(intersectionPoint);
        }
        else if(areaLight){
            
            lightDirection = areaLight->getDirection();
            
        }
        
        //get normalized light direction
        Vector3f normalizedLightDirection = normalize(lightDirection);

    
       //Apply shadow offset
        Ray shadowRay;
        Vector3f shadowSurfaceOffset =  normalizedLightDirection* shadowRayEps; 
        shadowRay.direction = normalizedLightDirection;
        shadowRay.origin = intersectionPoint + shadowSurfaceOffset ;

        if(shadowRay.direction.x == -0.0){
shadowRay.direction.x = 0.0;
        }
        if(shadowRay.direction.y == -0.0){
shadowRay.direction.y = 0.0;
        }
        if(shadowRay.direction.z == -0.0){
shadowRay.direction.z = 0.0;
        }
        shadowRay.isShadow = true;


        
        // there is no intersect
        //for area lights also calculate intersection between area light and shadow ray
        if (isShadowReachToLight(shadowRay, lightSources[i], objects )){
            //calculate diffuse
            //calculate specular
            //calculate mirror 
            
            if(pointLight){
               
                irradiance = pointLight->computeLightContribution(intersectionPoint);
                
            }
            else if(areaLight){
                
                irradiance = areaLight->computeLightContribution(intersectionPoint);
                
            }
            Vector3f diffuseIllimunation = this->calculateDiffuseShading(normalizedLightDirection, hit.normal, 
                                material, irradiance);
            
            color += diffuseIllimunation;

            //specular
            
            Vector3f normalizedHalfVector = normalize(normalizedLightDirection + wo );

            color+= calculateSpecularShading(hit.normal,normalizedHalfVector,irradiance, material);
            
            //std::cerr << diffuseIllimunation.r <<" "<< diffuseIllimunation.g<<" "<< diffuseIllimunation.b << " " << hit.materialID<<std::endl;
            //Vector3f specularIllimunation = this->calculateDiffuseShading()


            // compute mirror effect

           if (material.hasMirror()) {
                // Calculate reflected direction
                Vector3f reflectedDirection = (reflect(wo, hit.normal));

                // Trace reflected ray recursively
                Ray reflectedRay;
                reflectedRay.origin = intersectionPoint + (reflectedDirection * shadowRayEps);
                reflectedRay.direction = reflectedDirection;
                Hit reflectedHit = intersect(reflectedRay, objects);

                // Compute radiance recursively
                if (reflectedHit.t != INF && maxRayTraceDepth > 0) {
                    Vector3f reflectedRadiance = calculateRadiance(reflectedRay, objects, lightSources, ambientLight, reflectedHit, materials, maxRayTraceDepth - 1, shadowRayEps);
                    
                    Vector3f reflectedColor;
                    
                    reflectedColor.r = reflectedRadiance.r * material.mirrorReflectance.r;
                    reflectedColor.g = reflectedRadiance.g * material.mirrorReflectance.g;
                    reflectedColor.b = reflectedRadiance.b * material.mirrorReflectance.b;
                    color += reflectedColor;
                }
            }

        }
        else continue;


    }
    color.r = min(max(0.0f, color.r), 255.0f);
    color.g = min(max(0.0f, color.g), 255.0f);
    color.b = min(max(0.0f, color.b), 255.0f);
  

    return color;



}


Vector3f reflect(const Vector3f &direction, const Vector3f & normal){
        return ((direction * -1 ))+ (normal *2.0f * dotProduct(direction, normal)) ;

}

Vector3f RayTracing::calculateSpecularShading(const Vector3f & normal, const Vector3f& halfway , const Vector3f & irradiance , const Material & material) const{

    Vector3f specularIllimunation;
    float cosphi = dotProduct(normal, halfway);
    if(cosphi <0) cosphi = 0;


    specularIllimunation = material.specular*  pow(cosphi, material.phongExponent);
    specularIllimunation.r *= irradiance.r;
    specularIllimunation.g *= irradiance.g;
    specularIllimunation.b *= irradiance.b;



    return specularIllimunation;

}


bool RayTracing::isShadowReachToLight(const Ray & shadowRay , const LightSource * lightSource , const vector<Mesh*>objects ) const{
     
        const DirectionalLightSource* dirLight = dynamic_cast<const DirectionalLightSource*>(lightSource);
        const PointLightSource* pointLight = dynamic_cast<const PointLightSource*>(lightSource);
        const AreaLightSource* areaLight = dynamic_cast<const AreaLightSource*>(lightSource);

        Hit shadowHit = this->intersect(shadowRay,objects);

        bool retVal = false;

        
        if(pointLight){
            //perror("gecti");

            if (shadowHit.t >= vectorLength(pointLight->getDirection(shadowRay.origin))){
                
                retVal = true;            
            }
            
        }
        else if(areaLight){
      
            //perror("gecti");
            std::pair<bool, Vector3f> intersection = areaLight->intersectionTest(shadowRay);

            if(intersection.first) {
                //perror("gecti");
                if(shadowHit.t >= vectorLength(intersection.second - shadowRay.origin)){
                    retVal = true;
                }
                
                
            }
        }


    return retVal;
}




