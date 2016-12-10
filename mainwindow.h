#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userinformation.h"
#include "followersintersection.h"
#include "twitterclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, private twitterClient
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    userInformation* usrInfo;
    followersIntersection* folIntrs;
    bool _created;
};

#endif // MAINWINDOW_H
