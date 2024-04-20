


#include "scene.h"
#include "tinyxml2.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "mesh.h"
#include "rayTracing.h"
#include "image.h"
#include <chrono>
#include <thread>
#include <atomic>
using namespace tinyxml2;
#define nullIntersect {INF,{},-1}

Scene::Scene(const char *xmlPath){

    const char *str;
    XMLDocument xmlDoc;
    XMLError eResult;
    XMLElement *pElement;
    Vector3f tmpPoint;
    string line;
   
    maxraytracedepth = 0;
    

    eResult = xmlDoc.LoadFile(xmlPath);

    XMLNode *pRoot = xmlDoc.FirstChild();
    
    if(pRoot == nullptr){

        perror("null ROot");
    }
    pElement = pRoot->FirstChildElement("maxraytracedepth");

    
    if(pElement != nullptr){
        
        pElement->QueryIntText(&maxraytracedepth);
    }
    

    pElement = pRoot->FirstChildElement("backgroundColor");
    
    str = pElement->GetText();
    std::sscanf(str, "%f %f %f", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);
    
    /*pElement = pRoot->FirstChildElement("ShadowRayEpsilon");
    if(pElement != nullptr)
        pElement->QueryFloatText(&shadowRayEps);

    pElement = pRoot->FirstChildElement("IntersectionTestEpsilon");
    if(pElement != nullptr)
        eResult = pElement->QueryFloatText(&intTestEps);
    */
    // Parse cameras
    pElement = pRoot->FirstChildElement("camera");
    
    if(pElement != nullptr){

        Vector3f position, gaze, up;
        ImagePlane imgPlane;
        XMLElement *camElement;

        camElement = pElement->FirstChildElement("position");
        str = camElement->GetText();
        std::sscanf(str, "%f %f %f", &position.x, &position.y, &position.z);
        camElement = pElement->FirstChildElement("gaze");
        str = camElement->GetText();
        std::sscanf(str, "%f %f %f", &gaze.x, &gaze.y, &gaze.z);
        camElement = pElement->FirstChildElement("up");
        str = camElement->GetText();
        std::sscanf(str, "%f %f %f", &up.x, &up.y, &up.z);
        camElement = pElement->FirstChildElement("nearPlane");
        str = camElement->GetText();
        std::sscanf(str, "%f %f %f %f", &imgPlane.left, &imgPlane.right, &imgPlane.bottom, &imgPlane.top);
        camElement = pElement->FirstChildElement("neardistance");
        eResult = camElement->QueryFloatText(&imgPlane.nearDistance);
        camElement = pElement->FirstChildElement("imageresolution");
        str = camElement->GetText();
        std::sscanf(str, "%d %d", &imgPlane.nx, &imgPlane.ny);
        this->camera = {position, gaze , up , imgPlane};
    }
    
    // Parse materals
    pElement = pRoot->FirstChildElement("materials");
    XMLElement *pMaterial = pElement->FirstChildElement("material");
    XMLElement *materialElement;
    while(pMaterial != nullptr)
    {
        materials.push_back(new Material());

        int curr = materials.size() - 1;

        eResult = pMaterial->QueryIntAttribute("id", &materials[curr]->id);
        materialElement = pMaterial->FirstChildElement("ambient");
        str = materialElement->GetText();
        std::sscanf(str, "%f %f %f", &materials[curr]->ambient.r, &materials[curr]->ambient.g, &materials[curr]->ambient.b);
        materialElement = pMaterial->FirstChildElement("diffuse");
        str = materialElement->GetText();
        std::sscanf(str, "%f %f %f", &materials[curr]->diffuse.r, &materials[curr]->diffuse.g, &materials[curr]->diffuse.b);
        materialElement = pMaterial->FirstChildElement("specular");
        str = materialElement->GetText();
        std::sscanf(str, "%f %f %f", &materials[curr]->specular.r, &materials[curr]->specular.g, &materials[curr]->specular.b);
        materialElement = pMaterial->FirstChildElement("mirrorreflactance");
        if(materialElement != nullptr)
        {
            str = materialElement->GetText();
            std::sscanf(str, "%f %f %f", &materials[curr]->mirrorReflectance.r, &materials[curr]->mirrorReflectance.g, &materials[curr]->mirrorReflectance.b);
        }
        else
        {
            materials[curr]->mirrorReflectance.r = 0.0;
            materials[curr]->mirrorReflectance.g = 0.0;
            materials[curr]->mirrorReflectance.b = 0.0;
        }
        materialElement = pMaterial->FirstChildElement("phongexponent");
        if(materialElement != nullptr)
            materialElement->QueryIntText(&materials[curr]->phongExponent);

        pMaterial = pMaterial->NextSiblingElement("material");
    }

    // Parse vertex data
    pElement = pRoot->FirstChildElement("vertexdata");
    
    stringstream ss(pElement->GetText());
    
    // Parse each line
    while (getline(ss, line)) {
       
        std::istringstream lineStream(line);

        // Parse x, y, and z coordinates
        if(!line.empty()){

            lineStream >> tmpPoint.x >> tmpPoint.y >> tmpPoint.z;
            this->vertexDatas.push_back(tmpPoint);
        }
        
    }


    // Parse objects
    pElement = pRoot->FirstChildElement("objects");


    // Parse meshes
    XMLElement* pObject = pElement->FirstChildElement("mesh");
    XMLElement* objElement;
    while(pObject != nullptr)
    {
        int id;
        int matIndex;
        int p1Index;
        int p2Index;
        int p3Index;
        int cursor = 0;
        vector<Face> faces;

        eResult = pObject->QueryIntAttribute("id", &id);
        objElement = pObject->FirstChildElement("material");
        eResult = objElement->QueryIntText(&matIndex);
        objElement = pObject->FirstChildElement("faces");

        str = objElement->GetText();
        
        ss.clear( );

        ss.str(str);
        
        // Parse each line
        while (getline(ss, line)) {
           
            std::istringstream lineStream(line);

            
        // Parse x, y, and z coordinates
            if(!line.empty()){
                lineStream >> p1Index >> p2Index >> p3Index;
                faces.push_back(*(new Face{p1Index, p2Index, p3Index}));
                
            }
            
        // Add the point to the vector
        }
        
        objects.push_back(new Mesh(this, id, matIndex, faces));
        
        

        pObject = pObject->NextSiblingElement("mesh");
    }
    

    // Parse lights
    int id;
    Vector3f v1 ,v2 , v3;
    Vector3f position;
    Vector3f intensity;
    pElement = pRoot->FirstChildElement("lights");

    XMLElement *pLight = pElement->FirstChildElement("ambientlight");
    XMLElement *lightElement;
    str = pLight->GetText();
    sscanf(str, "%f %f %f", &ambientLight.r, &ambientLight.g, &ambientLight.b);
    pLight = pElement->FirstChildElement("pointlight");
    while(pLight != nullptr)
    {   
        eResult = pLight->QueryIntAttribute("id", &id);

        lightElement = pLight->FirstChildElement("position");
        str = lightElement->GetText();
        sscanf(str, "%f %f %f", &position.x, &position.y, &position.z);
        lightElement = pLight->FirstChildElement("intensity");
        str = lightElement->GetText();
        sscanf(str, "%f %f %f", &intensity.r, &intensity.g, &intensity.b);
        lightSources.push_back(new PointLightSource(id, intensity,position));

        pLight = pLight->NextSiblingElement("pointlight");
    }

    
    pLight = pElement->FirstChildElement("triangularlight");
    while(pLight != nullptr)
    {
        eResult = pLight->QueryIntAttribute("id", &id);
        
        lightElement = pLight->FirstChildElement("vertex1");
        str = lightElement->GetText();
        sscanf(str, "%f %f %f", &v1.x, &v1.y, &v1.z);
        //std::cerr << v1.x << v1.y << v1.z << std::endl;

        lightElement = pLight->FirstChildElement("vertex2");
        str = lightElement->GetText();
        sscanf(str, "%f %f %f", &v2.x, &v2.y, &v2.z);
        lightElement = pLight->FirstChildElement("vertex3");
        str = lightElement->GetText();
        sscanf(str, "%f %f %f", &v3.x, &v3.y, &v3.z);
        lightElement = pLight->FirstChildElement("intensity");
        str = lightElement->GetText();
        sscanf(str, "%f %f %f", &intensity.r, &intensity.g, &intensity.b);

        lightSources.push_back(new TriangularLightSource(id, intensity, v1, v2 , v3));

        pLight = pLight->NextSiblingElement("triangularlight");
    }


}




