#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"

#include "Message.h"


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
        numPlayers =0;
    };

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void net_thread();
    
private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<std::unique_ptr<Socket>> clients;

    /**
     * Socket del servidor
     */
    Socket socket;

    int numPlayers= 0;
    const int MAX_PLAYERS = 2;

   
};

#endif /* SOCKET_H_ */