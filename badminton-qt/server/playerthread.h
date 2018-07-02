#ifndef PLAYERTHREAD_H
#define PLAYERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class PlayerThread:public QObject
{
    Q_OBJECT
public:
    PlayerThread(QObject *parent,bool ifp1,QTcpSocket* socket,QString name,QString h);
    QString name;
    int space = 0;
    int move = 0;
    double enemyx = 0.255;
    double x = 0.255;
    int score = 0;
    bool p1;
    QTcpSocket* socket = nullptr;
    void ready();
    void setenemyname(QString);
    void setballposition(double x,double y,double p2x,int enemyspace);
    void over();
    double ball_x;
    double ball_y;
    int enemyspace = 0;
    int enemyscore = 0;
private:
    QString enemyname;
    QString parenthouse;
    ~PlayerThread();
signals:
    void sendmessage();
    void finished();
    void ok();
private slots:
    void acceptdata();
    void deletethis();

};

#endif // PLAYERTHREAD_H
