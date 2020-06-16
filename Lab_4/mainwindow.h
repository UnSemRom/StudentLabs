#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QDialog>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "exec.h"
#include "structures_data.h"

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
    void on_browse_btn_clicked();
    void update_edit();
    void show_drawing();
    void set_default();
    void set_default2();

private:
    Ui::MainWindow *ui;
    QGraphicsEllipseItem *point;
    void print_figure(result_figure_t &res, operation_t &oper);
    void set_factors(operation_t &oper);
    void malloc_result_values(result_figure_t &res);
    void malloc_op_chars(operation_t &oper);
    void free_result_values(result_figure_t &res);
    void free_op_chars(operation_t &op);
};
#endif // MAINWINDOW_H
