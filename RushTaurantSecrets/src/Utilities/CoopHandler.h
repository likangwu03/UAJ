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

    Uint8* receiveMsg(TCPsocket sock);
    bool Receive(Message& v);
    
public:
    CoopHandler();
    ~CoopHandler();

    bool isClient() { return client; }

    // Métodos de servidor

    void openServer();
    bool connectClient();

    // Métodos de cliente

    bool openClient(std::string ip);
    std::pair<bool, bool> connectServer();

    // Métodos conjuntos
    void closeServer();
    void closeConnection();
    void receive();
    bool send(const Message& message);
};