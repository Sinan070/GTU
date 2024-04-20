#ifndef __LIGHT_SOURCE_H
#define __LIGHT_SOURCE_H
#include "defs.h"
#include <string>
#include <vector>
#include "ray.h"
#include "mesh.h"
using namespace std;


//add area light for shadow

class LightSource{
    
    //private: 
    public:
    LightSource();
    LightSource(const int id , const Vector3f& intensity );
    int id;
    Vector3f intensity;
    private :
    virtual void virtualF() = 0;
    virtual Vector3f computeLightContribution(const Vector3f& p) const = 0;

  
};

class DirectionalLightSource : public LightSource{
    public:
    DirectionalLightSource(const int id  , const Vector3f& intensity, const Vector3f& direction );
    Vector3f direction;
    Vector3f getDirection() const ;
    private:
    void virtualF();
    virtual void virtualF2() = 0;

};



class PointLightSource : public LightSource{
    public:
    PointLightSource();
    PointLightSource(const int id , const Vector3f& intensity, const Vector3f &position);
    Vector3f position;
    Vector3f getDirection(const Vector3f &p) const ;
    private:
    void virtualF();
    public:
    Vector3f computeLightContribution(const Vector3f& p) const;

};


class AreaLightSource : public LightSource{
    public:
    AreaLightSource(const int id  , const Vector3f& intensity);
    
    Vector3f direction;
    virtual Vector3f getDirection() const = 0 ;
    
    virtual std::pair<bool, Vector3f> intersectionTest(const Ray & ray) const = 0;
    virtual Vector3f computeLightContribution(const Vector3f& p) const = 0;

    private : 
    void virtualF(){};
    virtual void virtualFArea() = 0;

};



class TriangularLightSource: public AreaLightSource{
    public:
    TriangularLightSource();
    TriangularLightSource(const int id , const Vector3f& intensity, const Vector3f & v1, const  Vector3f & v2 , const Vector3f & v3);
    
    Vector3f v1, v2, v3;
    
    
   // Vector3f computeLightContribution();
    std::pair<bool, Vector3f> intersectionTest(const Ray & ray) const;
    Vector3f getDirection() const{
        return direction;
    }
    Vector3f computeLightContribution(const Vector3f& p) const;

    private:
    Vector3f calculate_direction() const;
    void virtualF2(){};
    void virtualFArea(){};
    
};





#endif
