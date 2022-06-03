#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "InputHandler.h"

class Client;

class Player : public GameObject{
public:
    Player(Client*, Texture*, int x,int y, int s, int w, int h);
    virtual ~Player();
    bool update();

protected:
    InputHandler* ihs;
    int speed;
    int WIDTH;
    int HEIGHT;
    Client* client = nullptr;
    float timeLastShot = 0; 
    const float COOLDOWN = 1000;
};

#endif