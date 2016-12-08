#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include "twitterclient.h"

namespace Ui {
class userInformation;
}

class userInformation : public QDialog, private twitterClient
{
    Q_OBJECT

public:
    explicit userInformation(QWidget *parent = 0);
    void getUserInfo();
    void setFollowers();
    void setFriends();
    ~userInformation();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::userInformation *ui;
};

#endif // USERINFORMATION_H
