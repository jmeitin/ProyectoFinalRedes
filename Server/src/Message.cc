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

    memcpy(bin, nick.c_str(), 8*sizeof(char));
    bin += 8;  
 }
 int LogMessage::from_bin(char * bobj) {
     Message::from_bin(bobj);

     char* bin = _data + 1;

    char nickAux [8];

    memcpy(&nickAux, bin, sizeof(char)*8);
    bin += sizeof(char)*8;
    nick = nickAux;
  
    return 0;
 }

 void Object::to_bin() {
    Message::to_bin();

    char* bin = _data + 1 ;

    memcpy(bin, &player, sizeof(host_t));
    bin += sizeof(host_t);  

     memcpy(bin, &posx, sizeof(uint8_t));
    bin += sizeof(uint8_t);  

     memcpy(bin, &posy, sizeof(uint8_t));
    bin += sizeof(uint8_t);  

    memcpy(bin, &rot, sizeof(float));
    bin += sizeof(float);  
 }
 int Object::from_bin(char * bobj) {
    Message::from_bin(bobj);

     char* bin = _data +1 ;

   

     memcpy(&player, bin, sizeof(host_t));
    bin += sizeof(host_t);  

     memcpy( &posx, bin,sizeof(uint8_t));
    bin += sizeof(uint8_t);  

     memcpy(&posy, bin,sizeof(uint8_t));
    bin += sizeof(uint8_t);  

    memcpy(&rot, bin, sizeof(float));
    bin += sizeof(float);  
    
    
  
    return 0;
 }


void PlayerMsg::to_bin() {
    Message::to_bin();

    char* bin = _data + 1 ;

    memcpy(bin, &player, 1);
    bin += sizeof(host_t);  
 }
 int PlayerMsg::from_bin(char * bobj) {
      Message::from_bin(bobj);

    char* bin = _data +1;

    memcpy(&player, bin, sizeof(char)*8);
    bin += sizeof(host_t);
  
  
    return 0;
 }

