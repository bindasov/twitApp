#include "followersintersection.h"
#include "ui_followersintersection.h"

followersIntersection::followersIntersection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::followersIntersection)
{
    ui->setupUi(this);
    this->setFixedHeight(450);
    this->setFixedWidth(680);
}

followersIntersection::~followersIntersection()
{
    delete ui;
}

void followersIntersection::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    username=ui->lineEdit->text().toStdString();
    username2=ui->lineEdit_2->text().toStdString();
    try {
        getSharedFollowers();
        getSharedFriends();
    }
    catch (std::runtime_error& e) {
            error_handler("followersIntersection", e.what());
    }
}

void followersIntersection::getSharedFollowers()
{
    folUsrnms=getFollowers(username);
    folUsrnms2=getFollowers(username2);

    for (size_t i=0; i<folUsrnms.size(); i++) {
        for (size_t j=0; j<folUsrnms2.size(); j++)
            if (folUsrnms[i]==folUsrnms2[j]) sharedFollowers.push_back(folUsrnms[i]);
    }
    for (size_t i=0; i<sharedFollowers.size(); i++) ui->textBrowser->append(sharedFollowers[i]);
    sharedFollowers.clear();
}

void followersIntersection::getSharedFriends()
{
    frUsrnms=getFriends(username);
    frUsrnms2=getFriends(username2);

    for (size_t i=0; i<frUsrnms.size(); i++) {
            for (size_t j=0; j<frUsrnms2.size(); j++)
                if (frUsrnms[i]==frUsrnms2[j]) sharedFriends.push_back(frUsrnms[i]);
    }
    for (size_t i=0; i<sharedFriends.size(); i++) ui->textBrowser_2->append(sharedFriends[i]);
    sharedFriends.clear();
}
