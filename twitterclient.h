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

class twitterClient
{
private:
    std::string ConsumerKey, ConsumerSecret, AccessTokenKey, AccessTokenSecret;

protected:
    twitCurl twitterObj;
    std::string followersUrl = "https://api.twitter.com/1.1/followers/list.json?skip_status=true&include_user_entities=false&count=200&screen_name=";
    std::string friendsUrl = "https://api.twitter.com/1.1/friends/list.json?skip_status=true&include_user_entities=false&count=200&screen_name=";
    std::string username, username0, username2;
    std::string replyMsg;
    QString qReplyFol, qReplyInfo;
    QJsonObject fol, fr, info;
    QJsonDocument folDoc, frDoc, infDoc;
    std::vector<QString> folUsrnms, folUsrnms2, sharedFollowers;
    std::vector<QString> frUsrnms, frUsrnms2, sharedFriends;
    QString next_cursor_fol, previous_cursor_fol, next_cursor_fr, previous_cursor_fr;
    std::string _cursor="-1";

public:
    twitterClient();
    std::vector<QString> getFollowers(std::string& usrnm);
    std::vector<QString> getFriends(std::string& usrnm);

};

#endif // TWITTERCLIENT_H
