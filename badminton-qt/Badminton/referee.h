#ifndef REFEREE_H
#define REFEREE_H
#include <QTimer>
#include <QTime>
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QThread>
#include "player.h"
class Referee:public QObject
{
    Q_OBJECT
public:
    Referee(int winwidth,int winheight);
    ~Referee();
    int getaiscore();
    int getplayerscore();
    int getball_x();
    int getball_y();
    bool ifergo();
    bool ifungo();
    bool aiget();
    bool over();
    bool aiturn();
    Player leftone;
    Player rightone;
    void refresh(int w,int h,int ifspace,int aispace);
private:
    QTimer *balltimer;
    int currentstate = 0;
    int playerscore = 0;
    int aiscore = 0;
    int ball_x;
    int ball_y;
    int winwidth;
    int winheight;
    double v_ball_x = 0;
    double v_ball_y = 0;
    bool ifserve = false;
    bool iftoai = true;
    bool ifcollisiontoceiling = false;
    bool ifcollisiontonet = false;
    bool ifcollisiontowall = false;
    void collisiontoceiling();
    void collisiontowall();
    void collisiontonet();
    void collisiontofloor();
    void collisiontopat(bool ifplayerbeat,int ifspace,int aispace);
    void playergetscore();
    void aigetscore();

private slots:
    void ballmove();
signals:
    void beat();
};

#endif // REFEREE_H
