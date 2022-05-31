#include "Player.h"
#include "Game.h" //inclusion circular
#include "Texture.h"
Player::Player(Game* g, Texture* t , int x ,int y, int s, int w, int h,bool j) : GameObject(t,x,y){
    ihs = InputHandler::instance();
    speed = s;
    WIDTH = w;
    HEIGHT = h;
    game = g;
    jugadorA = j;
}

void Player::update()
{
    if(jugadorA){
            int Delta_x; int Delta_y;
            int mouse_x, mouse_y;
            rot;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            Delta_x = pos.x - mouse_x;
            Delta_y = pos.y - mouse_y ;
            
            rot = (atan2(Delta_y, Delta_x ) * 180.0000)/ 3.14159265;
            rot-=90;


            if (ihs->keyDownEvent()){
                // MOVIMIENTO------------------------------------------------------
                std::pair<int,int> currentPos = GetPosition();
                bool moverse = false;

            Vector2D velocity{0,0};

            if(ihs->isKeyDown(SDLK_d) ){
                moverse = true;
                velocity = Vector2D(speed,0);
            }
            
            else if(ihs->isKeyDown(SDLK_a) ){
                moverse = true;
                velocity = Vector2D(-speed,0);
            }
            
            if(ihs->isKeyDown(SDLK_s) ){
                moverse = true;
                velocity = Vector2D(0,-speed);
            }
                
            else if(ihs->isKeyDown(SDLK_w) ){
                moverse = true;
                velocity = Vector2D(0,speed);
            }

            velocity = velocity.rotate(rot-180);
            
            if(moverse && currentPos.first + velocity.getX() <= WIDTH &&
            currentPos.first + velocity.getX() >= 0&&
            currentPos.second + velocity.getY() <= HEIGHT &&
            currentPos.second + velocity.getY() >= 0){
        
                move(velocity);
            }

            // DISPARAR----------------------------------------------------------
            if(ihs->isKeyDown(SDLK_SPACE)){
                game->crearBala(currentPos, jugadorA, rot);
            
            }
        }
    }   
}
