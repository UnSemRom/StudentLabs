#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , facade(Facade(new FileReader(), new QtSceneDrawer()))
{
    ui->setupUi(this);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(actions(int)));
    setButtonMapping(signalMapper, ui->draw, OP_DRAW);
    setButtonMapping(signalMapper, ui->scale_plus, OP_SCALE_PLUS);
    setButtonMapping(signalMapper, ui->scale_minus, OP_SCALE_MINUS);
    setButtonMapping(signalMapper, ui->Ox_right,  OP_OX_RIGHT);
    setButtonMapping(signalMapper, ui->Ox_left, OP_OX_LEFT);
    setButtonMapping(signalMapper, ui->Oy_right,  OP_OY_RIGHT);
    setButtonMapping(signalMapper, ui->Oy_left,  OP_OY_LEFT);
    setButtonMapping(signalMapper, ui->Oz_right, OP_OZ_RIGHT);
    setButtonMapping(signalMapper, ui->Oz_left, OP_OZ_LEFT);
    setButtonMapping(signalMapper, ui->move_up, OP_MOVE_UP);
    setButtonMapping(signalMapper, ui->move_down, OP_MOVE_DOWN);
    setButtonMapping(signalMapper, ui->move_left, OP_MOVE_LEFT);
    setButtonMapping(signalMapper, ui->move_right, OP_MOVE_RIGHT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonMapping(QSignalMapper *signalMapper, QPushButton *button, ButtonOperations buttonNumber)
{
    connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(button, buttonNumber);
}



void MainWindow::on_fileDialog_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "", "", "*.csv");
    if(!filename.isEmpty())
    {
        if(filename.toStdString().compare(filename.size()-4, filename.size(), ".csv") != 0)
        {
            QMessageBox::information(0, "Ошибка", "Указан файл с неправильным расширением");
            filename = nullptr;
        }
        else
        {
            ui->filename->setText(ui->filename->toPlainText()+filename);
            float min = ui->range_min->text().toFloat(&CheckMin);
            float max = ui->range_max->text().toFloat(&CheckMax);
            float stepX = ui->step_Ox->text().toFloat(&CheckStepX);
            float stepY = ui->step_Oy->text().toFloat(&CheckStepY);
            if(CheckMin && CheckMax && CheckStepX && CheckStepY)
            {
                NormalizationParametrs parametrs(min, max, stepX, stepY);
                facade.LoadScene(filename.toStdString(), parametrs);
                facade.graphicsView = ui->graphicsView;
            }
            else
                QMessageBox::information(0, "Ошибка", "Укажите корректно диапазон нормировки и шаги");

        }
    }
}

void MainWindow::actions(int buttonNum)
{
    bool ok_model;
    NumberOfFigures = ui->model_num->text().toInt(&ok_model, 10);
    float rotationDegrees = ui->arrow_range_num->text().toFloat()/57;
    if(ok_model && NumberOfFigures < facade.GetScene().GetFigures().size())
    {
        switch(buttonNum)
        {
        case OP_OX_LEFT:
        {
            facade.RotateScene(-rotationDegrees, 0.0, 0.0, NumberOfFigures);
            break;
        }
        case  OP_OX_RIGHT:
        {
            facade.RotateScene(rotationDegrees, 0.0, 0.0, NumberOfFigures);
            break;
        }
        case  OP_OY_LEFT:
        {
            facade.RotateScene(0.0, -rotationDegrees, 0.0, NumberOfFigures);
            break;
        }
        case  OP_OY_RIGHT:
        {
            facade.RotateScene(0.0, rotationDegrees, 0.0, NumberOfFigures);
            break;
        }
        case OP_OZ_LEFT:
        {
            facade.RotateScene(0.0, 0.0, -rotationDegrees, NumberOfFigures);
            break;
        }
        case OP_OZ_RIGHT:
        {
            facade.RotateScene(0.0, 0.0, rotationDegrees, NumberOfFigures);
            break;
        }
        case OP_SCALE_PLUS:
        {
            facade.ScaleScene(0.0, 0.0, CONST_SCALE, NumberOfFigures);
            break;
        }
        case OP_SCALE_MINUS:
        {
            facade.ScaleScene(0.0, 0.0, 1/CONST_SCALE, NumberOfFigures);
            break;
        }
        case OP_MOVE_UP:
        {
            facade.MoveScene(0.0, -CONST_MOVE, 0.0, NumberOfFigures);
            break;
        }
        case OP_MOVE_DOWN:
        {
            facade.MoveScene(0.0, CONST_MOVE, 0.0, NumberOfFigures);
            break;
        }
        case OP_MOVE_LEFT:
        {
            facade.MoveScene(-CONST_MOVE, 0.0, 0.0, NumberOfFigures);
            break;
        }
        case OP_MOVE_RIGHT:
        {
            facade.MoveScene(CONST_MOVE, 0.0, 0.0, NumberOfFigures);
            break;
        }
        case OP_DRAW:
        {
            break;
        }
        };
        facade.DrawScene();
    }
    else
        QMessageBox::information(0, "Ошибка", "Укажите корректно номер модели");

}
