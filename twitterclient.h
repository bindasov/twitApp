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
private:
    std::string ConsumerKey, ConsumerSecret, AccessTokenKey, AccessTokenSecret;

protected:
    twitCurl twitterObj;
    std::string followersUrl;
    std::string friendsUrl;
    std::string username, username0, username2, tempusr;
    std::string replyMsg;
    QString qReplyFol, qReplyInfo;
    QJsonObject fol, fr, info;
    QJsonDocument folDoc, frDoc, infDoc;
    std::vector<QString> folUsrnms, folUsrnms2, sharedFollowers;
    std::vector<QString> frUsrnms, frUsrnms2, sharedFriends;
    QString next_cursor_fol, previous_cursor_fol, next_cursor_fr, previous_cursor_fr;
    std::string _cursor;

public:
    twitterClient();
    std::vector<QString> getFollowers(std::string& usrnm);
    std::vector<QString> getFriends(std::string& usrnm);
    QJsonDocument getUserInfo(std::string& usrnm);

};

#endif // TWITTERCLIENT_H
