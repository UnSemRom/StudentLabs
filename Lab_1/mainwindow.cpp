#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>


double num_first;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_calc_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->btn_calc_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));

    connect(ui->btn_calc_plus_minus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->bnt_calc_percent,SIGNAL(clicked()),this,SLOT(operations()));

    connect(ui->bnt_calc_divide,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->btn_calc_minus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->btn_calc_plus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->bnt_calc_umnoj,SIGNAL(clicked()),this,SLOT(math_operations()));


    ui->bnt_calc_divide->setCheckable(true);
    ui->btn_calc_minus->setCheckable(true);
    ui->btn_calc_plus->setCheckable(true);
    ui->bnt_calc_umnoj->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton* button = (QPushButton*)sender();

    double all_numbers;

    QString new_label;

    if (ui->btn_calc_res->text().contains(".") && button->text() == "0")
    {
        new_label = ui->btn_calc_res->text()+button->text();
    }
    else
    {

        all_numbers = (ui->btn_calc_res->text()+button->text()).toDouble();

        new_label = QString::number(all_numbers,'g',15);
    }

    ui->btn_calc_res->setText(new_label);


}

void MainWindow::on_btn_calc_point_clicked()
{
    if(!(ui->btn_calc_res->text().contains(".")))
    {
        ui->btn_calc_res->setText( ui->btn_calc_res->text()+".");
    }
}

void MainWindow::operations()
{
    QPushButton* button = (QPushButton*)sender();

    double all_numbers;

    QString new_label;


    if(button->text() == "+/-")
    {

        all_numbers = (ui->btn_calc_res->text()).toDouble();

        all_numbers = all_numbers* -1;

        new_label = QString::number(all_numbers,'g',15);

        ui->btn_calc_res->setText(new_label);
    }

    else if(button->text() == "%")
    {

        all_numbers = (ui->btn_calc_res->text()).toDouble();

        all_numbers = all_numbers* 0.01;

        new_label = QString::number(all_numbers,'g',15);

        ui->btn_calc_res->setText(new_label);
    }

}


void MainWindow::math_operations()
{
     QPushButton* button = (QPushButton*)sender();

     num_first = ui->btn_calc_res->text().toDouble();
     ui->btn_calc_res->setText("");

     button->setChecked(true);

}

void MainWindow::on_bnt_calc_C_clicked()
{
    ui->btn_calc_plus->setChecked(false);
    ui->btn_calc_minus->setChecked(false);
    ui->bnt_calc_divide->setChecked(false);
    ui->bnt_calc_umnoj->setChecked(false);
    ui->btn_calc_res->setText("0");

}

void MainWindow::on_btn_cacl_ravno_clicked()
{
    double label_number, num_second;
    QString new_label;
    num_second = ui->btn_calc_res->text().toDouble();
    if(ui->btn_calc_plus->isChecked())
    {
        label_number = num_first + num_second;
        new_label = QString::number(label_number,'g',15);
        ui->btn_calc_res->setText(new_label);
        ui->btn_calc_plus->setChecked(false);
    }
    if(ui->btn_calc_minus->isChecked())
    {
        label_number = num_first - num_second;
        new_label = QString::number(label_number,'g',15);
        ui->btn_calc_res->setText(new_label);
        ui->btn_calc_minus->setChecked(false);
    }
    if(ui->bnt_calc_divide->isChecked())
    {
        if(num_second == 0)
        {
            ui->btn_calc_res->setText(new_label);
        }
        else
        {
            label_number = num_first / num_second;
            new_label = QString::number(label_number,'g',15);
            ui->btn_calc_res->setText(new_label);
        }
        ui->bnt_calc_divide->setChecked(false);
    }
    if(ui->bnt_calc_umnoj->isChecked())
    {
        label_number = num_first * num_second;
        new_label = QString::number(label_number,'g',15);
        ui->btn_calc_res->setText(new_label);
        ui->bnt_calc_umnoj->setChecked(false);
    }

}

void MainWindow::on_btn_calc_DEL_clicked()
{
    ui->btn_calc_plus->setChecked(false);
    ui->btn_calc_minus->setChecked(false);
    ui->bnt_calc_divide->setChecked(false);
    ui->bnt_calc_umnoj->setChecked(false);

    double label_number, num_second;
    QString new_label;
    num_second = ui->btn_calc_res->text().toDouble();
    label_number = num_second;
    new_label = QString::number(label_number,'g',15);
    if(new_label.length() == 1)
    {
       label_number = 0;
       new_label = QString::number(label_number,'g',15);
       ui->btn_calc_res->setText(new_label);
    }
    else
    {
       new_label.remove(new_label.length()-1,1);
       ui->btn_calc_res->setText(new_label);
    }

}
