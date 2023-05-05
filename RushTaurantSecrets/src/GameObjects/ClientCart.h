#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/StraightMovement.h"
#include "../Components/ClientWithCart.h"

class ClientCart : public GameObject {
private:
	int width;
	int height;

public:
	ClientCart(Scene* scene, string sprite, float speed) : GameObject(scene), width(48), height(96) {
		new Transform(this, Vector(0, 0), Vector(0, 0), width, height);
		StraightMovement* s = new StraightMovement(this, speed);
		s->setWalkingState(pushing);
		new ClientWithCart(this, sprite);

		scene->pushRenderList(Down, this);
	}
};