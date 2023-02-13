#pragma once
#include "../structure/GameObject.h"

class Client : public GameObject {
public:
	Client(Scene* scene) : GameObject(scene) { }
};