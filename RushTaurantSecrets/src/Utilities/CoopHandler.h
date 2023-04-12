#pragma once
#include <SDL_net.h>
#include <string>
#include "../Definitions/Message_def.h"

typedef char byte;
typedef uint8_t id_type;
struct doubleByte { byte first, second; };


class CoopHandler {
private:
    SDLNet_SocketSet set;
    TCPsocket connectionSocket, serverSocket;

    static const int __CONNECTED_LENGTH = 10;
    // Mensaje recibido al conectarse al servidor (si todo ha ido bien)
    const char connected[__CONNECTED_LENGTH] = "Connected";

    byte data[1024], buffer[1024];

    int dataLength, bufferLength;

    static const int messageLengths[Message::msg_INVALID];

    void code(const Message& message, byte* buffer);
    void decode(Message::_msg_id id, byte* buffer);
public:
    CoopHandler();
    ~CoopHandler();

    // Métodos de servidor

    void openServer();
    bool connectClient();

    // Métodos de cliente

    void openClient(std::string ip);

    // Métodos conjuntos

    void closeConnection();
    void receive();
    void send();
    void addMessage(const Message& message);

    // Locurote

    // Se puede pasar cualquier carácter
    byte codeChar(char); char decodeChar(byte);
    // 8 bits va desde el -128 hasta el 127
    byte codeInt8(int); int decodeInt8(byte);
    // 8 bits va desde el 0 hasta el 255
    byte codeUInt8(uint8_t); uint8_t decodeUInt8(byte);
    // 16 bits va desde el -32768 hasta el 32767
    doubleByte codeInt16(int); int decodeInt16(doubleByte);
    // 16 bits va desde el 0 hasta el 65535
    doubleByte codeUInt16(uint16_t); uint16_t decodeUInt16(doubleByte);
    // 16 bits va desde el -327.68 hasta el 327.67
    doubleByte codeFloat16(float); float decodeFloat16(doubleByte);
};