#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "defs.h"


// Structure for holding variables related to the image plane
typedef struct ImagePlane
{

/*

– nearplane: left, right, bottom, top values of the image plane.
– neardistance: distance between the image plane and the camera. gaze vector is perpendicular to the
image plane.
– imageresolution: nx and ny dimensions of the image.
*/

	float left;     
	float right;     
	float bottom;   
	float top;    
    float nearDistance; 
    int nx;         
    int ny;         
} ImagePlane;



typedef struct Camera{
    /*
<position>x y z</position>
<gaze>x y z</gaze>
<up>x y z</up>
<nearplane>left right bottom top</nearplane>
<neardistance> distance </neardistance>
<imageresolution>nx ny</imageresolution>
*/

Vector3f position;
Vector3f gaze;
Vector3f up;
ImagePlane imagePlane;


}Camera;

#endif