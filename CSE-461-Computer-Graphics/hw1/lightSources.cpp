#include "lightSources.h"
#include "helper.h"
#include "rayTracing.h"
#include "defs.h"

LightSource::LightSource(){

}
LightSource::LightSource(const int id , const Vector3f& intensity ){
    this->id = id;
    this->intensity = intensity;

}

PointLightSource::PointLightSource(){

}
PointLightSource::PointLightSource(const int id , const Vector3f& intensity, const Vector3f &position) 
                                    : LightSource(id, intensity) , position(position)
{

}

DirectionalLightSource::DirectionalLightSource(const int id  , const Vector3f& intensity, const Vector3f& direction) 
: LightSource(id, intensity), direction(direction)
{

}

void DirectionalLightSource::virtualF(){

}
void DirectionalLightSource::virtualF2(){}

Vector3f DirectionalLightSource::getDirection() const {
   return (this->direction);
}



Vector3f PointLightSource::getDirection(const Vector3f& p) const{
    return   (position- p);
}

void PointLightSource::virtualF(){

}
Vector3f PointLightSource::computeLightContribution(const Vector3f& p) const{

	/*
	 * Irradiance on a point due to a light source is computed here
	 * using inverse square law formula
	 *
	 * E(d) = I / d^2
	 */

	Vector3f lightDirection = this->position - p;
    float lightDistance = vectorLength(lightDirection);
    Vector3f irradianceContribution = this->intensity / (lightDistance * lightDistance);
    return irradianceContribution;
}



/*float PointLightSource::calculateCosPhi(const Vector3f & cameraPosition, const Vector3f& surfaceNormal) const {
    

    //w = normalize position of light source - surface normal 
    Vector3f w = normalize(this->position - surfaceNormal);

    //v = normalize camera position - surface normal

    Vector3f v = normalize(cameraPosition - surfaceNormal);


    //2*(w.n).n -w
    Vector3f r = (surfaceNormal*(dotProduct(w,surfaceNormal)))*2.0 -w;

    //cos phi = (v.r)
    

    return std::max((float)0.0,dotProduct(v,r));

}
float PointLightSource::calculateCosTetha(const Vector3f& surfaceNormal) const{
    Vector3f w = normalize(this->position - surfaceNormal);
    return std::max((float) 0, dotProduct(w, surfaceNormal));
}

TriangularLightSource::TriangularLightSource(){

}


float TriangularLightSource::calculateCosPhi(const Vector3f & cameraPosition, const Vector3f& surfaceNormal) const{

}
float TriangularLightSource::calculateCosTetha( const Vector3f& surfaceNormal) const {

}*/


AreaLightSource::AreaLightSource(const int id  , const Vector3f& intensity) : LightSource(id,intensity){
    this->direction = direction;
}




TriangularLightSource::TriangularLightSource(const int id , const Vector3f& intensity , const  Vector3f &v1, const  Vector3f &v2 ,const  Vector3f &v3)
                                            :v1(v1), v2(v2), v3(v3), AreaLightSource(id, intensity)
                                            {

    this->direction = calculate_direction();


}

//The direction of the light follows the cross product (vertex1-vertex2) x (vertex1-vertex3)
Vector3f TriangularLightSource::calculate_direction() const{
    //std::cerr << v1.x << v1.y << v1.z << std::endl;
    //std::cerr <<"tset" << this->v2.x << v2.y << v2.z << std::endl;

    return crossProduct((v1 - v2), v1- v3);

}

std::pair<bool, Vector3f> TriangularLightSource::intersectionTest(const Ray& ray) const {
    const Vector3f p1 = this->v1;
    const Vector3f p2 = this->v2;
    const Vector3f p3 = this->v3;

    
    //std::cerr << ray.origin.x << ray.origin.y << ray.origin.z << std::endl;


    float det = determinant(
            p1.x - p2.x, p1.x - p3.x, ray.direction.x,
            p1.y - p2.y, p1.y - p3.y, ray.direction.y,
            p1.z - p2.z, p1.z - p3.z, ray.direction.z);

    float eps = pow(10,-6);
    if( det < 0 || ( det < eps && det > -eps)) {
        // No intersection
        return {false, Vector3f{INF, INF ,INF}};
    }

    float beta = determinant(
            p1.x - ray.origin.x, p1.x - p3.x, ray.direction.x,
            p1.y - ray.origin.y, p1.y - p3.y, ray.direction.y,
            p1.z - ray.origin.z, p1.z - p3.z, ray.direction.z)
                 / det;
    float gamma = determinant(
            p1.x - p2.x, p1.x - ray.origin.x, ray.direction.x,
            p1.y - p2.y, p1.y - ray.origin.y, ray.direction.y,
            p1.z - p2.z, p1.z - ray.origin.z, ray.direction.z)
                 / det;
    float t = determinant(
            p1.x - p2.x, p1.x - p3.x, p1.x - ray.origin.x,
            p1.y - p2.y, p1.y - p3.y, p1.y - ray.origin.y,
            p1.z - p2.z, p1.z - p3.z, p1.z - ray.origin.z)
              / det;

    if (t > eps && (beta + gamma <= 1) && (0 <= beta) && (0 <= gamma)) {
        // Intersection found, compute the intersection point
        Vector3f intersectionPoint = (ray.direction+ray.direction)*t;
        return {true, intersectionPoint};
    } else {
        
            
        
        // No intersection
        return {false, Vector3f{INF , INF , INF}};
    }
}

Vector3f TriangularLightSource::computeLightContribution(const Vector3f& p) const{
    Vector3f totalIrradianceContribution = {0.0f, 0.0f, 0.0f};
//perror("gecti");
// Iterate over each vertex of the triangle
for (int i = 0; i < 3; ++i) {
    // Access each vertex individually
    const Vector3f& vertex = (i == 0) ? v1 : ((i == 1) ? v2 : v3);

    // Compute the direction from the vertex to the point
    Vector3f lightDirection = vertex - p;
    float lightDistanceSquared = dotProduct(lightDirection, lightDirection);

    // Compute the irradiance contribution using inverse square law
    Vector3f irradianceContribution = intensity / lightDistanceSquared;

    // Add the contribution to the total
    totalIrradianceContribution += irradianceContribution;
}

return totalIrradianceContribution;



}






