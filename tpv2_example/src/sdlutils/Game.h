#pragma once

#include <list>
#include <SDL.h>

#include "sdlutils_demo.h"
#include "Player.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "macros.h"
#include "SDLUtils.h"
#include "Bala.h"


using namespace std;
const int WIDTH = 800;
const int HEIGHT = 600;
const int SPEED = 30;

class Game{
public:
    Game();
    void start();
    void crearBala(pair<int,int> pos, bool jugador,double rot);

private:
    void update();
    void checkCollision();
protected:
    SDLUtils* sdl = nullptr;
    SDL_Renderer* renderer = nullptr;
    InputHandler* ih = nullptr;
    Player* player = nullptr;
    Player* player2 = nullptr;
    bool exit_ = false;
    list<Bala*> bullets;
    list<Bala*> deadBullets;
};