#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->standart_btn, SIGNAL(clicked()), this, SLOT(set_default()));
    connect(ui->standart_btn_2, SIGNAL(clicked()), this, SLOT(set_default2()));
    connect(ui->move_minus_x_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->move_plus_x_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->move_minus_y_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->move_plus_y_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->move_minus_z_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->move_plus_z_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->rotate_minus_x_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->rotate_plus_x_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->rotate_minus_y_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->rotate_plus_y_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->rotate_minus_z_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->rotate_plus_z_btn, SIGNAL(clicked()), this, SLOT(update_edit()));
    connect(ui->show_btn, SIGNAL(clicked()), this, SLOT(show_drawing()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_browse_btn_clicked()
{
    QString address = QFileDialog::getOpenFileName(this,"Open Text file", "C:\\", tr("Text Files (*.csv)"));
    ui->file_name_le->setText(address);
}

void MainWindow::set_default()
{
  ui->step_le->setText("1");
  ui->range_le->setText("1,300");
  ui->move_x_le->setText("-200");
  ui->move_y_le->setText("200");
  ui->move_z_le->setText("-400");
  ui->rotate_x_le->setText("30");
  ui->rotate_y_le->setText("45");
  ui->rotate_z_le->setText("-45");
  show_drawing();
}

void MainWindow::set_default2()
{
  ui->step_le->setText("1");
  ui->range_le->setText("1,300");
  ui->move_x_le->setText("6");
  ui->move_y_le->setText("320");
  ui->move_z_le->setText("-100");
  ui->rotate_x_le->setText("38");
  ui->rotate_y_le->setText("-225");
  ui->rotate_z_le->setText("-27");
  show_drawing();
}

void MainWindow::update_edit()
{
  QObject *senderObj = sender();
  QString senderObjName = senderObj->objectName();
  QLineEdit *le;
  bool is_plus = false;
  if (senderObjName == "move_minus_x_btn") {
    le = ui->move_x_le;
  } else if (senderObjName == "move_plus_x_btn") {
      is_plus = true;
      le = ui->move_x_le;
  } else if (senderObjName == "move_minus_y_btn") {
      le = ui->move_y_le;
  } else if (senderObjName == "move_plus_y_btn") {
      is_plus = true;
      le = ui->move_y_le;
  } else if (senderObjName == "move_minus_z_btn") {
      le = ui->move_z_le;
  } else if (senderObjName == "move_plus_z_btn") {
      is_plus = true;
      le = ui->move_z_le;
  } else if (senderObjName == "rotate_minus_x_btn") {
      le = ui->rotate_x_le;
  } else if (senderObjName == "rotate_plus_x_btn") {
      is_plus = true;
      le = ui->rotate_x_le;
  } else if (senderObjName == "rotate_minus_y_btn") {
      le = ui->rotate_y_le;
  } else if (senderObjName == "rotate_plus_y_btn") {
      is_plus = true;
      le = ui->rotate_y_le;
  } else if (senderObjName == "rotate_minus_z_btn") {
      le = ui->rotate_z_le;
  } else {
      is_plus = true;
      le = ui->rotate_z_le;
  }
  double value = le->text().toDouble();
  if (is_plus) {
    value += 1;
  } else {
    value -= 1;
  }
  QString str;
  str.setNum(value);
  le->setText(str);
}

void MainWindow::show_drawing()
{
    if (ui->file_name_le->text().isEmpty()) {
       QMessageBox::critical(this, "Ошибка", "Необходимо указать путь до файла.");
    } else {
      operation_t op;
      malloc_op_chars(op);

      result_figure_t result;

      set_factors(op);

      result = execute_operation(op);

      if (result.error) {
          QMessageBox::critical(this, "Ошибка", "Поля Шаг и Диапазон обязательны для корректного заполнения.");
      } else {
          print_figure(result, op);
      }
      free_op_chars(op);
      free_result_values(result);
    }
}


void MainWindow::print_figure(result_figure_t &result, operation_t &oper)
{
        QGraphicsScene *scene = new QGraphicsScene;

        ui->graphicsView->setScene(scene);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        scene->setSceneRect(-500, -500, 1000, 1000);

        int pont_radius = 2;

        for (int i = 0; i < XY_MAX_COUNT; i++) {
            if (i % oper.step == 0)
                point = scene->addEllipse(result.xs[i][0], result.ys[i][0], pont_radius, pont_radius);

        for (int j = 0; j < XY_MAX_COUNT - oper.step; j++)
            if (i % oper.step == 0 && j % oper.step == 0) {
                scene->addLine(result.xs[i][j], result.ys[i][j], result.xs[i][j + oper.step], result.ys[i][j + oper.step]);
                point = scene->addEllipse(result.xs[i][j + oper.step], result.ys[i][j + oper.step], pont_radius, pont_radius);
            }
        }

        for (int j = 0; j < XY_MAX_COUNT; j++)
            for (int i= 0; i < XY_MAX_COUNT - oper.step; i++)
                if (i % oper.step == 0 && j % oper.step == 0)
                    scene->addLine(result.xs[i][j], result.ys[i][j], result.xs[i + oper.step][j], result.ys[i + oper.step][j]);
}



void MainWindow::set_factors(operation_t &op)
{
    QString range, deegre_str_x, deegre_str_y, deegre_str_z, mov_factor_str_x, mov_factor_str_y, mov_factor_str_z;
    op.step = ui->step_le->text().toDouble();
    QByteArray buf = ui->file_name_le->text().toLocal8Bit();

    string_copy(op.path, buf.data(), strlen(buf.data()) + 1);
    mov_factor_str_x = ui->move_x_le->text();
    buf = mov_factor_str_x.toLocal8Bit();

    string_copy(op.mfactor_str_x, buf.data(), strlen(buf.data()) + 1);
    mov_factor_str_y = ui->move_y_le->text();
    buf = mov_factor_str_y.toLocal8Bit();

    string_copy(op.mfactor_str_y, buf.data(), strlen(buf.data()) + 1);
    mov_factor_str_z = ui->move_z_le->text();
    buf = mov_factor_str_z.toLocal8Bit();

    string_copy(op.mfactor_str_z, buf.data(), strlen(buf.data()) + 1);
    deegre_str_x = ui->rotate_x_le->text();
    buf = deegre_str_x.toLocal8Bit();

    string_copy(op.degree_str_x, buf.data(), strlen(buf.data()) + 1);
    deegre_str_y = ui->rotate_y_le->text();
    buf = deegre_str_y.toLocal8Bit();

    string_copy(op.degree_str_y, buf.data(), strlen(buf.data()) + 1);
    deegre_str_z = ui->rotate_z_le->text();
    buf = deegre_str_z.toLocal8Bit();

    string_copy(op.degree_str_z, buf.data(), strlen(buf.data()) + 1);
    range = ui->range_le->text();
    buf = range.toLocal8Bit();

    string_copy(op.range, buf.data(), strlen(buf.data()) + 1);
}


void MainWindow::malloc_op_chars(operation_t & op)
{
    op.range = new char[CHARS_MAX_COUNT];
    op.path = new char[CHARS_MAX_COUNT];
    op.mfactor_str_x = new char[CHARS_MAX_COUNT];
    op.mfactor_str_y = new char[CHARS_MAX_COUNT];
    op.mfactor_str_z = new char[CHARS_MAX_COUNT];
    op.degree_str_x = new char[CHARS_MAX_COUNT];
    op.degree_str_y = new char[CHARS_MAX_COUNT];
    op.degree_str_z = new char[CHARS_MAX_COUNT];
}


void MainWindow::malloc_result_values(result_figure_t &r)
{
    r.zs = malloc_values(VALUES_MAX_COUNT);
    r.xs = malloc_values(VALUES_MAX_COUNT);
    r.ys = malloc_values(VALUES_MAX_COUNT);
}

void MainWindow::free_result_values(result_figure_t &r)
{
  delete r.zs;
  delete r.zs;
  delete r.zs;
}

void MainWindow::free_op_chars(operation_t &op)
{
  delete op.range;
  delete op.path;
  delete op.mfactor_str_x;
  delete op.mfactor_str_y;
  delete op.mfactor_str_z;
  delete op.degree_str_x;
  delete op.degree_str_y;
  delete op.degree_str_z;

}
