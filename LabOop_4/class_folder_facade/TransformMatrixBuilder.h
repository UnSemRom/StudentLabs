#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H

#define CONST_SCALE 1.5
#define CONST_MOVE 50

#include "TransformMatrix.h"
using namespace std;
class TransformMatrixBuilder
{
public:
    static TransformMatrix CreateMoveMatrix(float x, float y, float z);
    static TransformMatrix CreateScaleMatrix(float x, float y, float z);
    static TransformMatrix CreateRotationMatrix(float x, float y, float z);
    TransformMatrixBuilder(){};
};

#endif // TRANSFORMMATRIXBUILDER_H
