#include "OtherPlayerComp.h"
#include "../Structure/Game.h"
#include "../Utilities/CoopHandler.h"
#include "../Structure/GameObject.h"
#include "../Structure/Scene.h"


OtherPlayerComp::OtherPlayerComp(GameObject* parent) : Component(parent, id), timer(0) {
	myTrans = parent->getComponent<Transform>();
	theirTrans = parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>();
	algo = &(*SDLUtils::get()).images().at("BIN_HIGHLIGHT");
}

void OtherPlayerComp::update() {
	//timer += deltaTime;

	Message m{ };
	m.id = Message::msg_PLAYER;
	m.data_player.pos = theirTrans->getPos();
	m.data_player.vel = theirTrans->getVel();
	Game::get()->getCoopHandler()->send(m);
}

void OtherPlayerComp::receive(const Message& message) {
	if(message.id == Message::msg_PLAYER) {
		myTrans->setPos(message.data_player.pos);
		myTrans->setVel(message.data_player.vel);
		// Set move state y orientation
	}
}