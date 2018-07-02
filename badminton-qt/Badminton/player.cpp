#include "player.h"

Player::Player(int windowwidth,double x,bool ifleft)
{
    this->ifleftone = ifleft;
    this->windowwidth = windowwidth;
    this->posite = x;
}
Player::Player()
{

}
Player::position()
{
   if(this->ifleftone)
    return this->posite*this->windowwidth;
   else
       return (0.92-this->posite)*this->windowwidth;
}
void Player::goahead()
{
    if(ifserve)
    {
        if(posite<0.425)
            this->posite+=0.01;
    }
    else
    {
        if(posite<0.255)
            this->posite+=0.01;
    }
}
void Player::goback()
{
    if(posite>0.081)
    this->posite-=0.01;
}
void Player::refresh(int windowwidth)
{
    this->windowwidth = windowwidth;
}
int Player::patposition()
{
    if(this->ifleftone)
        return (this->posite-0.03)*this->windowwidth;
    else
        return (0.92-this->posite+0.08)*this->windowwidth;
}
void Player::free()
{
    this->ifserve=true;
}
void Player::disfree()
{
    this->ifserve = false;
    this->posite = 0.255;
}
