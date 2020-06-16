#include "TransformMatrixBuilder.h"
#include "library.h"

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(float x, float y, float z)
{
    float matr[MATRIX_SIZE][MATRIX_SIZE] =
    {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}
    };
    TransformMatrix transform(matr);
    return transform;
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(float x, float y, float z)
{
    float matr[MATRIX_SIZE][MATRIX_SIZE] =
    {
        {z, 0, 0, 0},
        {0, z, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}
    };
    TransformMatrix transform(matr);
    return transform;
}

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(float x, float y, float z)
{
    TransformMatrix transform;
    if(x != 0)
    {
        float matr[MATRIX_SIZE][MATRIX_SIZE] =
        {
            {1, 0, 0, 0},
            {0, cos(x), -sin(x), 0},
            {0, sin(x), cos(x), 0},
            {0, 0, 0, 1}
        };
        transform.SetMatrix(matr);
    }
    if(y != 0)
    {
        float matr[MATRIX_SIZE][MATRIX_SIZE] =
        {
            {cos(y), 0, sin(y), 0},
            {0, 1, 0, 0},
            {-sin(y), 0, cos(y), 0},
            {0, 0, 0, 1}
        };
        transform.SetMatrix(matr);
    }
    if(z != 0)
    {
        float matr[MATRIX_SIZE][MATRIX_SIZE] =
        {
            {cos(z), -sin(z), 0, 0},
            {sin(z), cos(z), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        transform.SetMatrix(matr);
    }
    return transform;
}

