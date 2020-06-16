#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#define MATRIX_SIZE 4

#include "3DPoint.h"
using namespace std;
class TransformMatrix
{
private:
    float TransformPointOnAxis(Point &point, int i);
    float matr[MATRIX_SIZE][MATRIX_SIZE];
public:
    TransformMatrix(){};
    TransformMatrix(float array[MATRIX_SIZE][MATRIX_SIZE]);   
    void SetMatrix(float array[MATRIX_SIZE][MATRIX_SIZE]);
    void TransformPoint(Point &point);
};

#endif // TRANSFORMMATRIX_H
