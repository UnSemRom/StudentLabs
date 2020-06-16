#include "TransformMatrix.h"

void TransformMatrix::TransformPoint(Point &point)
{
    point.SetPointX(TransformPointOnAxis(point, 0));
    point.SetPointY(TransformPointOnAxis(point, 1));
    point.SetPointZ(TransformPointOnAxis(point, 2));
}

float TransformMatrix::TransformPointOnAxis(Point &point, int i)
{
    float Point = point.GetPointX()*matr[i][0] + point.GetPointY()*matr[i][1] + point.GetPointZ()*matr[i][2] + matr[i][3];
    return Point;
}

TransformMatrix::TransformMatrix(float array[MATRIX_SIZE][MATRIX_SIZE])
{
    for(int i = 0; i < MATRIX_SIZE; i++)
    {
        for(int j = 0; j < MATRIX_SIZE; j++)
        {
            matr[i][j] = array[i][j];
        }
    }
}

void TransformMatrix::SetMatrix(float array[MATRIX_SIZE][MATRIX_SIZE])
{
    for(int i = 0; i < MATRIX_SIZE; i++)
    {
        for(int j = 0; j < MATRIX_SIZE; j++)
        {
            matr[i][j] = array[i][j];
        }
    }
}
