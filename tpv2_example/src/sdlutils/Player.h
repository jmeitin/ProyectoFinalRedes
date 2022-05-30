#include "GameObject.h"
#include "InputHandler.h"
#include "Bala.h"

class Player : public GameObject{
public:
    Player(Texture*, int x,int y, int s, int w, int h);
    void update();
protected:
    InputHandler* ihs;
    int speed;
    int WIDTH;
    int HEIGHT;

};