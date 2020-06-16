#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "class_folder_facade/Facade.h"
#include "operations.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setButtonMapping(QSignalMapper *signalMapper, QPushButton *button, ButtonOperations buttonNumber);
    void actions(int buttonNum);
    void on_fileDialog_clicked();

private:
    QString filename;
    Ui::MainWindow *ui;
    QGraphicsScene *graphicsScene;
    Facade facade;
    bool CheckStepX, CheckStepY, CheckMax, CheckMin, checkFacade;
    int NumberOfFigures;
    QtSceneDrawer drawer;

};
#endif // MAINWINDOW_H
