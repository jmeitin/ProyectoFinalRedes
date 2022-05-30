
#include "Player.h"

Player::Player(Texture* t , int x ,int y) : GameObject(t,x,y){
ihs = InputHandler::instance();

}

void Player::update()
{
    if (ihs->keyDownEvent()){
        if(ihs->isKeyDown(SDLK_RIGHT))
        move(1,0);
    }
}