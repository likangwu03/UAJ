#pragma once
#include "../Components/Route.h"

// Cliente empujando carro
class Route1 : public Route {
private:
	float elapsedTime;
	float timer;

public:
	Route1(GameObject* parent, float timer, vector<Vector> path) : Route(parent, path[0]), elapsedTime(0), timer(timer) {
		path.erase(path.begin());
		addPath(path);
	}

	virtual void update() {
		if (straightMovement->hasFinishedPath()) {
			elapsedTime += deltaTime;
			if (elapsedTime > timer) {
				elapsedTime = 0;
				straightMovement->goBack();
			}
		}
	}
};