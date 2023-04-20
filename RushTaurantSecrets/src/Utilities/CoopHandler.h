#pragma once
#include <SDL_net.h>
#include <string>
#include "../Definitions/Message_def.h"

typedef char byte;
typedef uint8_t id_type;
struct doubleByte { byte first, second; };
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

    byte data[1024];

    int dataLength;

    static const int messageLengths[Message::msg_INVALID];

    void code(const Message& message);
    Message decode(Message::_msg_id id, uint16_t& last);
public:
    CoopHandler();
    ~CoopHandler();

    void update();

    // Métodos de servidor

    void openServer();
    bool connectClient();

    // Métodos de cliente

    bool openClient(std::string ip);
    std::pair<bool, bool> connectServer();

    // Métodos conjuntos

    void closeConnection();
    void receive();
    void send(const Message& message);

    // Locurote

    
    /// <summary>
    /// Para int: desde el -128 hasta el 127 /
    /// Para uint: desde el 0 hasta el 255 /
    /// Para char: todos los carácteres /
    /// Para float: indefinido
    /// </summary>
    template<typename T>
    void code8(T input) {
        data[dataLength] = input;
        dataLength++;
    }
    template<typename T>
    T decode8(uint16_t& last) {
        T output = (T)data[last];
        last++;
        return output;
    }

    template<> void code8<int>(int input) { code8<int8_t>(input); }
    
    /// <summary>
    /// Para int: desde el -32768 hasta el 32767 /
    /// Para uint: desde el 0 hasta el 65535 /
    /// Para float: desde el -3276.8 hasta el 3276.7
    /// </summary>
    template<typename T>
    void code16(T input) {
        doubleByte output;
        output.first = output.second = 0;
        for(uint8_t i = 0; i < 8; i++, input >>= 1) {
            output.second = (output.second << 1) + (input & 1);
        }
        for(uint8_t i = 0; i < 8; i++, input >>= 1) {
            output.first = (output.first << 1) + (input & 1);
        }
        data[dataLength] = output.first; data[dataLength + 1] = output.second;
        dataLength += 2;
    }
    template<typename T>
    T decode16(uint16_t& last) {
        T output{}; std::pair<char, char> input;
        input.first = data[last]; input.second = data[last + 1];
        last += 2;
        for(uint8_t i = 0; i < 8; i++, input.first >>= 1) {
            output = (output << 1) + (input.first & 1);
        }
        for(uint8_t i = 0; i < 8; i++, input.second >>= 1) {
            output = (output << 1) + (input.second & 1);
        }
        return output;
    }

    template<> void code16<int>(int input) { code16<int16_t>(input); }
    template<> int decode16<int>(uint16_t& last) { return decode16<int16_t>(last); }
    template<> void code16<float>(float input) { code16<int16_t>(roundf(input * 10)); }
    template<> float decode16<float>(uint16_t& last) { return decode16<int16_t>(last) / 10.0f; }
};