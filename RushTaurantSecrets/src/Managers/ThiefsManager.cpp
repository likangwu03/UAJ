#include "ThiefsManager.h"

#include "../Utilities/checkML.h"


void ThiefsManager::createThief() {
	string sprite = "Thief_" + to_string(sdl->rand().nextInt(1, 9));

	int pos = randomPos();

	Objective objective = randomObjective();

	// posición de cada ladrón respecto de la puerta
	Vector aux = _ecs::DOOR;
	aux.setY(_ecs::DOOR.getY() - pos);

	new Thief(scene, RelativeToGlobal::pointPantry(aux), sprite, generalSpeed, escapeSpeed, objective, pos);
}

void ThiefsManager::addFrequently() {
	elapsedTime += deltaTime;

	if (thiefs->size() <= 0) {
		if (elapsedTime > timer) {
			elapsedTime = 0;

			allFalse();

			for (int i = 0; i < numThiefs; ++i) {
				createThief();
			}
		}
	}
}

int ThiefsManager::randomPos() {
	// posición random
	int pos = sdl->rand().nextInt(0, _ecs::MAX_THIEFS);
	// se comprueba si esa posición está ocupada y si lo está, se coge la siguiente
	while (selectedPosition[pos]) {
		pos = (pos + 1) % _ecs::MAX_THIEFS;
	}
	selectedPosition[pos] = true;

	return pos;
}

Objective ThiefsManager::randomObjective() {
	// elegir un camino u otro dependiendo de si puede ir al congelador o no
	int max = canGetFreezer ? 2 : 1;
	return (Objective)sdl->rand().nextInt(0, max);
}

ThiefsManager::ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, float frequencyThiefs, int numThiefs) :
	Manager(parent), generalSpeed(generalSpeed), escapeSpeed(escapeSpeed), canGetFreezer(canGetFreezer), timer(frequencyThiefs), numThiefs(numThiefs), elapsedTime(0), selectedPosition() {
	scene = parent->getScene();
	thiefs = scene->getGroup(_ecs::grp_THIEFS);
	sdl = SDLUtils::instance();
}

void ThiefsManager::update() {
	addFrequently();
}