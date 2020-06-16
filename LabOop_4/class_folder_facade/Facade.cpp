#include "Facade.h"

FacadeOperationResult Facade::DrawScene()
{
    QGraphicsScene graphicsScene;
    QtSceneDrawer drawer(graphicsView, &graphicsScene);
    drawer.graphicsScene = new QGraphicsScene();
    drawer.graphicsScene->clear();
    sceneDrawer = &drawer;
    for(size_t i = 0; i < scene.GetFigures().size(); i++)
    {
        sceneDrawer->DrawScene(scene, i);
    }
    return FacadeOperationResult::GetOkResult();
}

FacadeOperationResult Facade::LoadScene(string path, NormalizationParametrs &parametrs)
{
    scene = fileReader->ReadScene(path, parametrs);
    return FacadeOperationResult::GetOkResult();
}

FacadeOperationResult Facade::MoveScene(float x, float y, float z, int figureNumber)
{
    return modifiedScene(build.CreateMoveMatrix(x, y, z), figureNumber);
}

FacadeOperationResult Facade::ScaleScene(float x, float y, float z, int figureNumber)
{
    return modifiedScene(build.CreateScaleMatrix(x, y, z), figureNumber);
}

FacadeOperationResult Facade::RotateScene(float x, float y, float z, int figureNumber)
{
    return modifiedScene(build.CreateRotationMatrix(x, y, z), figureNumber);
}

FacadeOperationResult Facade::modifiedScene(TransformMatrix matr, int figureNumber)
{
    scene.TransformFigures(matr, figureNumber);
    return FacadeOperationResult::GetOkResult();
}

Scene Facade::GetScene()
{
    return scene;
}


Facade::Facade(BaseFileReader *reader, SceneDrawerBase *drawer)
{
    sceneDrawer = drawer;
    fileReader = reader;
}

Facade::~Facade()
{
    delete &sceneDrawer;
    delete &sceneDrawer;
}

