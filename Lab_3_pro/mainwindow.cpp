#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exec.h"
#include "chart.h"
#include "QMovie"

operation_t operation;
table_t table_data;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_file_select_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");
    ui->lab_inf_app_selected_file->setText(str);
    operation.filename = str.toStdString();
}

void MainWindow::print_gif()
{

    QMovie *movieNew = new QMovie( "tenor.gif" );
    ui->lab_graph->setMovie( movieNew );
    movieNew -> start();
}
void MainWindow::on_bnt_load_data_clicked()
{
    result_t res;
    QString region = ui->le_ent_reg->text();
    operation.region = region.toStdString();
    operation.type = LOAD;

    if (operation.region != "")
    {
        res = execure_operation(operation);
        table_data = res.table;

        switch(res.error)
        {
        case FALSE:
        {
            print_gif();
            print_tab();
            break;
        }
        case TRUE:
        {
            error(res.error_message, res);
            break;
        }
        case WARNING:
        {
            print_gif();
            print_tab();
            res.error_message = "Некоторые данные региона некоректны";
            error(res.error_message, res);
            break;
        }
        }
    }
}

void MainWindow::error(string str, result_t res)
{
    QString qstr = QString::fromStdString(str);
    QMessageBox::warning(this, "Внимание", qstr);
}

void MainWindow::print_chart(result_t result, QString column)
{
    QPixmap* pix_chart;

    if(column.toInt() >2)
    {
        chart_data_t chart_data;

        chart_data.year  = table_data.year;
        chart_data.max = result.max;
        chart_data.min = result.min;
        chart_data.med = result.med;

        misappropriation_colm( &chart_data.column, &operation);

        pix_chart = chart(chart_data);
    }

    ui->lab_graph->setPixmap(*pix_chart);
}

void MainWindow::on_btn_cal_met_clicked()
{
    QString column = ui->le_ent_col->text();
    QPixmap *pix_chart;

    operation.column_number = column.toInt();
    operation.table = table_data;
    operation.type = CALC_CHART;

    if (operation.region != "" && column != "")
    {
        result_t result = execure_operation(operation);
        print_metrics(&result);
        print_chart(result, column);
    }
}

void MainWindow::print_tab()
{
    QStandardItemModel* model = new QStandardItemModel;
    QStandardItem* item;
    QStringList horizontalHeader;

    horizontalHeader.append("1.Year");
    horizontalHeader.append("2.Region");
    horizontalHeader.append("3.NPG");
    horizontalHeader.append("4.Birth rate");
    horizontalHeader.append("5.Death rate");
    horizontalHeader.append("6.GDW");
    horizontalHeader.append("7.Urbanization");

    model->setHorizontalHeaderLabels(horizontalHeader);

    QString qstr;

    for (int i = 0; i < table_data.year.size(); i++)
    {

        qstr = QString::fromStdString(table_data.year[i]);
        item = new QStandardItem(qstr);
        model->setItem(i, 0, item);

        qstr = QString::fromStdString(table_data.reg[i]);
        item = new QStandardItem(qstr);
        model->setItem(i, 1, item);

        qstr = QString::fromStdString(table_data.npg[i]);
        item = new QStandardItem(qstr);
        model->setItem(i, 2, item);

        qstr = QString::fromStdString(table_data.bir_r[i]);
        item = new QStandardItem(qstr);
        model->setItem(i, 3, item);

        qstr = QString::fromStdString(table_data.dea_r[i]);
        item = new QStandardItem(qstr);
        model->setItem(i, 4, item);

        qstr = QString::fromStdString(table_data.gdw[i]);
        item = new QStandardItem(qstr);
        model->setItem(i, 5, item);

        qstr = QString::fromStdString(table_data.urb[i]);
        item = new QStandardItem(qstr);
        model->setItem(i, 6, item);

        ui->tab_reg->setModel(model);
        ui->tab_reg->resizeRowsToContents();
        ui->tab_reg->resizeColumnsToContents();
        ui->tab_reg->horizontalHeader()->resizeSections(QHeaderView::Stretch);
    }
}

void MainWindow::print_metrics(result_t *result)
{
    switch (result->error)
    {
    case FALSE:
    {
        QString stat;

        stat = QString::number(result->min);
        ui->lb_inf_min->setText(stat);

        stat = QString::number(result->max);
        ui->lb_inf_max->setText(stat);

        stat = QString::number(result->med);
        ui->lb_inf_med->setText(stat);
        break;
    }
    case TRUE:
    {
        error(result->error_message, *result);
        break;
    }
    }
}


