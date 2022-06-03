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
            //cliente aux = cliente((host_t)numPlayers,std::move(uPtr));
            clients.push_back(std::move(uPtr));
            std::cout << log.nick << " logged in\n" << "player: "<< numPlayers<< "\n";  
            if(numPlayers == 2){
           for (int i = 0; i < clients.size(); ++i) {   
                PlayerMsg idMsg(i);
                idMsg.type = Message::MessageType::CONFIRMATION;            
                socket.send(idMsg, (*clients[i].get()));               
            }
            std::cout <<  " confirmaciones\n";  
            }    
            //if(++numPlayers==2) playing = true;
               
                         
        }
        else if (message.type == Message::MessageType::LOGOUT) { 
            LogMessage log ; log.from_bin(buffer);          
            auto it = clients.begin();            
            while (it != clients.end() && !(*(*it).get() == *clientSd)) it++;
            clients.erase(it);
            --numPlayers; playing = false;
            std::cout << log.nick << " logged out\n";
        }
     
        else if (message.type == Message::MessageType::PLAYERPOS
                || message.type == Message::MessageType::SHOT
                || message.type == Message::MessageType::PlAYERKILLED)
                {           
            for (int i = 0; i < clients.size(); ++i) {
                if (!(*(clients[i].get()) == *clientSd))
                    socket.send(message, (*clients[i].get()));
            }            
        }
        // else if (message.type == Message::MessageType::SHOT){
        //     PlayerMsg player; player.from_bin(buffer);
        // }
        // else if (message.type == Message::MessageType::PlAYERKILLED){
        //     PlayerMsg player; player.from_bin(buffer);
        // }
           // else if (message.type == Message::MessageType::MESSAGE) {            
        //     for (int i = 0; i < clients.size(); ++i) {
        //         if (!(*(clients[i].second.get()) == *clientSd))
        //             socket.send(message, (*clients[i].second.get()));
        //     }
        //     std::cout << message.nick << " sent a message\n";
        // }
   
    }


}
