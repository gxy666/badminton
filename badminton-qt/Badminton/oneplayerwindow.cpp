#include "oneplayerwindow.h"
#include "ui_oneplayerwindow.h"
#include <iostream>
OnePlayerWindow::OnePlayerWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::OnePlayerWindow)
{
    ui->setupUi(this);
    aitimer = new QTimer(this);
    connect(aitimer,SIGNAL(timeout()),this,SLOT(aimove()));
    server = new Referee(this->width(),this->height());
    music = new MusicThread();
    setWindowIcon(QIcon(":/new/prefix1/resource/tb.ico"));
    player.load(":/new/prefix1/resource/people1");
    ai.load(":/new/prefix1/resource/people2");
    ball.load(":/new/prefix1/resource/bmt");
    playerpat.load(":/new/prefix1/resource/pat6");
    aipat.load(":/new/prefix1/resource/pat12");
    victory.load(":/new/prefix1/resource/victory");
    lose.load(":/new/prefix1/resource/lose");
    this->setFocus();    
    music->start();
    ifspace = 0;
    aispace = 0;
    this->setFocusPolicy(Qt::StrongFocus);
}
OnePlayerWindow::~OnePlayerWindow()
{
    delete ui;
    delete aitimer;
    delete music;
}
void OnePlayerWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap = QPixmap(":/new/prefix1/resource/plbg").scaled(this->size());
    palette.setBrush(this->backgroundRole(), QBrush(pixmap));
    this->setPalette(palette);
    //设置背景图

    QFont textfont;
    textfont.setFamily("Microsoft YaHei");
    textfont.setPointSize(textfontsize);
    painter.setFont(textfont);
    painter.drawText(ptext_x,text_y,"Player");
    painter.drawText(atext_x,text_y,"SuperDan");
    QFont scorefont;
    scorefont.setPointSize(scorefontsize);
    scorefont.setFamily("Microsoft YaHei");
    painter.setFont(scorefont);
    painter.drawText(pscore_x,score_y,QString::number(server->getplayerscore()));
    painter.drawText(ascore_x,score_y,QString::number(server->getaiscore()));//比分计分框

    if(!server->over())//如果对局未结束
    {
        if(aitimer->isActive()&&server->ifungo())
            aitimer->stop();
        if(!aitimer->isActive()&&server->ifergo())
            aitimer->start(19);
        if(server->aiget())
            aispace = 1;//ai发球
        this->sizef5();//数据刷新防止屏幕变形
        server->refresh(this->width(),this->height(),ifspace,aispace);//对内部数据进行刷新
        painter.drawPixmap(server->leftone.position(),phposition,playerwidth,playerheight,player);//player
        painter.drawPixmap(server->rightone.position(),phposition,playerwidth,playerheight,ai);//ai
        painter.drawPixmap(server->getball_x(),server->getball_y(),ballwidth,ballheight,ball);//ball
        if(ifspace>0)
        {
            QMatrix matrix;
            matrix.translate(server->leftone.patposition()+patwidth,phposition+patheight/3);
            if(ifspace<=9)
            {
                matrix.rotate(ifspace*5);
                matrix.translate(-server->leftone.patposition()-patwidth,-phposition-patheight/3);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(server->leftone.patposition(),patheposition,patwidth,patheight,playerpat);
                painter.resetMatrix();
                ++ifspace;
            }
            else
            {
                matrix.rotate((18-ifspace)*5);
                matrix.translate(-server->leftone.patposition()-patwidth,-phposition-patheight/3);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(server->leftone.patposition(),patheposition,patwidth,patheight,playerpat);
                painter.resetMatrix();
                ++ifspace;
                if(ifspace==18)
                {
                    ifspace = 0;
                }
            }
        }
        else
        {
            painter.drawPixmap(server->leftone.patposition(),patheposition,patwidth,patheight,playerpat);
        }//旋转球拍效果

        if(aispace>0)
        {
            QMatrix matrix;
            matrix.translate(server->rightone.patposition(),phposition+patheight/3);
            if(aispace<=15)
            {
                matrix.rotate(-aispace*3);
                matrix.translate(-server->rightone.patposition(),-phposition-patheight/3);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(server->rightone.patposition(),patheposition,patwidth,patheight,aipat);
                painter.resetMatrix();
                ++aispace;
            }
            else
            {
                matrix.rotate(-(30-aispace)*3);
                matrix.translate(-server->rightone.patposition(),-phposition-patheight/3);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(server->rightone.patposition(),patheposition,patwidth,patheight,aipat);
                painter.resetMatrix();
                ++aispace;
                if(aispace==30)
                {
                    aispace = 0;
                }
            }
        }
        else
        {
            painter.drawPixmap(server->rightone.patposition(),patheposition,patwidth,patheight,aipat);
        }
    }//同上旋转球拍效果
    else
    {
        if(server->getplayerscore()==11)
        {
            painter.drawPixmap(end_x,end_y,end_width,end_height,victory);
            music->changetovictorybgm();
        }
        else if (server->getaiscore()==11)
        {
            painter.drawPixmap(end_x,end_y,end_width,end_height,lose);
            music->changetolosebgm();
        }//对局结束
    }

}
void OnePlayerWindow::keyPressEvent(QKeyEvent  *event)
{
    if(event->key()==Qt::Key_A)
    {
        server->leftone.goback();
    }
    if(event->key()==Qt::Key_D)
    {
        server->leftone.goahead();
    }
    if(event->key()==Qt::Key_Space)
    {
        if(ifspace==0)
        ifspace = 1;
    }
}
void OnePlayerWindow::sizef5()
{
    playerwidth = this->width()/12;
    playerheight = this->height()/5;
    phposition = this->height()*0.65;
    patheposition = this->height()*0.58;
    ballwidth = this->width()/40;
    ballheight = this->height()/30;
    patwidth = this->width()/30;
    patheight = this->height()/10;
    textfontsize = (this->width()+1000)/100;
    scorefontsize = (this->width()+1000)/60;
    ptext_x = this->width()*0.34;
    text_y = this->height()*0.31;
    atext_x = this->width()*0.56;
    pscore_x = this->width()*0.35;
    ascore_x = this->width()*0.60;
    score_y = this->height()*0.40;
    end_x = this->width()*0.2;
    end_width = this->width()*0.6;
    end_y = this->height()*0.25;
    end_height = this->height()*0.5;
}
void OnePlayerWindow::aimove()
{
    if(server->getball_x()-(this->width()*0.059)>server->rightone.position())
    {
        server->rightone.goback();
        if(server->getball_y()>=this->height()*0.58&&server->getball_y()<=this->height()*0.59)
        {
            if(aispace == 0&&server->aiturn())
            aispace = 1;
        }
    }
    else
    {
        server->rightone.goahead();
        if(server->getball_y()>=this->height()*0.58&&server->getball_y()<=this->height()*0.59)
        {
            if(aispace == 0&&server->aiturn())
            aispace = 1;
        }
    }
}

