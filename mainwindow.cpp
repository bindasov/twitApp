#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedHeight(150);
    this->setFixedWidth(300);
    usrInfo = new userInformation;
    folIntrs = new followersIntersection;
}

MainWindow::~MainWindow()
{
    usrInfo->close();
    folIntrs->close();
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
