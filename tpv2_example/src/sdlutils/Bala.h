
#pragma once

#include "GameObject.h"
//#include "InputHandler.h"
class Bala : public GameObject{
public:
    Bala(Texture*, int x, int y, int s, int w, int h, double r = 0,bool j = false);
    void update();
    bool getCreator();
protected:
   // InputHandler* ihs;
    int speed;
    int WIDTH;
    int HEIGHT;
    Vector2D velocity;
    bool jugadorA;
};