#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedHeight(150);
    this->setFixedWidth(300);
    if (checkConnection()) {
        usrInfo = new userInformation;
        folIntrs = new followersIntersection;
        _created=1;
    }
    else {
        ui->pushButton->setDisabled(true);
        ui->pushButton_2->setDisabled(true);
        QMessageBox::critical(0, "Error", "Cannot authorize you!");
        _created=0;
    }
}

MainWindow::~MainWindow()
{
    if (_created) {
        usrInfo->close();
        delete usrInfo;
        folIntrs->close();
        delete folIntrs;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    usrInfo->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    folIntrs->show();
}
