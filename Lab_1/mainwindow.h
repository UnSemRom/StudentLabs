#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void digits_numbers();
    void on_btn_calc_point_clicked();
    void operations();

    void on_bnt_calc_C_clicked();

    void on_btn_cacl_ravno_clicked();

    void math_operations();



    void on_btn_calc_DEL_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
