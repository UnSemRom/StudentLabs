#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "library.h"

using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) ;
    ~MainWindow();

private slots:
    void on_loadCheckPb_clicked();


    void on_action_json_triggered();

    void on_action_triggered();

public:
    void textPrint(string &text);
    void messageError(const char * msg, const char *  where);
    void setErrorColor(int pos, string str);

private:
    Ui::MainWindow *ui;

};



#endif // MAINWINDOW_H
