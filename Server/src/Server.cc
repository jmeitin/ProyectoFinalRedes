#include "Server.h"
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void Server::net_thread()
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
        char buffer[Message::MESSAGE_SIZE];
        Message message;
        socket.recv(message,buffer, clientSd);
       
        if (numPlayers < MAX_PLAYERS && message.type == Message::MessageType::LOGIN) {
            LogMessage log ; log.from_bin(buffer);
            std::unique_ptr<Socket> uPtr(clientSd);
            numPlayers+= 1;
            
            clients.push_back(std::move(uPtr));
            std::cout << log.nick << " logged in\n" << "player: "<< numPlayers<< "\n";  
            if(numPlayers == 2){
           for (int i = 0; i < clients.size(); ++i) { 
                Message::host_t host =  Message::host_t(i);                 
                PlayerMsg idMsg(host);
                idMsg.type = Message::MessageType::CONFIRMATION;            
                socket.send(idMsg, (*clients[i].get()));               
            }
            std::cout <<  " confirmaciones\n";  
            }    
            
        }
        else if (message.type == Message::MessageType::LOGOUT) { 
            LogMessage log ; log.from_bin(buffer);          
            auto it = clients.begin();            
            while (it != clients.end() && !(*(*it).get() == *clientSd)) it++;
            clients.erase(it);
            numPlayers-=1;
            
            std::cout << log.nick << " logged out\n";
        }

        else if (message.type == Message::MessageType::PLAYERPOS){           
            Object playerPos; playerPos.from_bin(buffer);
            int otherID = (playerPos.player + 1) % 2;

            socket.send(playerPos, *clients[otherID].get());               
        }

        else if (message.type == Message::MessageType::SHOT || message.type == Message::MessageType::PlAYERKILLED){
            PlayerMsg shot; shot.from_bin(buffer);
            int otherID = (shot.player + 1) % 2;
            
            socket.send(shot, *clients[otherID].get());
        }   

    }


}
