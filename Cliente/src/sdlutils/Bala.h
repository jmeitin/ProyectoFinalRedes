
#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"

class Bala : public GameObject{
public:
    Bala(Texture*, int x, int y, int s, int w, int h, float r = 0);
    virtual ~Bala(){};
    void update();
    
protected:
    int speed;
    int WIDTH;
    int HEIGHT;
    Vector2D velocity;    
};

#endif