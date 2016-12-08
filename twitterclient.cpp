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
}

std::vector<QString> twitterClient::getFollowers(std::string& usrnm) {
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

        folUsr.resize(fol["users"].toArray().size());
        for (size_t i=0; i<folUsr.size(); i++)
            folUsr[i]=fol["users"].toArray()[i].toObject()["screen_name"].toString();
    }
    followersUrl.erase(followersUrl.find(usrnm));
    return folUsr;
}

std::vector<QString> twitterClient::getFriends(std::string& usrnm) {
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

        frUsr.resize(fr["users"].toArray().size());
        for (size_t i=0; i<frUsr.size(); i++)
            frUsr[i]=fr["users"].toArray()[i].toObject()["screen_name"].toString();
    }
    friendsUrl.erase(friendsUrl.find(usrnm));
    return frUsr;
}
