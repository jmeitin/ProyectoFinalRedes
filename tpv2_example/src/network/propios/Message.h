#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"


class Message: public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    enum host_t { p1 = 0, p2 = 1};  

    enum MessageType
    {
        LOGIN   = 0,
        LOGOUT = 1,
        PLAYERPOS  = 2,
        SHOT = 3,
        PlAYERKILLED = 4
    };

    Message(){};

    virtual void to_bin() = 0;

    virtual int from_bin(char * bobj) = 0;

    uint8_t type;
};

class LogMessage: public Message{

public:
    LogMessage(){};
    LogMessage(const std::string& n, const std::string& m):nick(n),message(m){};

    void to_bin() override;
    int from_bin(char * bobj) override;
private:

    std::string nick;
    std::string message;
};

class PlayerPos: public Message{
    public:
    PlayerPos(){};
    PlayerPos(const int& p, const uint8_t& px, const uint8_t& py):player((host_t)p),posx(px), posy(py){};

    void to_bin() override;
    int from_bin(char * bobj) override;
    private:
    host_t player;
    uint8_t posx, posy;
    
};

class Bullet: public Message{
    public:
    Bullet(){};
    Bullet(const uint8_t& p, const uint8_t& px, const uint8_t& py, const float& r): player((host_t)p),
                                                                                posx(px), 
                                                                                posy(py),
                                                                                rot(r){};

    void to_bin() override;
    int from_bin(char * bobj) override;
    private:
    host_t player ;
    uint8_t posx, posy;
    float rot;
    
};

class PlayerKilled: public Message{

public:
    PlayerKilled(){};
    PlayerKilled(const uint8_t& p):player(host_t(p)){};

    void to_bin() override;
    int from_bin(char * bobj) override;
private:
    host_t player;
};