#include "dealhouse.h"

DealHouse::DealHouse(QString id,QTcpSocket *a,QString p1name,QObject *parent)
{
    this->id = id;
    this->p1 = new PlayerThread(this,true,a,p1name,id);
}
void DealHouse::setsocket2(QTcpSocket *a,QString p2name)
{
    if(!lock)
    {
        p2 = new PlayerThread(this,false,a,p2name,id);
        p1->setenemyname(p2name);
        p2->setenemyname(p1->name);
        balltimer = new QTimer(this);
        connect(p1,SIGNAL(sendmessage()),this,SLOT(p1sendmessage()));
        connect(p2,SIGNAL(sendmessage()),this,SLOT(p2sendmessage()));
        connect(this,SIGNAL(timerstart()),this,SLOT(starttimer()));
        connect(this,SIGNAL(timerstop()),this,SLOT(stoptimer()));
        connect(balltimer,SIGNAL(timeout()),this,SLOT(ballmove()));
        connect(p1,SIGNAL(ok()),this,SLOT(p1ok()));
        connect(p2,SIGNAL(ok()),this,SLOT(p2ok()));
        p1->ready();
        p2->ready();
    }
}
void DealHouse::run()
{
    int a = 0;
    while (!ifp1ok||!ifp2ok)
    {
        a++;
    }
    qDebug()<<"start";
    while (ifp1ok&&ifp2ok)
    {
        int opspace = p1->space;
        int tpspace = p2->space;
        if(!ifserve)
        {
            if(!iftop2)
            {
                if(p1->move==1&&p1->x<0.425)
                {
                    p1->x+=0.01;
                }
                if(p1->move==-1&&p1->x>0.081)
                {
                    p1->x-=0.01;
                }
                if(p2->move==1&&p2->x<0.255)
                {
                    p2->x+=0.01;
                }
                if(p2->move==-1&&p2->x>0.081)
                {
                    p2->x-=0.01;
                }
                p1->move = 0;
                p2->move = 0;
                ball_x = 1-p2->x;
                ball_y = 0.585;
                if(p2->space>=1)
                {
                    v_ball_x = -0.0054;
                    v_ball_y = -0.0060;
                    emit timerstart();
                    ifserve = true;
                }
            }
            else
            {
                if(p2->move==1&&p2->x<0.425)
                {
                    p2->x+=0.01;
                }
                if(p2->move==-1&&p2->x>0.081)
                {
                    p2->x-=0.01;
                }
                if(p1->move==1&&p1->x<0.255)
                {
                    p1->x+=0.01;
                }
                if(p1->move==-1&&p1->x>0.081)
                {
                    p1->x-=0.01;
                }
                p1->move = 0;
                p2->move = 0;
                ball_x = p1->x-0.02;
                ball_y = 0.585;
                if(p1->space>=1)
                {
                    v_ball_x = 0.0054;
                    v_ball_y = -0.0060;
                    emit timerstart();
                    ifserve = true;
                }
            }
        }
        else
        {
            if(p2->move==1&&p2->x<0.425)
            {
                p2->x+=0.01;
            }
            if(p2->move==-1&&p2->x>0.081)
            {
                p2->x-=0.01;
            }
            p2->move = 0;
            if(p1->move==1&&p1->x<0.425)
            {
                p1->x+=0.01;
            }
            if(p1->move==-1&&p1->x>0.081)
            {
                p1->x-=0.01;
            }
            p1->move = 0;
            if(ball_y<0.19)
            {
                this->collisiontoceiling();
            }
            if(ball_x<0.03||ball_x>0.95)
            {
                this->collisiontowall();
            }
            if(ball_x>0.49&&ball_x<0.51&&ball_y>0.7)
            {
                this->collisiontonet();
            }
            if(ball_y>0.82)
            {
                this->collisiontofloor();
            }
            if(ball_y>=0.52&&ball_y<=0.63)
            {
                if((ball_x>(p1->x-0.065))&&(ball_x<(p1->x+0.01)))
                {
                    this->collisiontopat(true,opspace,tpspace);
                }
                else if(ball_x>((0.92-p2->x)-0.01)&&(ball_x<((0.92-p2->x)+0.065)))
                {
                    this->collisiontopat(false,opspace,tpspace);
                }
            }
        }
        p1->setballposition(ball_x,ball_y,p2->x,p2->space);
        p2->setballposition(0.975-ball_x,ball_y,p1->x,p1->space);
        if(p1->score==11||p2->score==11)
        {
            ifp1ok = false;
            ifp2ok = false;
        }
    }
}
void DealHouse::collisiontoceiling()
{
    if(!ifcollisiontoceiling)
    {
        v_ball_y = -v_ball_y;
    }
    ifcollisiontoceiling = true;
}
void DealHouse::collisiontowall()
{
    if(!ifcollisiontowall)
    {
        v_ball_x = -0.7*v_ball_x;
    }
    ifcollisiontowall = true;
}
void DealHouse::collisiontonet()
{

    if(!ifcollisiontonet)
    {
        v_ball_x = -v_ball_x;
    }
    ifcollisiontonet = true;
}
void DealHouse::collisiontofloor()
{
    ifcollisiontoceiling = false;
    ifcollisiontonet = false;
    ifcollisiontowall = false;
    v_ball_x = 0;
    v_ball_y = 0;
    emit timerstop();
    if(ball_x >=0.5 )
    {
        p1->score++;
        p2->enemyscore++;
        iftop2 = true;
        ifserve = false;
    }
    else
    {
        p2->score++;
        p1->enemyscore++;
        iftop2 = false;
        ifserve = false;
        p1->x = 0.255;
        p2->x = 0.255;
    }

}
void DealHouse::collisiontopat(bool ifp1beat,int p1space,int p2space)
{
    ifcollisiontoceiling = false;
    ifcollisiontowall = false;
    ifcollisiontonet = false;
    if(ifp1beat)
    {
        if(p1space!=0)
        {
            v_ball_y = -0.0063+((double)p1space)/100000/5;
            v_ball_x = 0.0051+((double)p1space)/100000/5;
            iftop2 = true;
        }
    }
    else
    {
        if(p2space!=0)
        {
            v_ball_y = -0.0063+((double)p2space)/100000/5;
            v_ball_x = -0.0051-((double)p2space)/100000/5;
            iftop2 = false;
        }
    }
}
void DealHouse::ballmove()
{
    ball_x+=(v_ball_x);
    ball_y+=(v_ball_y);
    v_ball_y+=0.00012;
}
void DealHouse::overed()
{
    p1->over();
    p2->over();
}
void DealHouse::p1ok()
{
    ifp1ok = true;
}
void DealHouse::p2ok()
{
    ifp2ok = true;
    this->start();
}
void DealHouse::starttimer()
{
    balltimer->start(9);
}
void DealHouse::stoptimer()
{
    balltimer->stop();
}
void DealHouse::p1sendmessage()
{
    QString send = QString::number(p1->x,'f');
    send += "@@@@";
    send += QString::number(p1->enemyx,'f');
    send += "@@@@";
    send += QString::number(p1->ball_x,'f');
    send += "@@@@";
    send += QString::number(p1->ball_y,'f');
    send += "@@@@";
    send += QString::number(p2->space);
    send += "@@@@";
    send += QString::number(p1->score);
    send += "@@@@";
    send += QString::number(p1->enemyscore);
    qDebug()<<"send to house: "<<id<<p1->name<<' '<<send;
    p1->socket->write(send.toLatin1());
    p1->socket->flush();
    p2->space = 0;
}
void DealHouse::p2sendmessage()
{
    QString send = QString::number(p2->x,'f');
    send += "@@@@";
    send += QString::number(p2->enemyx,'f');
    send += "@@@@";
    send += QString::number(p2->ball_x,'f');
    send += "@@@@";
    send += QString::number(p2->ball_y,'f');
    send += "@@@@";
    send += QString::number(p1->space);
    send += "@@@@";
    send += QString::number(p2->score);
    send += "@@@@";
    send += QString::number(p2->enemyscore);
    qDebug()<<"send to house: "<<id<<p2->name<<' '<<send;
    p2->socket->write(send.toLatin1());
    p2->socket->flush();
    p1->space = 0;
}
