#include "Vertex.h"

Point Vertex::GetPosition()
{
    return position;
}

void Vertex::Transform(TransformMatrix &matrix)
{
    matrix.TransformPoint(position);
}

Vertex::Vertex(float x, float y, float z)
{
    position.SetPointX(x);
    position.SetPointY(y);
    position.SetPointZ(z);
}

void Vertex::SetPosition(float x, float y, float z)
{
    position.SetPointX(x);
    position.SetPointY(y);
    position.SetPointZ(z);
}
