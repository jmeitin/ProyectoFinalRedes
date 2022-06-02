#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"

#include "Message.h"
#define cliente std::pair<host_t,std::unique_ptr<Socket>> 

/**
 *  Clase para el servidor de chat
 */
class Server
{
public:

    enum host_t { p1 = 0, p2 = 1};

    Server(const char * s, const char * p): socket(s, p)
    {
        socket.bind();
    };

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void net_thread();
    void game_thread();
private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<cliente> clients;

    /**
     * Socket del servidor
     */
    Socket socket;

    int numPlayers;
    const int MAX_PLAYERS = 2;

    bool playing = false;
};