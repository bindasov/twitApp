#ifndef TWITTERCLIENT_H
#define TWITTERCLIENT_H
#include <twitcurl.h>
#include <curl/curl.h>
#include <string>
#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <vector>
#include <QString>
#include <QDebug>
#include <QMessageBox>

class twitterClient
{
protected:
    twitCurl twitterObj;
    char PROTECT_STACK[1]; // чтобы все работало
    std::string followersUrl, friendsUrl;
    std::string username, username2, tempusr;
    std::string replyMsg, _cursor;
    QString qReplyFol, qReplyInfo;
    QJsonObject fol, fr, info;
    QJsonDocument folDoc, frDoc, infDoc;
    std::vector<QString> folUsrnms, folUsrnms2, sharedFollowers;
    std::vector<QString> frUsrnms, frUsrnms2, sharedFriends;
    QString next_cursor_fol, previous_cursor_fol, next_cursor_fr, previous_cursor_fr;

public:
    twitterClient();
    std::vector<QString> getFollowers(std::string& usrnm);
    std::vector<QString> getFriends(std::string& usrnm);
    QJsonDocument getUserInfo(std::string& usrnm);
    bool checkConnection();
    void error_handler(std::string name, std::string what);
};

#endif // TWITTERCLIENT_H
