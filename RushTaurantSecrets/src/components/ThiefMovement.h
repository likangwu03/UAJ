#pragma once

#include "../structure/Component.h"
#include "../components/StraightMovement.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include <vector>

vector<Vector> pathsThief[3] = {
	{Vector(32, 18)},	// origin
	{Vector(20, 18)},	// secret
	{Vector(24, 18)}	// freezer
};

enum Objective { Origin, Freezer, Secret };

class ThiefMovement : public Component {
	enum States { OBJECTIVE, FREEZER, SECRET, DEAD, ESCAPE };

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

	ThiefMovement(GameObject* parent, bool canGetFridger, float escapeSpeed) : 
		Component(parent, id), canGetFridger(canGetFridger), currentState(OBJECTIVE), timer(5000), firstTick(0), escapeSpeed(escapeSpeed) {
		straightMovement = parent->getComponent<StraightMovement>();
		transform = parent->getComponent<Transform>();
		sdl = SDLUtils::instance();
		inputHandler = InputHandler::instance();

		int max = 2;
		if (canGetFridger) {
			++max;
		}
		objective = (Objective)sdl->rand().nextInt(1, max);
		straightMovement->addPath(pathsThief[objective]);
	}

	// se tendría que llamar al pulsar el botón de matar
	void die() {
		currentState = DEAD;
		straightMovement->stop();
		firstTick = sdl->currRealTime();
		// se cambia a muerto (se pone rojo el sprite y se tumba el sprite)
		transform->setMovState(dead);
	}

	// se tendría que llamar al pulsar el botón de escapar
	void escape() {
		currentState = ESCAPE;
		straightMovement->stop();
		straightMovement->addPath(pathsThief[Origin]);
		straightMovement->changeSpeed(escapeSpeed);
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
				tick = 0;
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
			die();
		}
		// huye
		if (inputHandler->isKeyDown(SDLK_h)) {
			escape();
		}
	}
};