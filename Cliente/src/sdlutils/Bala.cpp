#include "Bala.h"

Bala::Bala(Texture* t , int x ,int y, int s, int w, int h,float r) : GameObject(t,x,y,r){
    speed = s;
    WIDTH = w;
    HEIGHT = h;
    velocity = Vector2D(0,speed);
    velocity = velocity.rotate(r-180);
}

void Bala::update() {
    std::pair<int,int> currentPos = GetPosition();
    move(velocity);    
}
