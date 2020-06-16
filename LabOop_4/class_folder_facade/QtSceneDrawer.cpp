#include "QtSceneDrawer.h"

void QtSceneDrawer::DrawScene(Scene &scene,  int countFig)
{
    graphicsView->setScene(graphicsScene);
    QPen penForLine(Qt::darkRed,2);
    QPen penForPoint(Qt::darkRed,3);
    DrawLineX(penForLine, scene, countFig);
    DrawLineY(penForLine, scene, countFig);
    DrawPoint(penForPoint, scene, countFig);
}

void QtSceneDrawer::DrawPoint(QPen penForPoint, Scene &scene, int countFig)
{
    for(int i = 0; i < scene.GetFigures()[countFig].GetQuantity_i(); i++)
    {
        for(int j = 0; j < scene.GetFigures()[countFig].GetQuantity_j(); j++)
        {
            float x = pointX(scene, i, j, countFig);
            float y = pointY(scene, i, j, countFig);
            graphicsScene->addLine(x, y, x, y,penForPoint);
        }
    }
}

void QtSceneDrawer::DrawLineX(QPen penForLine, Scene &scene, int countFig)
{
    for(int i = 0; i < scene.GetFigures()[countFig].GetQuantity_i(); i++)
    {
        for(int j = 0; j < scene.GetFigures()[countFig].GetQuantity_j() - 1; j++)
        {
            float x1 = pointX(scene, i, j, countFig);
            float y1 = pointY(scene, i, j, countFig);
            float x2 = pointX(scene, i, j+1, countFig);
            float y2 = pointY(scene, i, j+1, countFig);
            graphicsScene->addLine(x1, y1, x2, y2, penForLine);
        }
    }
}

void QtSceneDrawer::DrawLineY(QPen penForLine, Scene &scene, int countFig)
{
    for(int i = 0; i < scene.GetFigures()[countFig].GetQuantity_i() - 1; i++)
    {
        for(int j = 0; j < scene.GetFigures()[countFig].GetQuantity_j(); j++)
        {
            float x1 = pointX(scene, i, j, countFig);
            float y1 = pointY(scene, i, j, countFig);
            float x2 = pointX(scene, i, j + scene.GetFigures()[countFig].GetQuantity_j(), countFig);
            float y2 = pointY(scene, i, j + scene.GetFigures()[countFig].GetQuantity_j(), countFig);
            graphicsScene->addLine(x1, y1, x2, y2, penForLine);
        }
    }
}

float QtSceneDrawer::pointX(Scene &scene, int i, int j, int countFig)
{
    return scene.GetFigures()[countFig].GetVertices()[i*scene.GetFigures()[countFig].GetQuantity_j()+j].GetPosition().GetPointX();
}

float QtSceneDrawer::pointY(Scene &scene, int i, int j, int countFig)
{
    return scene.GetFigures()[countFig].GetVertices()[i*scene.GetFigures()[countFig].GetQuantity_j()+j].GetPosition().GetPointY();
}

