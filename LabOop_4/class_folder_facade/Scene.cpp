#include "Scene.h"

vector<Figure> Scene::GetFigures()
{
    return figures;
}

void Scene::TransformFigures(TransformMatrix &matrix, int countFig)
{
    figures[countFig].Transform(matrix);
}

Scene::Scene(vector<Figure> &figure)
{
    figures = figure;
}

void Scene::SetFigure(vector<Figure> &figure)
{
    figures = figure;
}
