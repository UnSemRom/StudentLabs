#ifndef FIGURE_H
#define FIGURE_H

#include "Vertex.h"
#include "SceneObject.h"

#include "library.h"

using namespace std;

class Figure : public SceneObject
{
private:
    vector<Vertex> vertices;
    int QuantityI;
    int QuantityJ;
public:
    Figure(){};
    Figure(vector<Vertex> &figure, int i, int j);
    vector<Vertex> GetVertices();
    void SetQuantity_i(int i);
    void SetQuantity_j(int j);
    int GetQuantity_i();
    int GetQuantity_j();
    void SetFigure(vector<Vertex> &figure, int i, int j);
    void AddVertex(Vertex &position);
    void Transform(TransformMatrix &matrix) override;
};

#endif // FIGURE_H
