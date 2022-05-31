

#include "GameObject.h"

GameObject::GameObject(Texture* text , int x , int y, double r){
    texture = text;
    pos.x = x;
    pos.y = y;
    rot = r;
}

std::pair<int,int> GameObject::GetPosition(){
    return std::pair<int,int>(pos.x,pos.y);
}

Vector2D GameObject::getPosition2(){
    return Vector2D(pos.x,pos.y);
}
void GameObject::render(){
    SDL_Rect dest = { pos.x, pos.y, texture->width(), texture->height() };
    texture->render(dest, rot);
}
void GameObject::move(Vector2D vel){
    pos.x += vel.getX();
    pos.y += vel.getY();
}
float GameObject::getW(){
    return texture->width();
}
float GameObject::getH(){
    return texture->height();
}
float GameObject::getRot(){
    return rot;
}
// void GameObject::move(int x ,int y){
//     pos.x += x;
//     pos.y += y;
// }