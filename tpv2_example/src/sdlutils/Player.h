#include "GameObject.h"
#include "InputHandler.h"
#include "Bala.h"

class Game;

class Player : public GameObject{
public:
    Player(Game*, Texture*, int x,int y, int s, int w, int h);
    void update();
protected:
    InputHandler* ihs;
    int speed;
    int WIDTH;
    int HEIGHT;
    Game* game = nullptr;
    bool jugadorA = true;

};