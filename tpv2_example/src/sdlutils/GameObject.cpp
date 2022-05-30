

#include "GameObject.h"

GameObject::GameObject(Texture* text , int x , int y){
    texture = text;
    pos.x = x;
    pos.y = y;
}

std::pair<int,int> GameObject::GetPosition(){
    return std::pair<int,int>(pos.x,pos.y);
}

void GameObject::render(){
    texture->render(pos.x, pos.y);
}

void GameObject::move(int x ,int y){
    pos.x += x;
    pos.y += y;
}