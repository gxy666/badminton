#include "musicthread.h"

MusicThread::MusicThread()
{
    victorybgm = new QMediaPlayer(this);
    losebgm = new QMediaPlayer(this);
    victorybgm->setMedia(QUrl("qrc:\\new\\prefix1\\resource\\victor.wav"));
    victorybgm->setVolume(50);
    losebgm->setMedia(QUrl("qrc:\\new\\prefix1\\resource\\lose.wav"));
    losebgm->setVolume(50);
    normalbgm = new QMediaPlayer();
    list = new QMediaPlaylist;
    list->addMedia(QUrl("qrc:\\new\\prefix1\\resource\\Base.wav"));
    list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    normalbgm->setPlaylist(list);
    normalbgm->setVolume(50);
}
void MusicThread::run()
{
    normalbgm->play();
}
MusicThread::~MusicThread()
{
    delete normalbgm;
    delete victorybgm;
    delete losebgm;
}
void MusicThread::changetovictorybgm()
{
    if(normalbgm->state()==1)
    normalbgm->stop();
    if(losebgm->state()==1)
    losebgm->stop();
    if(victorybgm->state()==0)
    victorybgm->play();
}
void MusicThread ::changetonormalbgm()
{
    if(losebgm->state()==1)
    losebgm->stop();
    if(victorybgm->state()==1)
    victorybgm->stop();
    if(normalbgm->state()==0)
    normalbgm->play();
}
void MusicThread::changetolosebgm()
{
    if(normalbgm->state()==1)
    normalbgm->stop();
    if(victorybgm->state()==1)
    victorybgm->stop();
    if(losebgm->state()==0)
    losebgm->play();
}
