#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"


class   Message: public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 9 + sizeof(uint8_t) + sizeof(int) * 2 + sizeof(float);

    enum host_t { p1 = 0, p2 = 1};  

    enum MessageType
    {
        LOGIN   = 0,
        LOGOUT = 1,
        PLAYERPOS  = 2,
        SHOT = 3,
        PlAYERKILLED = 4,
        CONFIRMATION = 5
    };

    Message(){};

    virtual void to_bin() ;

    virtual int from_bin(char * bobj);

    uint8_t type;
    
};

class LogMessage: public Message{

public:
    LogMessage(){};
    LogMessage(const std::string& n):nick(n){};

    void to_bin() override;
    int from_bin(char * bobj) override;

    std::string nick;
};


//esta clase sirve tanto para mandar player y su orientacion 
class Object: public Message{
public:
    Object(){};
    Object(const host_t& p, const int& px, const int& py, const float& r): player((host_t)p),
                                                                                posx(px), 
                                                                                posy(py),
                                                                                rot(r){};

    void to_bin() override;
    int from_bin(char * bobj) override;
    
    host_t player ;
    int posx, posy;
    float rot;
    
};

class PlayerMsg: public Message{

public:
    PlayerMsg(){};
    PlayerMsg(const host_t& p):player(host_t(p)){};

    void to_bin() override;
    int from_bin(char * bobj) override;

    host_t player;
};













// class PlayerPos: public Message{
//     public:
//     PlayerPos(){};
//     PlayerPos(const int& p, const uint8_t& px, const uint8_t& py):player((host_t)p),posx(px), posy(py){};

//     void to_bin() override;
//     int from_bin(char * bobj) override;
//     private:
//     host_t player;
//     uint8_t posx, posy;
    
// };
#endif /* SOCKET_H_ */