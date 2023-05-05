#include "CoopHandler.h"
#include <exception>
#include <cstdint>
#include "../Structure/Game.h"

#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "checkML.h"


// Constructoras y destructoras

CoopHandler::CoopHandler() : set(nullptr), connectionSocket(nullptr), serverSocket(nullptr),data(), client(false) {
#ifdef _DEBUG
	std::cout << "Initializing SDL_net.\n";
#endif

	if (SDLNet_Init() < 0) {
		throw std::exception("SDLNet couldn't initialize.");
	}

	set = SDLNet_AllocSocketSet(1);
	gm = GameManager::get();
}

CoopHandler::~CoopHandler() {
	if (serverSocket) SDLNet_TCP_Close(serverSocket);
	SDLNet_FreeSocketSet(set);
	SDLNet_Quit();
}


// Conexiones

void CoopHandler::openServer() {
#ifdef _DEBUG
	std::cout << "Opening server on port 1882.\n";
#endif
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, NULL, 1882) < 0) {
		throw std::exception("SDLNet: Couldn't open server (ResolveHost).");
	}

	serverSocket = SDLNet_TCP_Open(&ip);
	if (serverSocket == NULL) {
		throw std::exception("SDLNet: Couldn't open server (TCP_Open).");
	}
}

bool CoopHandler::openClient(std::string ipStr) {

	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, ipStr.c_str(), 1882) < 0) {
		throw std::exception(("SDLNet: Couldn't resolve ip \"" + ipStr + ":1882\".").c_str());
	}

	connectionSocket = SDLNet_TCP_Open(&ip);
	if (connectionSocket == NULL) {
		return false;
	}

	SDLNet_TCP_AddSocket(set, connectionSocket);
	return true;
}

bool CoopHandler::connectClient() {
	connectionSocket = SDLNet_TCP_Accept(serverSocket);

	if (connectionSocket) {
		SDLNet_TCP_Send(connectionSocket, connected, __CONNECTED_LENGTH);
		SDLNet_TCP_AddSocket(set, connectionSocket);
	}

	return connectionSocket;
}

// Comprobar que el servidor conectado es correcto.
std::pair<bool, bool> CoopHandler::connectServer() {
	if (SDLNet_CheckSockets(set, 0) > 0) {
		int dataLength = SDLNet_TCP_Recv(connectionSocket, data, 1024);
		dataLength = 0;
		bool achieved = true;
		for (int i = 0; achieved && i < __CONNECTED_LENGTH; i++) {
			if (data[i] != connected[i]) achieved = false;
		}
		if (!achieved) {
			return { true, false };
		}
		client = true;
		return { true, true };
	}
	return { false, false };
}

void CoopHandler::closeConnection() {
	
	if (connectionSocket) {
		SDLNet_TCP_DelSocket(set, connectionSocket);
		SDLNet_TCP_Close(connectionSocket);
		connectionSocket = NULL;
		client = false;
	}
	closeServer();
}

// Mensajes

bool CoopHandler::send(const Message& message) {
	if (!connectionSocket)return false;
	Uint8* end = message.code(data);
	Uint16 size = end - data;
	assert(size <= bufferSize_);
	auto result = SDLNet_TCP_Send(connectionSocket, reinterpret_cast<Uint8*>(&size),sizeof(size));
	if (result != sizeof(size))
		return false;
	result = SDLNet_TCP_Send(connectionSocket, data, size);
	return result == size;
}


Uint8* CoopHandler::receiveMsg(TCPsocket sock) {
	int result = 0;
	result = SDLNet_TCP_Recv(sock, data, sizeof(Uint16));
	if (result != sizeof(Uint16))
		return nullptr;
	Uint16 size = (*reinterpret_cast<Uint16*>(data));
	assert(size <= bufferSize_);
	auto bytesRead = 0;
	while (bytesRead < size) {
		result = SDLNet_TCP_Recv(sock, data + bytesRead,
			size - bytesRead);
		if (result < 1)
			return nullptr;
		bytesRead += result;
	}
	return data;
}


bool CoopHandler::Receive(Message& v) {
	Uint8* msg = receiveMsg(connectionSocket);
	if (msg == nullptr)
		return false;
	else {
		v.decode(data);
		return true;
	}
}

void CoopHandler::receive() {
	while (SDLNet_CheckSockets(set, 0) > 0) {
		Message m;
		if (!Receive(m)) { // Desconexión
			GameObject* otherPlayer = GameManager::get()->getCurrentScene()->getGameObject(_ecs::hdr_OTHERPLAYER);
			if(otherPlayer != nullptr) otherPlayer->getComponent<Transform>()->setPos(Vector(-100, -100));
			SDLNet_TCP_DelSocket(set, connectionSocket);
			Game::get()->setExitCoop();
			return;
		}
		gm->receive(m);
	}
}

void CoopHandler::closeServer() {
	if (serverSocket) SDLNet_TCP_Close(serverSocket);
}