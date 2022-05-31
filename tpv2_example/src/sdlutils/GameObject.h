
#pragma once

#include "Texture.h"
class GameObject {

struct position{
    int x;
    int y;
};
public:
    GameObject(Texture* text , int x , int y, double r = 0);
    std::pair<int,int> GetPosition();
    void render();  
     void move(Vector2D);  
    void move(int x,int y);
    bool isDestroyable(){return destructible;};
    void setDestroyable(bool d){destructible = d;};

    float getW();
    float getH();
    float getRot();
    Vector2D getPosition2();
protected:
    Texture* texture;
    position pos;
    double rot;
    bool destructible = false;
};