void renderRows(Image &image, Scene* scene, std::atomic<int> &nextRow) {
    Vector3f pixelColor;
    ImagePlane* imagePlane = &scene->camera.imagePlane;
    RayTracing rayTracing;
    int row;
    while ((row = nextRow.fetch_add(1)) < image.height) {
        for (int i = 0; i < (*imagePlane).nx; ++i) {
            Hit minIntersection = {INF, {}, -1};
            Ray primaryRay = rayTracing.findPrimaryRay(scene->camera, row, i);
            Hit hit = rayTracing.intersect(primaryRay, scene->objects);
            if (hit.t != INF) {
                pixelColor = rayTracing.calculateRadiance(primaryRay, scene->objects, scene->lightSources, scene->ambientLight, hit, scene->materials, scene->maxraytracedepth);
            } else {
                // background color
                pixelColor = scene->backgroundColor;
            }
            pixelColor.r = std::min(std::max(0.0f, pixelColor.r), 255.0f);
            pixelColor.g = std::min(std::max(0.0f, pixelColor.g), 255.0f);
            pixelColor.b = std::min(std::max(0.0f, pixelColor.b), 255.0f);
            image.setPixelValue(i, row, {static_cast<unsigned char>(pixelColor.r),
                                          static_cast<unsigned char>(pixelColor.g),
                                          static_cast<unsigned char>(pixelColor.b)});
        }
    }
}

void Scene::render(Image &image, const char *name) {
    
        auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    std::atomic<int> nextRow(0);

    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(renderRows, std::ref(image), this, std::ref(nextRow));
    }

    for (std::thread& thread : threads) {
        thread.join();
    }
     auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Elapsed time: " << duration.count() << " milliseconds" << std::endl;
    image.saveImage(name);
}