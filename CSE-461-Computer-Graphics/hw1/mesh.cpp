#include "mesh.h"
#include "scene.h"

const float INF = numeric_limits<float>::max();

#define nullIntersect {INF,{},-1}

Mesh::Mesh(Scene * scene,int id, int matIndex, const vector<Face>& faces) 
: scene(scene) , id(id), materialIndex(matIndex), faces(faces){
    
}






Hit Mesh::invidualHit(const Ray & ray , const Face & face, const int matIndex) const{
    const Vector3f p1 = this->scene->vertexDatas[face.vertes1Index -1];
    const Vector3f p2 = this->scene->vertexDatas[face.vertes2Index -1];
    const Vector3f p3 = this->scene->vertexDatas[face.vertes3Index -1];



    float det = determinant(
            p1.x - p2.x, p1.x - p3.x, ray.direction.x,
            p1.y - p2.y, p1.y - p3.y, ray.direction.y,
            p1.z - p2.z, p1.z - p3.z, ray.direction.z);

    float eps = pow(10,-6);
    if(det < eps && det > -eps){
        return nullIntersect;
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

    if (t>eps && ( beta + gamma <= 1) && (0 <= beta) && (0 <= gamma)){
        
        return {t, normalize(crossProduct(p3-p2, p1-p2)), matIndex};
    }
    else{
        return nullIntersect;
    }
    
}
Hit Mesh::findHit(const Ray & ray) const{

    int size = this->faces.size();
    Hit tempMin = nullIntersect;

    for(int i=0; i < size; i++)
    {
        Hit inters = invidualHit(ray, faces[i], this->materialIndex);
        if(inters.t != INF && inters.t < tempMin.t)
        {
            tempMin = inters;
        }
    }
    
    return tempMin;

}





