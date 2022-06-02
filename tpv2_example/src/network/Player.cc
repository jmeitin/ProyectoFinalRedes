#include <thread>
#include "../sdlutils/Game.h"

int main(int argc, char **argv)
{
    Client ec(argv[1], argv[2], argv[3]);    
    std::thread ([&ec](){ ec.net_thread(); delete &ec; }).detach();    

    ec.login();

    ec.input_thread();
}

