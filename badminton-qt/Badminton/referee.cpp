#include "referee.h"

Referee::Referee(int winwidth,int winheight)
{
    this->winwidth = winwidth;
    this->winheight = winheight;
    balltimer = new QTimer(this);
    connect(balltimer,SIGNAL(timeout()),this,SLOT(ballmove()));
    leftone = Player(winwidth,0.255,true);//0.255是发球线位置
    rightone = Player(winwidth,0.255,false);
}
void Referee::ballmove()
{
    ball_x+=(v_ball_x*winwidth);
    ball_y+=(v_ball_y*winheight);
    v_ball_y+=0.00012;
}
Referee::~Referee()
{
    delete balltimer;
}
Referee::getaiscore()
{
    return aiscore;
}
Referee::getplayerscore()
{
    return playerscore;
}
Referee::getball_x()
{
    return ball_x;
}
Referee::getball_y()
{
    return ball_y;
}
void Referee::refresh(int w,int h,int ifspace,int aispace)
{
    if(!this->over())
    {
        if(!ifserve)
        {
            if(!iftoai)
            {
                ball_x = rightone.position()+0.08*winwidth;
                ball_y = winheight*0.585;
                if(aispace==1)
                {
                    v_ball_x = -0.0054;
                    v_ball_y = -0.0060;
                    balltimer->start(10);
                    ifserve = true;
                    leftone.free();
                    rightone.free();
                }
            }
            else
            {
                ball_x = leftone.position()-0.02*winwidth;
                ball_y = winheight*0.585;
                if(ifspace==1)
                {
                    v_ball_x = 0.0054;
                    v_ball_y = -0.0060;
                    balltimer->start(9);
                    ifserve = true;
                    leftone.free();
                    rightone.free();
                }
            }
        }
        else
        {
            if(ball_y<winheight*0.19)
            {
                this->collisiontoceiling();
            }
            if(ball_x<winwidth*0.03||ball_x>winwidth*0.95)
            {
                this->collisiontowall();
            }
            if(ball_x>winwidth*0.49&&ball_x<winwidth*0.51&&ball_y>winheight*0.7)
            {
                this->collisiontonet();
            }
            if(ball_y>winheight*0.82)
            {
                this->collisiontofloor();
            }
            if(ball_y>=winheight*0.57&&ball_y<=winheight*0.60)
            {
                if((ball_x>(rightone.position()+0.065*winwidth))&&(ball_x<(rightone.position()+0.095*winwidth)))
                {
                    this->collisiontopat(false,ifspace,aispace);
                }
            }
            if(ball_y>=winheight*0.52&&ball_y<=winheight*0.63)
            {
                if((ball_x>(leftone.position()-0.04*winwidth))&&(ball_x<(leftone.position()+0.01*winwidth)))
                {
                    this->collisiontopat(true,ifspace,aispace);
                }
            }
        }
        ball_x = ball_x*w/winwidth;
        ball_y = ball_y*h/winheight;
        leftone.refresh(w);
        rightone.refresh(w);
        this->winwidth = w;
        this->winheight = h;
    }
}
void Referee::collisiontoceiling()
{
    if(!ifcollisiontoceiling)
    {
        v_ball_y = -v_ball_y;
    }
    ifcollisiontoceiling = true;
}
void Referee::collisiontowall()
{
    if(!ifcollisiontowall)
    {
        v_ball_x = -0.7*v_ball_x;
    }
    ifcollisiontowall = true;
}
void Referee::collisiontonet()
{

    if(!ifcollisiontonet)
    {
        v_ball_x = -v_ball_x;
    }
    ifcollisiontonet = true;
}
void Referee::collisiontofloor()
{
    QThread::sleep(1);
    ifcollisiontoceiling = false;
    ifcollisiontonet = false;
    ifcollisiontowall = false;
    v_ball_x = 0;
    v_ball_y = 0;
    balltimer->stop();
    if(ball_x >=winwidth*0.5 )
    {
        this->playergetscore();
    }
    else
    {
        this->aigetscore();
    }

}
void Referee::collisiontopat(bool ifplayerbeat,int ifspace,int aispace)
{
    ifcollisiontoceiling = false;
    ifcollisiontowall = false;
    ifcollisiontonet = false;
    if(ifplayerbeat)
    {
        if(ifspace!=0)
        {
            v_ball_y = -0.0063+((double)ifspace)/100000/5;
            v_ball_x = 0.0051+((double)ifspace)/100000/5;
            iftoai = true;
        }
    }
    else
    {
        if(aispace!=0)
        {
            v_ball_y = -0.0063+((double)aispace)/100000/5;
            v_ball_x = -0.0051-((double)aispace)/100000/5;
            iftoai = false;
        }
    }
}
void Referee::playergetscore()
{
    playerscore++;
    iftoai = true;
    ifserve = false;
    leftone.disfree();
    rightone.disfree();
}
void Referee::aigetscore()
{
    aiscore++;
    iftoai = false;
    ifserve = false;
    leftone.disfree();
    rightone.disfree();
}
bool Referee::ifergo()
{
    if(!ifserve&&iftoai)
       return false;
    else
        return true;
}
bool Referee::aiget()
{
    if(!ifserve&&!iftoai)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Referee::ifungo()
{
    return !ifserve;
}
bool Referee::over()
{
    if(aiscore>=11||playerscore>=11)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Referee::aiturn()
{
    return iftoai;
}
