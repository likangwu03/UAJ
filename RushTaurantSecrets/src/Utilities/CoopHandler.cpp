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
		buffer[0] = code8(m.data_placeholder.dataUint);
		buffer[1] = code8(m.data_placeholder.dataChar);
		buffer[2] = code8(m.data_placeholder.dataInt);
		buffer[3] = code8(m.data_placeholder.dataCmpId);
		// El float tiene que codificarse como dos bytes:
		doubleByte aux = code16(m.data_placeholder.dataFloat);
		buffer[4] = aux.first; buffer[5] = aux.second;
		break;
	}
}

// Recoge la información del buffer y ejecuta las acciones pertinentes
void CoopHandler::decode(Message::_msg_id id, byte* buffer) {
	switch(id) {
	case Message::msg_PLACEHOLDER:
		uint8_t dataUint = decode<uint8_t>(buffer[0]);
		char dataChar = decode<char>(buffer[1]);
		int dataInt = decode<int>(buffer[2]);
		_ecs::_cmp_id dataCmpId = decode<_ecs::_cmp_id>(buffer[3]);
		float dataFloat = decode<float>({ buffer[4], buffer[5] });
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
		SDLNet_TCP_AddSocket(set, connectionSocket);
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