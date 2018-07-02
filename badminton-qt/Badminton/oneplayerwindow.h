#ifndef ONEPLAYERWINDOW_H
#define ONEPLAYERWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "musicthread.h"
#include "referee.h"
namespace Ui {
class OnePlayerWindow;
}

class OnePlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OnePlayerWindow(QWidget *parent = 0);
    Ui::OnePlayerWindow *ui;
    ~OnePlayerWindow();
private:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void sizef5();
    Referee *server;
    MusicThread *music;
    QPixmap player;
    QPixmap ai;
    QPixmap playerpat;
    QPixmap aipat;
    QPixmap ball;
    QPixmap victory;
    QPixmap lose;
    QTimer *aitimer;
    int playerwidth = this->width()/12;
    int playerheight = this->height()/5;
    int phposition = this->height()*0.65;
    int ballwidth = this->width()/40;
    int ballheight = this->height()/30;
    int patheposition = this->height()*0.58;
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
    int ifspace;
    int aispace;
private slots:
    void aimove();
};

#endif // ONEPLAYERWINDOW_H
