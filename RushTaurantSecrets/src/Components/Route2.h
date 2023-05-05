#pragma once
#include "../Components/Route.h"

// Conga
class Route2 : public Route {
private:
	int length;

public:
	Route2(GameObject* parent, Vector initPos, int length) : Route(parent, initPos), length(length) {
		addPath({ Vector(initPos.getX() + length, initPos.getY()) });
		straightMovement->setWalkingState(pushing);
		straightMovement->enableInfiniteRoundTrip();
	}
};