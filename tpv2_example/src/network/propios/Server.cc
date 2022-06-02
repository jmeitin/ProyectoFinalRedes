#include "Server.h"
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void ChatServer::net_thread()
{
    while (true)
    {
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */

        //Recibir Mensajes en y en función del tipo de mensaje
        // - LOGIN: Añadir al vector clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)


        Socket* clientSd;
        Message message;
        socket.recv(message, clientSd);
       
        if (message.type == Message::MessageType::LOGIN && numPlayers < MAX_PLAYERS) {
            std::unique_ptr<Socket> uPtr(clientSd);
            player aux = player((host_t)numPlayers,std::move(uPtr));
            clients.push_back(aux);
            if(++numPlayers==2) playing = true;
            std::cout << message.nick << " logged in\n";            
        }
        else if (message.type == Message::MessageType::LOGOUT) {           
            auto it = clients.begin();            
            while (it != clients.end() && !(*(*it).second.get() == *clientSd)) it++;
            clients.erase(it);
            --numPlayers;
            std::cout << message.nick << " logged out\n";
        }
        else if (message.type == Message::MessageType::MESSAGE) {            
            for (int i = 0; i < clients.size(); ++i) {
                if (!(*(clients[i].second.get()) == *clientSd))
                    socket.send(message, (*clients[i].second.get()));
            }
            std::cout << message.nick << " sent a message\n";
        }

        
    }


}

void ChatServer::game_thread(){
    while(playing){

    }
}