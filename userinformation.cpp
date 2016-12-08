#include "userinformation.h"
#include "ui_userinformation.h"
#include <QDebug>

userInformation::userInformation(QWidget *parent) :
    QDialog(parent),
    twitterClient(),
    ui(new Ui::userInformation)
{
    ui->setupUi(this);
    this->setFixedHeight(450);
    this->setFixedWidth(920);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
}

userInformation::~userInformation()
{
    delete ui;
}

void userInformation::on_pushButton_clicked()
{
    username = ui->lineEdit->text().toStdString();
    getUserInfo();
    setFollowers();
    setFriends();
}

void userInformation::getUserInfo()
{
    ui->textBrowser->clear();
    if (twitterObj.userGet(username, 0))
        twitterObj.getLastWebResponse(replyMsg);
    else twitterObj.getLastCurlError(replyMsg);
    qReplyInfo = QString::fromStdString(replyMsg);
    infDoc = QJsonDocument::fromJson(qReplyInfo.toUtf8());
    if (!infDoc.isNull() && infDoc.isObject()) {
        info = infDoc.object();
        if (info["id_str"].toString()=="") ui->textBrowser->setText("User not found!");
        else
            ui->textBrowser->setText("ID: " + (info["id_str"].toString()) + "\nName: " + info["name"].toString() +
                    "\nUsername: " + info["screen_name"].toString() + "\nLocation: " + info["location"].toString() +
                    "\nDescription: " + info["description"].toString() + "\nRegistered at: " + info["created_at"].toString() +
                    "\nTweets: " + QString::number(info["statuses_count"].toInt()) +
                    "\nFollowers: " + QString::number(info["followers_count"].toInt()) +
                    "\nFriends: " + QString::number(info["friends_count"].toInt()) +
                    "\nFavourites: " + QString::number(info["favourites_count"].toInt()) +
                    "\nTime zone: " + info["time_zone"].toString() + "\nHomepage: " +
                    info["entities"].toObject()["url"].toObject()["urls"].toArray()[0].toObject()["display_url"].toString() +
                    "\nLast tweet: \"" + info["status"].toObject()["text"].toString() + "\" created at " +
                    info["status"].toObject()["created_at"].toString());
    }
}

void userInformation::setFollowers()
{
    ui->textBrowser_2->clear();

    folUsrnms=getFollowers(username);

    for (size_t i=0; i<folUsrnms.size(); i++)
        ui->textBrowser_2->append(folUsrnms[i]);
    if (previous_cursor_fol=="0") ui->pushButton_2->setDisabled(true);
    else ui->pushButton_2->setEnabled(true);
    if (next_cursor_fol=="0") ui->pushButton_3->setDisabled(true);
    else ui->pushButton_3->setEnabled(true);
}

void userInformation::setFriends() {
    ui->textBrowser_3->clear();

    frUsrnms=getFriends(username);

    for (size_t i=0; i<frUsrnms.size(); i++)
        ui->textBrowser_3->append(frUsrnms[i]);

    if (previous_cursor_fr=="0") ui->pushButton_4->setDisabled(true);
    else ui->pushButton_4->setEnabled(true);
    if (next_cursor_fr=="0") ui->pushButton_5->setDisabled(true);
    else ui->pushButton_5->setEnabled(true);
}

void userInformation::on_pushButton_2_clicked()
{
    _cursor=previous_cursor_fol.toStdString();
    setFollowers();
}

void userInformation::on_pushButton_3_clicked()
{
    _cursor=next_cursor_fol.toStdString();
    setFollowers();
}

void userInformation::on_pushButton_4_clicked()
{
    _cursor=previous_cursor_fr.toStdString();
    setFriends();
}

void userInformation::on_pushButton_5_clicked()
{
    _cursor=next_cursor_fr.toStdString();
    setFriends();
}
