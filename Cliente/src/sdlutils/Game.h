#ifndef CLIENT_H_
#define CLIENT_H_

#include <list>
#include <SDL.h>


#include "Player.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "macros.h"
#include "SDLUtils.h"
#include "Bala.h"
#include "../network/Socket.h"
#include <string>

#include "../network/Message.h"
using namespace std;
const int WIDTH = 800;
const int HEIGHT = 600;
const int SPEED = 10;

//enum host_t { p1 = 0, p2 = 1};  




class Client{
public:
    Client(const char* ip, const char* port, const char * n);
    ~Client();
    void login();
    void startGame();
    void logout();
    void net_thread();
    void game_thread();
    void crearBala(pair<int,int> pos,float rot);
    void crearBalaEnemiga(pair<int,int> pos, float rot);
    float getSDLcurrTime();
private:  
    void checkCollision();
    void freeDeadBullets();
    void updateAllBullets();
    std::pair<int,int> posiciones[2] = {{WIDTH/27, HEIGHT/2},{WIDTH-WIDTH/8, HEIGHT/2}};
protected:

    Socket socket;
    Message::host_t MyPlayerID ;
    std::string nick ="";
    bool playing = false;

    SDLUtils* sdl = nullptr;
    SDL_Renderer* renderer = nullptr;
    InputHandler* ih = nullptr;
    Player* player = nullptr;

    Player* player2 = nullptr;
    
    bool exit_ = false;

    list<Bala*> MyBullets;
    list<Bala*> EnemyBullets;
    list<Bala*> MyDeadBullets;
    list<Bala*> EnemyDeadBullets;
};

#endif
