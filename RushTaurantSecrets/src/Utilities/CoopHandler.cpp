#include "CoopHandler.h"
#include <exception>
#include <cstdint>
#include "../Structure/Game.h"

#ifdef _DEBUG
#include <iostream>
#endif

// Codificación de mensajes

// Almacena cuantos espacios ocupa cada id de mensaje
const int CoopHandler::messageLengths[]{
	6, // msg_PLACEHOLDER
};

// Recoge la información pertinente del mensaje y la mete en el buffer
void CoopHandler::code(const Message& m, byte* buffer) {
	switch(m.id) {
	case Message::msg_PLACEHOLDER:
		buffer[0] = codeUInt8(m.data_placeholder.dataUint);
		buffer[1] = codeChar(m.data_placeholder.dataChar);
		buffer[2] = codeInt8(m.data_placeholder.dataInt);
		// Las IDs están basadas en UInt8
		buffer[3] = codeUInt8(m.data_placeholder.dataCmpId);
		// El float tiene que codificarse como dos bytes:
		doubleByte aux = codeFloat16(m.data_placeholder.dataFloat);
		buffer[4] = aux.first; buffer[5] = aux.second;
		break;
	}
}

// Recoge la información del buffer y ejecuta las acciones pertinentes
void CoopHandler::decode(Message::_msg_id id, byte* buffer) {
	switch(id) {
	case Message::msg_PLACEHOLDER:
		uint8_t dataUint = decodeUInt8(buffer[0]);
		char dataChar = decodeChar(buffer[1]);
		int dataInt = decodeInt8(buffer[2]);
		_ecs::_cmp_id dataCmpId = (_ecs::_cmp_id)decodeUInt8(buffer[3]);
		float dataFloat = decodeFloat16({ buffer[4], buffer[5] });
		break;
	}
}

// Constructoras y destructoras

CoopHandler::CoopHandler() : set(nullptr), connectionSocket(nullptr), serverSocket(nullptr), dataLength(0), bufferLength(0), data(), buffer() {
#ifdef _DEBUG
	std::cout << "Initializing SDL_net.\n";
#endif

	if(SDLNet_Init() < 0) {
		throw std::exception("SDLNet couldn't initialize.");
	}

	set = SDLNet_AllocSocketSet(1);
}

CoopHandler::~CoopHandler() {
	if(serverSocket) SDLNet_TCP_Close(serverSocket);
	SDLNet_FreeSocketSet(set);
	SDLNet_Quit();
}

// Conexiones

void CoopHandler::openServer() {
#ifdef _DEBUG
	std::cout << "Opening server on port 1882.\n";
#endif

	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, NULL, 1882) < 0) {
		throw std::exception("SDLNet: Couldn't open server (ResolveHost).");
	}

	serverSocket = SDLNet_TCP_Open(&ip);
	if(serverSocket == NULL) {
		throw std::exception("SDLNet: Couldn't open server (TCP_Open).");
	}

#ifdef _DEBUG
	std::cout << "Opened server.\n";
#endif
}

bool CoopHandler::openClient(std::string ipStr) {
#ifdef _DEBUG
	std::cout << "Opening connection with ip \"" << ipStr << ":1882\".\n";
#endif

	IPaddress ip;
	if(SDLNet_ResolveHost(&ip, ipStr.c_str(), 1882) < 0) {
		throw std::exception(("SDLNet: Couldn't resolve ip \"" + ipStr + ":1882\".").c_str());
	}

	connectionSocket = SDLNet_TCP_Open(&ip);
	if(connectionSocket == NULL) {
		return false;
	}
	
	SDLNet_TCP_AddSocket(set, connectionSocket);

#ifdef _DEBUG
	std::cout << "Opened connection with server.";
#endif
	return true;
}

bool CoopHandler::connectClient() {
	connectionSocket = SDLNet_TCP_Accept(serverSocket);

	if(connectionSocket) {
		SDLNet_TCP_Send(connectionSocket, connected, __CONNECTED_LENGTH);
	}

	return connectionSocket;
}

// Comprobar que el servidor conectado es correcto.
std::pair<bool, bool> CoopHandler::connectServer() {
	if(SDLNet_CheckSockets(set, 0) > 0) {
		dataLength = SDLNet_TCP_Recv(connectionSocket, data, 1024);

		if(dataLength != __CONNECTED_LENGTH) {
			dataLength = 0;
			return { true, false };
		}
		dataLength = 0;
		bool achieved = true;
		for(int i = 0; achieved && i < __CONNECTED_LENGTH; i++) {
			if(data[i] != connected[i]) achieved = false;
		}
		if(!achieved) {
			return { true, false };
		}
		return { true, true };
	}
	return { false, false };
}

void CoopHandler::closeConnection() {
	if(connectionSocket) {
		SDLNet_TCP_Send(connectionSocket, "Close", 6);
		SDLNet_TCP_DelSocket(set, connectionSocket);
		SDLNet_TCP_Close(connectionSocket);
		connectionSocket = NULL;
		Game::get()->setExitCoop();
	}
}

// Mensajes

void CoopHandler::receive() {
	while(SDLNet_CheckSockets(set, 0) > 0) {
		dataLength = SDLNet_TCP_Recv(connectionSocket, data, 1024);

		if(dataLength == 6 /*&& == "Close"*/) {
			// Cerrar
		}

		for(int i = 0; i < dataLength;) {
			char id = data[i];
			char* msgBuffer = new char[messageLengths[id]];
			i++;

			for(int j = 0; j < messageLengths[id]; j++, i++) {
				msgBuffer[j] = data[i];
			}

			decode((Message::_msg_id)id, msgBuffer);

			delete[] msgBuffer;
		}
	}
}

void CoopHandler::send() {
	if(bufferLength > 0) {
		SDLNet_TCP_Send(connectionSocket, buffer, bufferLength);
		bufferLength = 0;
	}
}

void CoopHandler::addMessage(const Message& message) {
	if(1024 - bufferLength < messageLengths[message.id] + 1) send();

	char* msgBuffer = new char[messageLengths[message.id]];

	code(message, msgBuffer);

	buffer[bufferLength] = message.id; bufferLength++;
	for(int i = 0; i < messageLengths[message.id]; i++, bufferLength++) {
		buffer[bufferLength] = msgBuffer[i];
	}

	delete[] msgBuffer;
}

// Locurote
inline byte CoopHandler::codeChar(char input) { return input; }
inline char CoopHandler::decodeChar(byte input) { return input; }
inline byte CoopHandler::codeInt8(int input) { return (int8_t)input; }
inline int CoopHandler::decodeInt8(byte input) { return input; }
inline byte CoopHandler::codeUInt8(uint8_t input) { return input; }
inline uint8_t CoopHandler::decodeUInt8(byte input) { return input; }
doubleByte CoopHandler::codeInt16(int input) {
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
int CoopHandler::decodeInt16(doubleByte input) {
	int output = 0;
	for(int i = 0; i < 8; i++, input.first >>= 1) {
		output = (output << 1) + (input.first & 1);
	}
	for(int i = 0; i < 8; i++, input.second >>= 1) {
		output = (output << 1) + (input.second & 1);
	}
	return output;
}
inline doubleByte CoopHandler::codeUInt16(uint16_t input) { return codeInt16(input); }
inline uint16_t CoopHandler::decodeUInt16(doubleByte input) { return decodeInt16(input); }
inline doubleByte CoopHandler::codeFloat16(float input) {
	int aux = (int)(roundf(input * 100));
	return codeInt16(aux);
}
inline float CoopHandler::decodeFloat16(doubleByte input) { return decodeInt16(input) / 100.0f; }