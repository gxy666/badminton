#ifndef DEALHOUSE_H
#define DEALHOUSE_H
#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include "playerthread.h"

class DealHouse : public QThread
{
    Q_OBJECT
public:
    DealHouse(QString id,QTcpSocket*,QString p1,QObject *parent);
    QString id;
    void setsocket2(QTcpSocket*,QString p2);
    bool lock = false;
private:
    PlayerThread *p1;
    PlayerThread *p2;
    QTimer *balltimer;
    bool ifcollisiontoceiling = false;
    bool ifcollisiontonet = false;
    bool ifcollisiontowall = false;
    void collisiontoceiling();
    void collisiontowall();
    void collisiontonet();
    void collisiontofloor();
    void collisiontopat(bool ifp1beat,int ifspace,int aispace);
    bool ifp1ok = false;
    bool ifp2ok = false;
    bool ifserve = false;
    bool iftop2 = true;
    double v_ball_x = 0;
    double v_ball_y = 0;
    void run();
private:
    double ball_x;
    double ball_y;

signals:
    void over();
    void timerstart();
    void timerstop();
private slots:
    void p1sendmessage();
    void p2sendmessage();
    void ballmove();
    void overed();
    void p1ok();
    void p2ok();
    void starttimer();
    void stoptimer();
};

#endif // DEALHOUSE_H
