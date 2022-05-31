#include "Bala.h"

Bala::Bala(Texture* t , int x ,int y, int s, int w, int h,double r) : GameObject(t,x,y,r){
    //ihs = InputHandler::instance();
    speed = s;
    WIDTH = w;
    HEIGHT = h;
    velocity = Vector2D(0,speed);
    velocity = velocity.rotate(r-180);
    std::cout << "a\n";
}

void Bala::update()
{
    std::pair<int,int> currentPos = GetPosition();
    move(velocity);
    
}