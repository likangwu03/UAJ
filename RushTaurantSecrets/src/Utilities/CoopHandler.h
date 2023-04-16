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

    bool openClient(std::string ip);
    std::pair<bool, bool> connectServer();

    // Métodos conjuntos

    void closeConnection();
    void receive();
    void send();
    void addMessage(const Message& message);

    // Locurote

    
    template<typename T>
    /// <summary>
    /// Para int: desde el -128 hasta el 127 /
    /// Para uint: desde el 0 hasta el 255 /
    /// Para char: todos los carácteres /
    /// Para float: indefinido
    /// </summary>
    byte code8(T input) { return input; }
    template<typename T>
    T decode(byte input) { return (T)input; }

    template<> byte code8<int>(int input) { return (int8_t)input; }
    
    
    template<typename T>
    /// <summary>
    /// Para int: desde el -32768 hasta el 32767 /
    /// Para uint: desde el 0 hasta el 65535 /
    /// Para float: desde el -327.68 hasta el 327.67
    /// </summary>
    doubleByte code16(T input) { return { -1, -1 }; }
    template<typename T>
    T decode(doubleByte input) { return T(); }

    template<> doubleByte code16<int>(int input) {
        doubleByte output;
        output.first = output.second = 0;
        for(uint8_t i = 0; i < 8; i++, input >>= 1) {
            output.second = (output.second << 1) + (input & 1);
        }
        for(uint8_t i = 0; i < 8; i++, input >>= 1) {
            output.first = (output.first << 1) + (input & 1);
        }
        return output;
    }
    template<> int decode(doubleByte input) {
        int output = 0;
        for(int i = 0; i < 8; i++, input.first >>= 1) {
            output = (output << 1) + (input.first & 1);
        }
        for(int i = 0; i < 8; i++, input.second >>= 1) {
            output = (output << 1) + (input.second & 1);
        }
        return output;
    }
    template<> doubleByte code16<uint16_t>(uint16_t input) { return code16<int>(input); }
    template<> uint16_t decode<uint16_t>(doubleByte input) { return decode<int>(input); }
    template<> doubleByte code16<float>(float input) { return code16<int>(roundf(input * 100)); }
    template<> float decode<float>(doubleByte input) { return decode<int>(input) / 100.0f; }
};