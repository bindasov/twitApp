#include "userinformation.h"
#include "ui_userinformation.h"

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
    try {
        setUserInfo();
        setFollowers();
        setFriends();
    }
    catch (std::runtime_error& e) {
            QMessageBox qmsbox;
            qmsbox.setText(QString::fromStdString(e.what()));
            qmsbox.setWindowModality(Qt::WindowModal);
            qmsbox.exec();
    }
}

void userInformation::setUserInfo()
{
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    ui->textBrowser_3->clear();

    infDoc = getUserInfo(username);
    if (!infDoc.isNull() && infDoc.isObject()) {
        info = infDoc.object();
        if (info["id_str"].toString()=="") throw std::runtime_error
                (info["errors"].toArray()[0].toObject()["message"].toString().toStdString());
        ui->textBrowser->setText("ID: " + (info["id_str"].toString()) + "\nName: " + info["name"].toString() +
            "\nUsername: " + info["screen_name"].toString() + "\nLocation: " + info["location"].toString() +
            "\nDescription: " + info["description"].toString() + "\nRegistered at: " +
            info["created_at"].toString() + "\nTweets: " + QString::number(info["statuses_count"].toInt()) +
            "\nFollowers: " + QString::number(info["followers_count"].toInt()) +
            "\nFriends: " + QString::number(info["friends_count"].toInt()) +
            "\nFavourites: " + QString::number(info["favourites_count"].toInt()) +
            "\nTime zone: " + info["time_zone"].toString() + "\nHomepage: " +
            info["entities"].toObject()["url"].toObject()["urls"].toArray()[0].toObject()["display_url"].toString() +
            "\nLast tweet: \"" + info["status"].toObject()["text"].toString() + "\" created at " +
            info["status"].toObject()["created_at"].toString());
        // что-то страшное, но вроде работает
    }
}

void userInformation::setFollowers()
{
    try {
        folUsrnms=getFollowers(username);
    }
    catch (std::runtime_error& e) {
            QMessageBox qmsbox;
            qmsbox.setText(QString::fromStdString(e.what()));
            qmsbox.setWindowModality(Qt::WindowModal);
            qmsbox.exec();
    }

    for (size_t i=0; i<folUsrnms.size(); i++)
        ui->textBrowser_2->append(folUsrnms[i]);
    if (folUsrnms.size()==1) {
        ui->pushButton_2->setDisabled(true);
        ui->pushButton_3->setDisabled(true);
    }
    else {
        if (previous_cursor_fol=="0") ui->pushButton_2->setDisabled(true);
        else ui->pushButton_2->setEnabled(true);
        if (next_cursor_fol=="0") ui->pushButton_3->setDisabled(true);
        else ui->pushButton_3->setEnabled(true);
    }
}

void userInformation::setFriends() {
    try {
        frUsrnms=getFriends(username);
    }
    catch (std::runtime_error& e) {
            QMessageBox qmsbox;
            qmsbox.setText(QString::fromStdString(e.what()));
            qmsbox.setWindowModality(Qt::WindowModal);
            qmsbox.exec();
    }

    for (size_t i=0; i<frUsrnms.size(); i++)
        ui->textBrowser_3->append(frUsrnms[i]);

    if (frUsrnms.size()==1) {
        ui->pushButton_4->setDisabled(true);
        ui->pushButton_5->setDisabled(true);
    }
    else {
        if (previous_cursor_fr=="0") ui->pushButton_4->setDisabled(true);
        else ui->pushButton_4->setEnabled(true);
        if (next_cursor_fr=="0") ui->pushButton_5->setDisabled(true);
        else ui->pushButton_5->setEnabled(true);
    }
}

void userInformation::on_pushButton_2_clicked()
{
    _cursor=previous_cursor_fol.toStdString();
    try {
        setFollowers();
    }
    catch (std::runtime_error& e) {
            QMessageBox qmsbox;
            qmsbox.setText(QString::fromStdString(e.what()));
            qmsbox.setWindowModality(Qt::WindowModal);
            qmsbox.exec();
    }
}

void userInformation::on_pushButton_3_clicked()
{
    _cursor=next_cursor_fol.toStdString();
    try {
        setFollowers();
    }
    catch (std::runtime_error& e) {
            QMessageBox qmsbox;
            qmsbox.setText(QString::fromStdString(e.what()));
            qmsbox.setWindowModality(Qt::WindowModal);
            qmsbox.exec();
    }
}

void userInformation::on_pushButton_4_clicked()
{
    _cursor=previous_cursor_fr.toStdString();
    try {
        setFriends();
    }
    catch (std::runtime_error& e) {
            QMessageBox qmsbox;
            qmsbox.setText(QString::fromStdString(e.what()));
            qmsbox.setWindowModality(Qt::WindowModal);
            qmsbox.exec();
    }
}

void userInformation::on_pushButton_5_clicked()
{
    _cursor=next_cursor_fr.toStdString();
    try {
        setFriends();
    }
    catch (std::runtime_error& e) {
            QMessageBox qmsbox;
            qmsbox.setText(QString::fromStdString(e.what()));
            qmsbox.setWindowModality(Qt::WindowModal);
            qmsbox.exec();
    }
}
// так как в catch всегда одинаково, почему бы не создать отдельную функцию для этого, исключая дублирование кода
