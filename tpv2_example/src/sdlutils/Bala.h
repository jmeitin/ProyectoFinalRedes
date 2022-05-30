#include "GameObject.h"
//#include "InputHandler.h"
class Bala : public GameObject{
public:
    Bala(Texture*, int x, int y, int s, int w, int h);
    void update();

protected:
   // InputHandler* ihs;
    int speed;
    int WIDTH;
    int HEIGHT;

};