#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorcheckclassChildrenSet.h"

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

void MainWindow::on_loadCheckPb_clicked()
{
    ui->resCheckTe->clear();
    QString address = QFileDialog::getOpenFileName(this,"Open Text file", "C:\\", tr("Text Files (*.json)"));
    ui->nameFileLe->setText(address);
    try
    {
        fileReader file(address.toStdString());
        string fileContent = file.getContent();
        textPrint(fileContent);
        objectJsonSet jsonRoot(fileContent);
        jsonRoot.corrUncorr();
        ui->infLa->setText("<html><head/><body><p style=\"background-color:green;\" align=\"center\">Валидный JSON</p></body></html>");
    }
    catch (exceptionJson &error) {
        setErrorColor(error.where(), error.whereStr());
        ui->infLa->setText("<html><head/><body><p style=\"background-color:red;\" align=\"center\">Невалидный JSON</p></body></html>");
        messageError(error.what(), NULL);

    }
    catch ( const std::exception& e ) {
        messageError(e.what(), NULL);
    }
}

void MainWindow::setErrorColor(int pos, string str)
{
    QTextCharFormat fmt;
    fmt.setBackground(Qt::red);
    QTextCursor cursor(ui->resCheckTe->document());
    if (pos == -1) {
       std::cout << ui->resCheckTe->document()->toRawText().length() << std::endl;
       cursor.setPosition(ui->resCheckTe->document()->toRawText().length() - 3, QTextCursor::MoveAnchor);
       cursor.setPosition(ui->resCheckTe->document()->characterCount() - 1, QTextCursor::KeepAnchor);
    } else if (str.length() > 0) {
        cursor.setPosition(ui->resCheckTe->document()->find(str.c_str()).position(), QTextCursor::MoveAnchor);
        cursor.setPosition(ui->resCheckTe->document()->find(str.c_str()).position() - str.length(), QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(pos+1, QTextCursor::MoveAnchor);
        cursor.setPosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    }
    cursor.setCharFormat(fmt);
}

void MainWindow::messageError(const char * msg, const char *  where)
{
    QMessageBox message;
    message.setText("Ошибка");
    QString strErrorMessage = msg;
    if (where != std::nullptr_t()) {
        strErrorMessage += "Рядом с ";
        strErrorMessage += where;
        strErrorMessage +=   ".";
    }
    strErrorMessage += "Пожалуйста исправте ошибку и повторите проверку снова. ";
    message.setInformativeText(strErrorMessage);
    message.exec();
}

void MainWindow::textPrint(string &text)
{
    stringFormatter sf(text);
    ui->resCheckTe->setText(QString::fromStdString(sf.prepare()));
}

void MainWindow::on_action_json_triggered()
{
    try {
        fileReader file("jsonHelp.txt");
        string fileContent = file.getContent();
        ui->resCheckTe->setText(QString::fromStdString(fileContent));
    } catch (const std::exception& e) {
        messageError(e.what(), NULL);
    }
}

void MainWindow::on_action_triggered()
{
    try {
        fileReader file("checkErrorJson.txt");
        string fileContent = file.getContent();
        ui->resCheckTe->setText(QString::fromStdString(fileContent));
    } catch (const std::exception& e) {
        messageError(e.what(), NULL);
    }
}
