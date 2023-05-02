#include "OtherPlayerComp.h"
#include "../Structure/Game.h"
#include "../Utilities/CoopHandler.h"
#include "../Structure/GameObject.h"
#include "../Structure/Scene.h"


OtherPlayerComp::OtherPlayerComp(GameObject* parent, uint8_t scene) : Component(parent, id), timer(0), scene(scene) {
	myTrans = parent->getComponent<Transform>();
	theirTrans = parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>();
}

void OtherPlayerComp::update() {
	timer += deltaTime;

	if(timer > 40) {
		Message m{ };
		m.id = Message::msg_PLAYER;
		m.player.pos = theirTrans->getPos();
		m.player.vel = theirTrans->getVel();
		m.player.scene = scene;
		Game::get()->getCoopHandler()->send(m);
		timer = 0;
	}
}

void OtherPlayerComp::receive(const Message& message) {
	if(message.id == Message::msg_PLAYER && message.player.scene == scene) {
		myTrans->setPos(message.player.pos);
		myTrans->setVel(message.player.vel);
		myTrans->setMovState(message.player.vel.magnitude() == 0 ? idle : walking);
		if(message.player.vel.getX() > 0) myTrans->setOrientation(east);
		if(message.player.vel.getX() < 0) myTrans->setOrientation(west);
		if(message.player.vel.getY() > 0) myTrans->setOrientation(south);
		if(message.player.vel.getY() < 0) myTrans->setOrientation(north);
	}
}

void OtherPlayerComp::sceneOut() {
	Message m{ };
	m.id = Message::msg_PLAYER;
	m.player.pos = Vector(-100, -100);
	m.player.vel = Vector::zero;
	m.player.scene = scene;
	Game::get()->getCoopHandler()->send(m);
}