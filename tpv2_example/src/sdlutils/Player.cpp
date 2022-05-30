
#include "Player.h"

Player::Player(Texture* t , int x ,int y, int s, int w, int h) : GameObject(t,x,y){
    ihs = InputHandler::instance();
    speed = s;
    WIDTH = w;
    HEIGHT = h;
}

void Player::update()
{
    if (ihs->keyDownEvent()){
        // MOVIMIENTO------------------------------------------------------
        std::pair<int,int> currentPos = GetPosition();

        if(ihs->isKeyDown(SDLK_RIGHT) && currentPos.first + speed <= WIDTH)
            move(speed,0);
        else if(ihs->isKeyDown(SDLK_LEFT) && currentPos.first - speed >= 0)
            move(-speed,0);
        else if(ihs->isKeyDown(SDLK_UP) && currentPos.second + speed <= HEIGHT)
            move(0, speed);
        else if(ihs->isKeyDown(SDLK_DOWN) && currentPos.second - speed >= 0)
            move(0, -speed);
        else if(ihs->isKeyDown(SDLK_SPACE)){
            
            Bala* b = new Bala(&sdl.images().at("sdl_logo"), currentPos.first, currentPos.second, speed*3, WIDTH, HEIGHT)

        }
        
        // DISPARAR----------------------------------------------------------

    }
}