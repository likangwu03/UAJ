#pragma once
#include "../Components/Route.h"

class Route2 : public Route {
private:

public:
	Route2(GameObject* parent, Vector initPos) : Route(parent, initPos) {
		addPath({ Vector(initPos.getX() + 9, initPos.getY()) });
		straightMovement->enableInfiniteRoundTrip();
	}
};