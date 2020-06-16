#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "TransformMatrix.h"
using namespace std;
class SceneObject
{
protected:
    virtual void Transform(TransformMatrix &matrix) = 0;
public:
    SceneObject(){};
};

#endif // SCENEOBJECT_H
