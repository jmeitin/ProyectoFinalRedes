#include "Bala.h"

Bala::Bala(Texture* t , int x ,int y, int s, int w, int h) : GameObject(t,x,y){
    //ihs = InputHandler::instance();
    speed = s;
    WIDTH = w;
    HEIGHT = h;
}

void Bala::update()
{
    std::pair<int,int> currentPos = GetPosition();
    move(speed, 0);
    
}