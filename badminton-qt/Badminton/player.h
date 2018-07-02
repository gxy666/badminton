#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player(int windowwidth,double x,bool ifleft);
    Player();
    int position();
    int patposition();
    void goahead();
    void goback();
    void refresh(int windowwidth);
    void free();
    void disfree();
private:
    bool ifleftone;
    bool ifserve;
    int windowwidth;
    double posite;


};

#endif // PLAYER_H
