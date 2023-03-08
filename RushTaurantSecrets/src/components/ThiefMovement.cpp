#include "./ThiefMovement.h"
#include "../utils/checkML.h"

ThiefMovement::ThiefMovement(GameObject* parent, bool canGetFridger, float escapeSpeed) :
	Component(parent, id), canGetFridger(canGetFridger), currentState(OBJECTIVE), deadTime(1 * 1000), firstTick(0), escapeSpeed(escapeSpeed) {
	straightMovement = parent->getComponent<StraightMovement>();
	transform = parent->getComponent<Transform>();
	sdl = SDLUtils::instance();

	// elegir un camino u otro dependiendo de si puede ir al congelador o no
	int max = canGetFridger ? 2 : 1;
	objective = (Objective)sdl->rand().nextInt(0, max);
	vector<Vector> points;
	switch (objective) {
	case Freezer:
		points.push_back(_ecs::FREEZER);
		break;
	case Secret:
		points.push_back(_ecs::SECRET);
		break;
	}
	straightMovement->addPath(points);
}

void ThiefMovement::die() {
	currentState = DEAD;
	straightMovement->stop();
	firstTick = sdl->currRealTime();
	// se cambia a muerto (se pone rojo el sprite y se tumba el sprite)
	transform->setMovState(dead);
}

void ThiefMovement::escape() {
	currentState = ESCAPE;
	straightMovement->stop();
	straightMovement->addPath({ _ecs::DOOR });
	straightMovement->changeSpeed(escapeSpeed);
}

void ThiefMovement::update() {
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
		// se cambia a la escena en la que los ladrones han descubierto el secreto
		parent->setAlive(false);
		break;

	case FREEZER:
		// se cambia a la escena en la que los ladrones han abierto el congelador
		parent->setAlive(false);
		break;

	case DEAD:
		tick = sdl->currRealTime() - firstTick;
		if (tick > deadTime) {
			parent->setAlive(false);
			tick = 0;	// no haría falta
		}
		break;

	case ESCAPE:
		if (straightMovement->hasFinishedPath()) {
			parent->setAlive(false);
		}
		break;
	}
}
