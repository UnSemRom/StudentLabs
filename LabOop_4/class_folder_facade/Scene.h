#ifndef SCENE_H
#define SCENE_H

#include "TransformMatrix.h"
#include "Figure.h"
using namespace std;
class Scene
{
private:
    vector<Figure> figures;
public:
    Scene(){};
    Scene(vector<Figure> &figure);
    vector<Figure> GetFigures();
    void SetFigure(vector<Figure> &figure);
    void TransformFigures(TransformMatrix &matrix, int countFig);
};

#endif // SCENE_H
