#include "playerthread.h"

PlayerThread::PlayerThread(QObject *parent,bool ifp1,QTcpSocket* socket,QString name,QString h)
{
    this->parenthouse = h;
    this->socket = socket;
    this->name = name;
    this->p1 = ifp1;
    connect(socket,SIGNAL(disconnected()),this,SLOT(deletethis()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(acceptdata()));
}
void PlayerThread::ready()
{
    socket->write("ready");
    socket->flush();
}
void PlayerThread::acceptdata()
{
    QString instruct = (QString)socket->readAll();
    qDebug()<<"house: "<<parenthouse<<name<<' '<<instruct;
    if(instruct.compare("ready")==0)
    {
        QString send = "!";
        send+=enemyname;
        qDebug()<<"send to house: "<<parenthouse<<name<<' '<<send;
        socket->write(send.toUtf8(),send.toUtf8().length());
        socket->flush();
        QThread::msleep(1);
        emit ok();
    }
    else
    {
        QStringList dolist = instruct.split("@@@@");
        QString temp0 = dolist.at(0);
        QString temp1 = dolist.at(1);
        QString temp2 = dolist.at(2);
        if(temp0.toInt()==1)
        {
            if(move==0)
                move++;
        }
        else if(temp1.toInt()==1)
        {
            if(move==0)
                move--;
        }
        space = temp2.toInt();
        emit sendmessage();
    }
}
void PlayerThread::deletethis()
{
    qDebug()<<"house: "<<parenthouse<<name<<" is deleted";
    socket->disconnectFromHost();
    socket->deleteLater();
    emit finished();
}
void PlayerThread::setenemyname(QString e)
{
    this->enemyname = e;
}
void PlayerThread::over()
{
    socket->write("over");
    socket->flush();
}
void PlayerThread::setballposition(double x, double y, double p2x, int enemyspace)
{
    this->ball_x = x;
    this->ball_y = y;
    this->enemyx = p2x;
    this->enemyspace = enemyspace;
}
PlayerThread::~PlayerThread()
{
    emit over();
}
