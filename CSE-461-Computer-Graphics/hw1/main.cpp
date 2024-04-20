#include "scene.h"
#include "image.h"
#include <iostream>
int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input_xml_file output_image_file" << std::endl;
        return 1; // Return a non-zero value to indicate incorrect usage
    }

    const char *xmlPath = argv[1];
    const char *output = argv[2];

    Scene *pScene = new Scene(xmlPath);
  
    Image *image = new Image(pScene->camera.imagePlane.nx, pScene->camera.imagePlane.ny);
    
    pScene->render(*image, output);

    return 0;
}