#pragma once
#include "../Components/Route.h"

class Route1 : public Route {
private:
	float elapsedTime;
	float timer;

public:
	Route1(GameObject* parent) : Route(parent, Vector(10, 5)), elapsedTime(0), timer(10000) {
		addPath({ Vector(10, 9), Vector(20, 9) });
	}

	virtual void update() {
		if (transform->getMovState() == idle) {
			elapsedTime += deltaTime;
			if (elapsedTime > timer) {
				elapsedTime = 0;
				straightMovement->goBack();
			}
		}
	}
};