#include "CoopHandler.h"
#include <exception>
#include <cstdint>
#include "../Structure/Game.h"

#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "checkML.h"

#ifdef _DEBUG
#include <iostream>
#endif

// Codificación de mensajes

// Almacena cuantos espacios ocupa cada id de mensaje
const int CoopHandler::messageLengths[]{
	8, // msg_PLAYER
};

// Recoge la información pertinente del mensaje y la mete en el buffer
void CoopHandler::code(const Message& m) {
	switch(m.id) {
	case Message::msg_PLAYER:
		code16(m.player.pos.getX());
		code16(m.player.pos.getY());
		code16(m.player.vel.getX());
		code16(m.player.vel.getY());
		code8(m.player.scene);
		break;
	case Message::msg_BASKET:
		code8(m.basket.ing);
		code8(m.basket.n);
		break;
	}
}

// Recoge la información del buffer y ejecuta las acciones pertinentes
Message CoopHandler::decode(Message::_msg_id id, uint16_t& last) {
	Message m{ };
	m.id = id;
	switch(id) {
	case Message::msg_PLAYER:
		m.player.pos.setX(decode16<float>(last));
		m.player.pos.setY(decode16<float>(last));
		m.player.vel.setX(decode16<float>(last));
		m.player.vel.setY(decode16<float>(last));
		m.player.scene = decode8<uint8_t>(last);
		break;
	case Message::msg_BASKET:
		m.basket.ing = decode8<_ecs::_ingredients_id>(last);
		m.basket.n = decode8<int>(last);
	}
	return m;
}

// Constructoras y destructoras

CoopHandler::CoopHandler() : set(nullptr), connectionSocket(nullptr), serverSocket(nullptr), dataLength(0), data(), client(false) {
#ifdef _DEBUG
	std::cout << "Initializing SDL_net.\n";
#endif

	if(SDLNet_Init() < 0) {
		throw std::exception("SDLNet couldn't initialize.");
	}

	set = SDLNet_AllocSocketSet(1);
	gm = GameManager::get();
}

CoopHandler::~CoopHandler() {
	if(serverSocket) SDLNet_TCP_Close(serverSocket);
	SDLNet_FreeSocketSet(set);
	SDLNet_Quit();
}

void CoopHandler::update() {
	
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
		client = true;
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
		client = false;
		Game::get()->setExitCoop();
	}
}

// Mensajes

void CoopHandler::receive() {
	while(SDLNet_CheckSockets(set, 0) > 0) {
		dataLength = SDLNet_TCP_Recv(connectionSocket, data, 1024);

		if(dataLength == -1) { // Desconexión
			GameManager::get()->getCurrentScene()->getGameObject(_ecs::hdr_OTHERPLAYER)
				->getComponent<Transform>()->setPos(Vector(-100, -100));

			SDLNet_TCP_DelSocket(set, connectionSocket);
			SDLNet_TCP_Close(connectionSocket);
			connectionSocket = NULL; client = false;
			Game::get()->setExitCoop();
			return;
		}

		if(dataLength == 6 /*&& == "Close"*/) {
			// Cerrar
		}

		char id = data[0];
		uint16_t last = 1;

		Message m = decode((Message::_msg_id)id, last);

		gm->receive(m);
	}
}

void CoopHandler::send(const Message& message) {
	if(connectionSocket == nullptr) return;

	data[0] = message.id;
	dataLength = 1;

	code(message);

	SDLNet_TCP_Send(connectionSocket, data, dataLength);
}

void CoopHandler::closeServer() {
	if (serverSocket) SDLNet_TCP_Close(serverSocket);
}