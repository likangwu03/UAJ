#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/StraightMovement.h"
#include "../Components/ClientWithCart.h"

class ClientMarket : public GameObject {
private:
	int width;
	int height;

public:
	ClientMarket(Scene* scene) : GameObject(scene), width(48), height(96) {
		new Transform(this, Vector(0, 0), Vector(0, 0), width, height);
		StraightMovement* s = new StraightMovement(this, 3);
		s->setWalkingState(pushing);
		new ClientWithCart(this);

		scene->pushRenderList(Down, this);
	}
};