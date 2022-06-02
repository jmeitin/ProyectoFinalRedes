
#include "Client.h"
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void ChatClient::login()
{
    std::string msg;

    ChatMessage em(nick, msg);
    em.type = ChatMessage::LOGIN;

    socket.send(em, socket);
}

void ChatClient::logout()
{
    // Completar
    std::string msg;

    ChatMessage em(nick, msg);
    em.type = ChatMessage::LOGOUT;

    socket.send(em, socket);
}

void ChatClient::input_thread()
{
    while (true)
    {
        // Leer stdin con std::getline
        // Enviar al servidor usando socket
        std::string msg;
        std::getline(std::cin, msg);
        if (msg == "q" || msg == "Q" ) {
            logout();
            break;
        }
        ChatMessage chatMsg(nick, msg);
        chatMsg.type = ChatMessage::MessageType::MESSAGE;
        socket.send(chatMsg, socket);
    }
}

void ChatClient::net_thread()
{
    while(true)
    {
        //Recibir Mensajes de red
        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        ChatMessage chatMsg;
        socket.recv(chatMsg);
        if(chatMsg.type == ChatMessage::MessageType::LOGOUT)break;
        std::cout << chatMsg.nick << ": " << chatMsg.message << "\n";
    }
}

