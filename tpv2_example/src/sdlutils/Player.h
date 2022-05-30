
#include "GameObject.h"
#include "InputHandler.h"
class Player : public GameObject{
public:
    Player(Texture*, int,int);
    void update();
protected:
    InputHandler* ihs;

};