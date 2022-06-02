#include "Server.h"

int main(int argc, char **argv)
{
    if(argc < 3){
        std::cout << "Introduzca ./Host <dirección IP> <puerto>"
    }
    Server es(argv[1], argv[2]);

    std::thread ([&es](){ es.net_thread(); delete &es; }).detach();    

    es.game_thread();
    return 0;
}
