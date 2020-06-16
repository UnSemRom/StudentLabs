#ifndef VERTEX_H
#define VERTEX_H

#include "3DPoint.h"
#include "SceneObject.h"
using namespace std;
class Vertex : public SceneObject
{
private:
    Point position;
public:
    Vertex(float x, float y, float z);
    Point GetPosition();
    void SetPosition(float x, float y, float z);
    void Transform(TransformMatrix &matrix) override;
};

#endif // VERTEX_H
