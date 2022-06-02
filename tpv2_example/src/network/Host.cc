#include "Server.h"
#include <thread>
int main(int argc, char **argv)
{
    if(argc < 3){
        std::cout << "Introduzca ./Host <dirección IP> <puerto>";
    }
    Server es(argv[1], argv[2]);

    es.net_thread();

    //std::thread ([&es](){ es.net_thread(); delete &es; }).detach();    

    
    return 0;
}
