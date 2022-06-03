#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "InputHandler.h"


class Client;

class Player : public GameObject{
public:
    Player(Client*, Texture*, int x,int y, int s, int w, int h);
    bool update();
protected:
    InputHandler* ihs;
    int speed;
    int WIDTH;
    int HEIGHT;
    Client* client = nullptr;
   

};

#endif