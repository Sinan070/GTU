
#ifndef __DEFS_H_
#define __DEFS_H_

#include <iostream>




typedef struct Vector3f{

	union 
	{
		float x;
		float r;
	};
	union
	{
		float y;
		float g;
	};
	union
	{
		float z;
		float b;
	};

    

    inline Vector3f operator+(const Vector3f &vector ) const{
        return {this->x + vector.x, this->y+vector.y, this->z+vector.z};

    }
    inline Vector3f operator-(const Vector3f a) const {
		return {x-a.x, y-a.y, z-a.z};
    }
    inline Vector3f & operator/=(float a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
    }

    inline Vector3f operator*(const float a) const {
		return {x*a, y*a, z*a};
    }

    inline Vector3f& operator+=(Vector3f a) {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }
	inline Vector3f operator/(float a) const {
		return {x/a, y/a, z/a};
    }
	inline Vector3f & operator*=(float a) {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }
	// Overload the output stream operator
	
	//friend std::ostream& operator<<(std::ostream& os, const Vector3f& v);

}Vector3f;




typedef struct hit{
    float t;
    Vector3f normal;
    int materialID;


}Hit;

typedef struct Triangle{
    int vertes1Index;
    int vertes2Index;
    int vertes3Index;
}Face;



#endif