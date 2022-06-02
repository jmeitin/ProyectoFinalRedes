#pragma once

#include "GameObject.h"
#include "InputHandler.h"


class Client;

class Player : public GameObject{
public:
    Player(Client*, Texture*, int x,int y, int s, int w, int h);
    void update();
protected:
    InputHandler* ihs;
    int speed;
    int WIDTH;
    int HEIGHT;
    Client* client = nullptr;
   

};