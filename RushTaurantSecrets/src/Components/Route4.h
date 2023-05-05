#pragma once
#include "../Components/Route.h"

// Cliente empujando carro
class Route4 : public Route {
private:
	enum States {
		START,
		MEAT,
		FISH,
		MEAT2,

	};

	float elapsedTime;
	float timer;
	States state;

public:
	Route4(GameObject* parent, float timer) : Route(parent, Vector(15, 13)), 
		elapsedTime(0), timer(timer), state(START) {

	}

	virtual void update() {
		switch (state) {
		case START:
			if (straightMovement->hasFinishedPath()) {
				transform->setMovState(phone);
				elapsedTime += deltaTime;
				if (elapsedTime > timer) {
					elapsedTime = 0;
					addPath({ Vector(15, 13),Vector(15, 17), Vector(14, 17) });
					state = MEAT;
				}
			}
			break;

		case MEAT:
			if (straightMovement->hasFinishedPath()) {
				elapsedTime += deltaTime;
				if (elapsedTime > timer) {
					elapsedTime = 0;
					reset(Vector(14, 17));
					addPath({ Vector(14, 16), Vector(8, 16), Vector(8,14) });
					state = FISH;
				}
			}
			break;

		case FISH:
			if (straightMovement->hasFinishedPath()) {
				elapsedTime += deltaTime;
				if (elapsedTime > timer) {
					elapsedTime = 0;
					straightMovement->goBack();
					state = MEAT2;
				}
			}
			break;

		case MEAT2:
			if (straightMovement->hasFinishedPath()) {
				elapsedTime += deltaTime;
				if (elapsedTime > timer) {
					elapsedTime = 0;
					addPath({ Vector(15, 17), Vector(15, 13), Vector(14, 13) });
					state = START;
				}
			}
			break;
		}

	}
};