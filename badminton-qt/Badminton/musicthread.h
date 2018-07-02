#ifndef MUSICTHREAD_H
#define MUSICTHREAD_H
#include <QThread>
#include <QMediaPlayer>
#include <QMediaPlaylist>
class MusicThread : public QThread
{
public:
    MusicThread();
    void run();
    ~MusicThread();
    void changetovictorybgm();
    void changetolosebgm();
    void changetonormalbgm();
private:
    QMediaPlayer *normalbgm;
    QMediaPlayer *victorybgm;
    QMediaPlayer *losebgm;
    QMediaPlaylist *list;
};

#endif // MUSICTHREAD_H
