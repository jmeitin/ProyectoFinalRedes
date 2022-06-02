#include "Message.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// void ChatMessage::to_bin()
// {
//     alloc_data(MESSAGE_SIZE);

//     memset(_data, 0, MESSAGE_SIZE);

//     //Serializar los campos type, nick y message en el buffer _data

//     char *tmp = _data;

//     memcpy(tmp, &type, sizeof(uint8_t));
//     tmp += sizeof(uint8_t);

//     memcpy(tmp, nick.c_str(), 8*sizeof(char));
//     tmp += 8*sizeof(char);

//     memcpy(tmp, message.c_str(), 80*sizeof(char));
// }

// int ChatMessage::from_bin(char * bobj)
// {
//     alloc_data(MESSAGE_SIZE);

//     memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);

//     //Reconstruir la clase usando el buffer _data


//     char *tmp = bobj;

//     char nickAux [8];
//     char msgAux [80];

//     memcpy(&type, tmp, sizeof(uint8_t));
//     tmp += sizeof(uint8_t);

//     memcpy(nickAux, tmp, 8*sizeof(char));
//     tmp += 8*sizeof(char);
//     nick = nickAux;

//     memcpy(msgAux, tmp, 80*sizeof(char));
//     message = msgAux;

//     return 0;

// }