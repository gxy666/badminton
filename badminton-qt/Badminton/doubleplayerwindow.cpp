#include "doubleplayerwindow.h"
#include "ui_doubleplayerwindow.h"

#define IP "172.21.3.20"
#define PORT 8081
Doubleplayerwindow::Doubleplayerwindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::Doubleplayerwindow)
{
    socket = new QTcpSocket;
}
void Doubleplayerwindow::musicgo()
{
    music->start();
}
void Doubleplayerwindow::closemovie()
{
    ui->waitlabel->hide();
    movie->stop();
    delete movie;
}
Doubleplayerwindow::~Doubleplayerwindow()
{
    delete ui;
    delete music;
}
void Doubleplayerwindow::paintEvent(QPaintEvent *)
{  
    QPainter painter(this);
    this->sizef5();
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap = QPixmap(":/new/prefix1/resource/plbg").scaled(this->size());
    palette.setBrush(this->backgroundRole(), QBrush(pixmap));
    this->setPalette(palette);
    //设置背景图
    if(ifstart)
    {
        if(!(ui->waitlabel->isHidden()))
            ui->waitlabel->hide();
        QFont textfont;
        textfont.setFamily("Microsoft YaHei");
        textfont.setPointSize(textfontsize);
        painter.setFont(textfont);
        painter.drawText(ptext_x,text_y,name);
        painter.drawText(atext_x,text_y,enemyname);
        QFont scorefont;
        scorefont.setPointSize(scorefontsize);
        scorefont.setFamily("Microsoft YaHei");
        painter.setFont(scorefont);
        painter.drawText(pscore_x,score_y,QString::number(playerscore));
        painter.drawText(ascore_x,score_y,QString::number(enemyscore));//比分计分框
        painter.drawPixmap(this->getplayer_x(),this->getpeople_y(),playerwidth,playerheight,player);//player
        painter.drawPixmap(this->getenemy_x(),this->getpeople_y(),playerwidth,playerheight,enemy);//ai
        painter.drawPixmap(this->getball_x(),this->getball_y(),ballwidth,ballheight,ball);//ball
        if(playerspace>0)
        {
            QMatrix matrix;
            matrix.translate(getplayerpat_x()+patwidth,getpat_y()+patheight);
            if(playerspace<=9)
            {
                matrix.rotate(playerspace*5);
                matrix.translate(-getplayerpat_x()-patwidth,-getpat_y()-patheight);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(getplayerpat_x(),getpat_y(),patwidth,patheight,playerpat);
                painter.resetMatrix();
                ++playerspace;
            }
            else
            {
                matrix.rotate((18-playerspace)*5);
                matrix.translate(-getplayerpat_x()-patwidth,-getpat_y()-patheight);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(getplayerpat_x(),getpat_y(),patwidth,patheight,playerpat);
                painter.resetMatrix();
                ++playerspace;
                if(playerspace==18)
                {
                    playerspace = 0;
                }
            }
        }
        else
        {
            painter.drawPixmap(getplayerpat_x(),getpat_y(),patwidth,patheight,playerpat);
        }//旋转球拍效果

        if(enemyspace>0)
        {
            QMatrix matrix;
            matrix.translate(getenemypat_x(),getpat_y()+patheight);
            if(enemyspace<=9)
            {
                matrix.rotate(-enemyspace*5);
                matrix.translate(-getenemypat_x(),-getpat_y()-patheight);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(getenemypat_x(),getpat_y(),patwidth,patheight,enemypat);
                painter.resetMatrix();
                enemyspace++;
            }
            else
            {
                matrix.rotate(-(18-enemyspace)*5);
                matrix.translate(-getenemypat_x(),-getpat_y()-patheight);
                painter.setWorldMatrix(matrix);
                painter.drawPixmap(getenemypat_x(),getpat_y(),patwidth,patheight,enemypat);
                painter.resetMatrix();
                enemyspace++;
                if(enemyspace==18)
                {
                    enemyspace = 0;
                }
            }
        }
        else
        {
            painter.drawPixmap(getenemypat_x(),getpat_y(),patwidth,patheight,enemypat);
        }
        if(playerscore==11)
        {
            painter.drawPixmap(end_x,end_y,end_width,end_height,victory);
            music->changetovictorybgm();
        }
        else if (enemyscore==11)
        {
            painter.drawPixmap(end_x,end_y,end_width,end_height,lose);
            music->changetolosebgm();
        }
    }
    else
    {
        if(playerscore==11)
        {
            painter.drawPixmap(end_x,end_y,end_width,end_height,victory);
            music->changetovictorybgm();
        }
        else if (enemyscore==11)
        {
            painter.drawPixmap(end_x,end_y,end_width,end_height,lose);
            music->changetolosebgm();
        }
        else
        {
            this->ui->waitlabel->setGeometry((this->width()-960)/2,(this->height()-720)/2,960,720);
            this->ui->waitlabel->setMovie(movie);
            movie->start();
        }
    }
}
void Doubleplayerwindow::keyPressEvent(QKeyEvent  *event)
{
    if(ifstart)
    {
        if(event->key()==Qt::Key_A)
        {
            ifgoback = 1;
        }
        else if(event->key()==Qt::Key_D)
        {
            ifgoahead = 1;
        }
        if(event->key()==Qt::Key_Space)
        {
            if(playerspace==0)
                playerspace = 1;
        }
    }
}
void Doubleplayerwindow::setNAMEID(QString name,QString id)
{
    this->name = name;
    this->id = id;
}
void Doubleplayerwindow::setip(QString ip)
{
    this->ip = ip;
    socket->connectToHost(QHostAddress(this->ip),PORT);
    if(socket->waitForConnected(1000))
    {
        ui->setupUi(this);
        connect(socket,SIGNAL(disconnected()),this,SLOT(shutdown()));
        connect(this,SIGNAL(ready()),this,SLOT(closemovie()));
        music = new MusicThread();
        movie = new QMovie(":/new/prefix1/resource/timg.gif");
        setWindowIcon(QIcon(":/new/prefix1/resource/tb.ico"));
        player.load(":/new/prefix1/resource/people1");
        enemy.load(":/new/prefix1/resource/people2");
        ball.load(":/new/prefix1/resource/bmt");
        playerpat.load(":/new/prefix1/resource/pat6");
        enemypat.load(":/new/prefix1/resource/pat12");
        victory.load(":/new/prefix1/resource/victory");
        lose.load(":/new/prefix1/resource/lose");
        //加载图片资源
        this->setFocus();
        playerspace = 0;
        enemyspace = 0;
        this->setFocusPolicy(Qt::StrongFocus);
        connect(socket,SIGNAL(readyRead()),this,SLOT(acceptdata()));
    }
    else
    {
        diesignal = true;
    }
}
void Doubleplayerwindow::sizef5()
{
    playerwidth = this->width()/12;
    playerheight = this->height()/5;
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
void Doubleplayerwindow::sendlogmessage()
{
    QString instruct = "";
    instruct += name;
    instruct += "@@@@";
    instruct += id;
    socket->write(instruct.toUtf8(),instruct.toUtf8().length());
}
void Doubleplayerwindow::acceptdata()
{
    QString a = (QString)socket->readAll();
    qDebug()<<a;
    if(a.compare("full")==0)
    {
        QMessageBox::critical(NULL, "Badminton", "房间已满");
        QThread::sleep(3);
        this->close();
    }
    else if(a.compare("ready")==0)
    {
        socket->write("ready");
        socket->flush();
    }
    else if(a.compare("over")==0)
    {
        ifstart = false;
        socket->disconnectFromHost();
        delete socket;
    }
    else if(a.at(0)==QChar('!'))
    {
        enemyname = a.mid(1);
        emit ready();
        this->musicgo();
        socket->write("0@@@@0@@@@0");
        ifstart = true;
    }
    else
    {
        QString instruct = QString::number(ifgoahead);
        instruct+="@@@@";
        instruct+=QString::number(ifgoback);
        instruct+="@@@@";
        instruct+=QString::number(playerspace);
        socket->write(instruct.toLatin1());
        socket->flush();
        QStringList dolist = a.split("@@@@");
        QString temp0 = dolist.at(0);
        QString temp1 = dolist.at(1);
        QString temp2 = dolist.at(2);
        QString temp3 = dolist.at(3);
        QString temp4 = dolist.at(4);
        QString temp5 = dolist.at(5);
        QString temp6 = dolist.at(6);
        player_x = temp0.toDouble();
        enemy_x = temp1.toDouble();
        ball_x = temp2.toDouble();
        ball_y = temp3.toDouble();
        if(enemyspace == 0)
            if(temp4.toInt()>=1)
                enemyspace = 1;
        playerscore = temp5.toInt();
        enemyscore =  temp6.toInt();
        ifgoahead = 0;
        ifgoback = 0;
    }
}
void Doubleplayerwindow::shutdown()
{
    QMessageBox::critical(NULL, "Badminton", "网络已断开");
    this->close();
}
int Doubleplayerwindow::getball_x()
{
    return (int)(this->width()*ball_x);
}
int Doubleplayerwindow::getball_y()
{
    return (int)(this->height()*ball_y);
}
int Doubleplayerwindow::getplayer_x()
{
    return (int)(this->width()*player_x);
}
int Doubleplayerwindow::getplayerpat_x()
{
    return  (int)((player_x-0.03)*this->width());
}
int Doubleplayerwindow::getenemy_x()
{
    return (int)((0.92-enemy_x)*this->width());
}
int Doubleplayerwindow::getenemypat_x()
{
    return (int)((0.92-enemy_x+0.08)*this->width());
}
int Doubleplayerwindow::getpat_y()
{
    return (int)(this->height()*0.58);
}
int Doubleplayerwindow::getpeople_y()
{
    return (int)(this->height()*0.65);
}
