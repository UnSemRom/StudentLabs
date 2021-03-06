#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "QFileDialog"
#include "QStandardItemModel"
#include <QMessageBox>
#include <QHeaderView>
#include <QPainter>

#include "exec.h"

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
    void on_btn_file_select_clicked();

    void on_bnt_load_data_clicked();

    void on_btn_cal_met_clicked();

    void print_metrics(result_t* result);

    void print_tab();

    void error(std::string str, result_t res);

    void print_chart(result_t result, QString column);

    void print_gif();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
