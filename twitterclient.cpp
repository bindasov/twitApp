#include "twitterclient.h"

twitterClient::twitterClient()
{
    ConsumerKey       = "";
    ConsumerSecret    = "";
    AccessTokenKey    = "";
    AccessTokenSecret = "";
    twitterObj.getOAuth().setConsumerKey(ConsumerKey);
    twitterObj.getOAuth().setConsumerSecret(ConsumerSecret);
    twitterObj.getOAuth().setOAuthTokenKey(AccessTokenKey);
    twitterObj.getOAuth().setOAuthTokenSecret(AccessTokenSecret);
    followersUrl = "https://api.twitter.com/1.1/followers/list.json?skip_status=true&include_user_entities=false&count=200&screen_name=";
    friendsUrl = "https://api.twitter.com/1.1/friends/list.json?skip_status=true&include_user_entities=false&count=200&screen_name=";
    _cursor = "";
}

std::vector<QString> twitterClient::getFollowers(std::string& usrnm) {
    if (usrnm=="") throw std::runtime_error("");
    if (usrnm!=tempusr) _cursor="-1";
    tempusr=usrnm;
    followersUrl+= usrnm + "&cursor=" + _cursor;

    if (twitterObj.performGet(followersUrl))
        twitterObj.getLastWebResponse(replyMsg);
    else twitterObj.getLastCurlError(replyMsg);

    std::vector<QString> folUsr;
    qReplyFol = QString::fromStdString(replyMsg);
    folDoc = QJsonDocument::fromJson(qReplyFol.toUtf8());
    if (!folDoc.isNull() && folDoc.isObject()) {
        fol = folDoc.object();
        previous_cursor_fol=fol["previous_cursor_str"].toString();
        next_cursor_fol=fol["next_cursor_str"].toString();

        if (fol["errors"].toArray().size()>0) throw std::runtime_error
                (fol["errors"].toArray()[0].toObject()["message"].toString().toStdString());
        folUsr.resize(fol["users"].toArray().size());
        for (size_t i=0; i<folUsr.size(); i++)
            folUsr[i]=fol["users"].toArray()[i].toObject()["screen_name"].toString();
    }
    followersUrl.erase(followersUrl.find(usrnm));
    return folUsr;
}

std::vector<QString> twitterClient::getFriends(std::string& usrnm) {
    if (usrnm=="") throw std::runtime_error("");
    if (usrnm!=tempusr) _cursor="-1";
    tempusr=usrnm;
    friendsUrl+= usrnm + "&cursor=" + _cursor;

    if (twitterObj.performGet(friendsUrl))
        twitterObj.getLastWebResponse(replyMsg);
    else twitterObj.getLastCurlError(replyMsg);

    std::vector<QString> frUsr;
    qReplyFol = QString::fromStdString(replyMsg);
    frDoc = QJsonDocument::fromJson(qReplyFol.toUtf8());
    if (!frDoc.isNull() && frDoc.isObject()) {
        fr = frDoc.object();
        previous_cursor_fr=fr["previous_cursor_str"].toString();
        next_cursor_fr=fr["next_cursor_str"].toString();

        if (fr["errors"].toArray().size()>0) throw std::runtime_error
                (fr["errors"].toArray()[0].toObject()["message"].toString().toStdString());

        frUsr.resize(fr["users"].toArray().size());
        for (size_t i=0; i<frUsr.size(); i++)
        frUsr[i]=fr["users"].toArray()[i].toObject()["screen_name"].toString();
    }
    friendsUrl.erase(friendsUrl.find(usrnm));
    return frUsr;
}

QJsonDocument twitterClient::getUserInfo(std::string& usrnm) {
    if (usrnm=="") throw std::runtime_error("Enter username!");
    if (twitterObj.userGet(usrnm, 0))
        twitterObj.getLastWebResponse(replyMsg);
    else twitterObj.getLastCurlError(replyMsg);

    qReplyInfo = QString::fromStdString(replyMsg);
    QJsonDocument infDocum = QJsonDocument::fromJson(qReplyInfo.toUtf8());
    return infDocum;
}
