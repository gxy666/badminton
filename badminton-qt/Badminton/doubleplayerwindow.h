#ifndef DOUBLEPLAYERWINDOW_H
#define DOUBLEPLAYERWINDOW_H

#include <QMainWindow>
#include "musicthread.h"
#include "QMessageBox"
#include <QPixmap>
#include <QMovie>
#include <QHostAddress>
#include <QTcpSocket>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QPainter>
namespace Ui
{
    class Doubleplayerwindow;
}

class Doubleplayerwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Doubleplayerwindow(QWidget *parent = 0);
    ~Doubleplayerwindow();
    bool diesignal = false;
    void setNAMEID(QString name,QString id);
    void setip(QString ip);
    void musicgo();
    void sendlogmessage();
signals:
    void ready();
private:
    Ui::Doubleplayerwindow *ui;
    MusicThread *music;
    QString name;
    QString enemyname;
    QString id;
    QString ip;
    QPixmap player;
    QPixmap enemy;
    QPixmap playerpat;
    QPixmap enemypat;
    QPixmap ball;
    QPixmap victory;
    QPixmap lose;
    QMovie *movie;
    QTcpSocket *socket;
    bool ifstart = false;
    int ifgoahead = 0;
    int ifgoback = 0;
    int playerwidth = this->width()/12;
    int playerheight = this->height()/5;
    int ballwidth = this->width()/40;
    int ballheight = this->height()/30;
    int patwidth = this->width()/30;
    int patheight = this->height()/10;
    int ptext_x = this->width()*0.34;
    int text_y = this->height()*0.31;
    int atext_x = this->width()*0.56;
    int pscore_x = this->width()*0.35;
    int ascore_x = this->width()*0.60;
    int score_y = this->height()*0.40;
    int textfontsize = (this->width()+1000)/100;
    int scorefontsize = (this->width()+1000)/60;
    int end_x = this->width()*0.2;
    int end_width = this->width()*0.6;
    int end_y = this->height()*0.25;
    int end_height = this->height()*0.5;
    int playerspace;
    int enemyspace;
    int playerscore = 0;
    int enemyscore = 0;
    double player_x = -1;
    double enemy_x = -1;
    double ball_x = -1;
    double ball_y = -1;
    int getball_x();
    int getball_y();
    int getplayer_x();
    int getplayerpat_x();
    int getenemy_x();
    int getenemypat_x();
    int getpat_y();
    int getpeople_y();
    void sizef5();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent  *event);
private slots:
    void closemovie();
    void acceptdata();
    void shutdown();
};

#endif // DOUBLEPLAYERWINDOW_H
