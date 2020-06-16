#include "Figure.h"

vector<Vertex> Figure::GetVertices()
{
    return vertices;
}

void Figure::Transform(TransformMatrix &matrix)
{
    for (size_t i = 0; i < vertices.size(); i++)
    {
        vertices[i].Transform(matrix);
    }
}

void Figure::SetFigure(vector<Vertex> &figure, int i, int j)
{
    vertices.clear();
    vertices = figure;
    QuantityI = i;
    QuantityJ = j;
}

Figure::Figure(vector<Vertex> &figure, int i, int j)
{
    vertices.clear();
    vertices = figure;
    QuantityI = i;
    QuantityJ = j;
}

void Figure::AddVertex(Vertex &position)
{
    vertices.push_back(position);
}

void Figure::SetQuantity_i(int i)
{
    QuantityI = i;
}

void Figure::SetQuantity_j(int j)
{
    QuantityJ = j;
}

int Figure::GetQuantity_i()
{
    return QuantityI;
}

int Figure::GetQuantity_j()
{
    return QuantityJ;
}
