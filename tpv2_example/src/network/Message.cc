#include "Message.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void Message::to_bin(){
 alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    //Serializar los campos type, nick y message en el buffer _data
    char* bin = _data;

    memcpy(bin, &type, 1);
    bin += 1;   
}

int Message::from_bin(char * bobj){

    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);

    char* bin = _data;

    memcpy(&type, bin, sizeof(uint8_t));
    bin += sizeof(uint8_t);
}



 void LogMessage::to_bin() {
     Message::to_bin();

    char* bin = _data + 1 ;

    memcpy(bin, &nick, 1);
    bin += 8;  
 }
 int LogMessage::from_bin(char * bobj) {
     Message::from_bin(bobj);

     char* bin = _data;

    char nickAux [8];

    memcpy(&nickAux, bin, sizeof(char)*8);
    bin += sizeof(char)*8;
    nick = nickAux;
  
    return 0;
 }

 void Object::to_bin() {

 }
 int Object::from_bin(char * bobj) {
     
 }


void PlayerMsg::to_bin() {

 }
 int PlayerMsg::from_bin(char * bobj) {
     
 }

