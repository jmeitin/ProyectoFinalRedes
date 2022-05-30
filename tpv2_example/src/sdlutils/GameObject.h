
#pragma once

#include "Texture.h"
class GameObject {

struct position{
    int x;
    int y;
};
public:
    GameObject(Texture* text , int x , int y);
    std::pair<int,int> GetPosition();
    void render();    
    void move(int x,int y);
    
protected:
    Texture* texture;
    position pos;
};