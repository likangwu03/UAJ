#pragma once

#include "../structure/Component.h"
#include "../components/StraightMovement.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include <vector>

class ThiefMovement : public Component {
	enum States{OBJECTIVE, FREEZER, SECRET, DEAD, ESCAPE};

	enum Objective{Freezer, Secret};

	vector<Vector> paths[2] = {
		{Vector(20, 18)},	// secret
		{Vector(24, 18)}	// freezer
	};

private:
	States currentState;
	StraightMovement* straightMovement;
	Transform* transform;
	SDLUtils* sdl;
	bool canGetFridger;
	Objective objective;
	InputHandler* inputHandler;
	float firstTick;
	float timer;
	float escapeSpeed;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	ThiefMovement(GameObject* parent, bool canGetFridger, float escapeSpeed) : Component(parent, id), canGetFridger(canGetFridger), currentState(OBJECTIVE), timer(5000), firstTick(0), escapeSpeed(escapeSpeed) {
		straightMovement = parent->getComponent<StraightMovement>();
		transform = parent->getComponent<Transform>();
		sdl = SDLUtils::instance();
		inputHandler = InputHandler::instance();

		int max = 1;
		if (canGetFridger) {
			++max;
		}
		objective = (Objective)sdl->rand().nextInt(0, max);
		straightMovement->addPath(paths[objective]);
	}

	void update() {
		float tick = 0;
		switch (currentState) {
		case OBJECTIVE:
			if (straightMovement->hasFinishedPath()) {
				switch (objective) {
				case Secret:
					currentState = SECRET;
				case Freezer:
					currentState = FREEZER;
					break;
				}
			}
			break;

		case SECRET:
			parent->setAlive(false);
			break;

		case FREEZER:
			parent->setAlive(false);
			break;
		case DEAD:
			tick = sdl->currRealTime() - firstTick;
			if (tick > timer) {
				parent->setAlive(false);
			}
			break;
		case ESCAPE:
			if (straightMovement->hasFinishedPath()) {
				parent->setAlive(false);
			}
			break;
		}
	}

	void handleEvents() {
		// muere
		if (inputHandler->isKeyDown(SDLK_m)) {
			currentState = DEAD;
			straightMovement->stop();
			firstTick = sdl->currRealTime();
			// se cambia al sprite de muerto
			transform->setMovState(idle);
		}
		// huye
		if (inputHandler->isKeyDown(SDLK_h)) {
			currentState = ESCAPE;
			straightMovement->stop();
			straightMovement->addPath({ Vector(32, 18) });
			straightMovement->changeSpeed(escapeSpeed);
		}
	}
};