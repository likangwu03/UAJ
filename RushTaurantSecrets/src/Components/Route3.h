#pragma once
#include "../Components/Route.h"

// Pescadería
class Route3 : public Route {
private:
	enum States {
		START,
		LOOP
	};

	Vector initPos;
	Vector endPos;
	float elapsedTime;
	float timer;
	States state;

public:
	Route3(GameObject* parent, Vector initPos, Vector endPos, float timer) : Route(parent, initPos),
		initPos(initPos), endPos(endPos), elapsedTime(0), timer(timer), state(START) {
		transform->setOrientation(east);
	}

	virtual void update() {
		switch (state) {
		case START:
			elapsedTime += deltaTime;
			if (elapsedTime > timer) {
				elapsedTime = 0;

				addPath({ initPos, endPos });

				state = LOOP;
			}
			break;

		case LOOP:
			if (straightMovement->hasFinishedPath()) {
				transform->setOrientation(east);
				elapsedTime += deltaTime;
				if (elapsedTime > timer) {
					elapsedTime = 0;
					straightMovement->goBack();
				}
			}
			break;
		}
	}
};