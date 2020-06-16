#ifndef SCENEDRAWERBASE_H
#define SCENEDRAWERBASE_H

#include "Scene.h"
using namespace std;
class SceneDrawerBase
{  
public:
    SceneDrawerBase(){};
    virtual void DrawScene(Scene &scene, int countFig) = 0;
};

#endif // SCENEDRAWERBASE_H
