#pragma once
#include "../structure/GameObject.h"
#include "../components/ClientState.h"

class Client : public GameObject {
public:
	Client(Scene* scene) : GameObject(scene) {
		new ClientState(this);
	}
};