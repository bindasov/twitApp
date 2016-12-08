#ifndef FOLLOWERSINTERSECTION_H
#define FOLLOWERSINTERSECTION_H

#include "twitterclient.h"

namespace Ui {
class followersIntersection;
}

class followersIntersection : public QDialog, private twitterClient
{
    Q_OBJECT

public:
    explicit followersIntersection(QWidget *parent = 0);
    void getSharedFollowers();
    void getSharedFriends();
    ~followersIntersection();

private slots:
    void on_pushButton_clicked();

private:
    Ui::followersIntersection *ui;
};

#endif // FOLLOWERSINTERSECTION_H
