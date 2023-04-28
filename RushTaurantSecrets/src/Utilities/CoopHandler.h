#pragma once
#include <SDL_net.h>
#include <string>
#include "../Definitions/Message_def.h"


class GameManager;


class CoopHandler {
private:
    SDLNet_SocketSet set;
    TCPsocket connectionSocket, serverSocket;
    bool client;
    GameManager* gm;

    static const int __CONNECTED_LENGTH = 10;
    // Mensaje recibido al conectarse al servidor (si todo ha ido bien)
    const char connected[__CONNECTED_LENGTH] = "Connected";
    static constexpr std::size_t bufferSize_ = 1024;
    Uint8 data[bufferSize_];

    int dataLength;

    void code(const Message& message);

    Message decode(Message::_msg_id id, uint16_t& last);

    Uint8* receiveMsg(TCPsocket sock);
    bool Receive(Message& v);
    
public:
    CoopHandler();
    ~CoopHandler();

    void update();

    bool isClient() { return client; }

    // M�todos de servidor

    void openServer();
    bool connectClient();

    // M�todos de cliente

    bool openClient(std::string ip);
    std::pair<bool, bool> connectServer();

    // M�todos conjuntos
    void closeServer();
    void closeConnection();
    void receive();
    bool send(Message& message);
};