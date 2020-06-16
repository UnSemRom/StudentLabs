#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H

#include "SceneDrawerBase.h"
using namespace std;
class QtSceneDrawer : public SceneDrawerBase
{
private:   
    void DrawPoint(QPen penForPoint, Scene &scene, int countFig);
    void DrawLineX(QPen penForLine,  Scene &scene, int countFig);
    void DrawLineY(QPen penForLine,  Scene &scene, int countFig);
    float pointX(Scene &scene, int i, int j, int countFig);
    float pointY(Scene &scene, int i, int j, int countFig);
public:
    QtSceneDrawer(){};
    QtSceneDrawer(QGraphicsView *graphicsV, QGraphicsScene *graphicsS): graphicsView(graphicsV), graphicsScene(graphicsS){};
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    void DrawScene(Scene &scene, int countFig) override;
};

#endif // QTSCENEDRAWER_H
