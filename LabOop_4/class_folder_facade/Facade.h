#ifndef FACADE_H
#define FACADE_H

#include "Scene.h"
#include "SceneDrawerBase.h"
#include "QtSceneDrawer.h"
#include "TransformMatrixBuilder.h"
#include "NormalizationParametrs.h"
#include "FileReader.h"
#include "FacadeOperationResult.h"
using namespace std;

class Facade
{
private: 
    Scene scene;
    TransformMatrixBuilder build;
    FacadeOperationResult modifiedScene(TransformMatrix matr, int countFig);
    BaseFileReader *fileReader;
    SceneDrawerBase *sceneDrawer;

public:
    Facade(BaseFileReader *reader, SceneDrawerBase *drawer);
    ~Facade();
    class Scene GetScene();
    QGraphicsView *graphicsView;
    FacadeOperationResult DrawScene();
    FacadeOperationResult LoadScene(string path, NormalizationParametrs &parametrs);
    FacadeOperationResult MoveScene(float x, float y, float z, int figureNumber);
    FacadeOperationResult ScaleScene(float x, float y, float z, int figureNumber);
    FacadeOperationResult RotateScene(float x, float y, float z, int figureNumber);
};

#endif // FACADE_H
