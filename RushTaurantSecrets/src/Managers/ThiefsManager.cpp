#include "ThiefsManager.h"

#include "../Utilities/checkML.h"


void ThiefsManager::createThief() {
	string sprite = "Thief_" + to_string(sdl->rand().nextInt(1, 9));

	int pos = randomPos();

	// posición de cada ladrón respecto de la puerta
	Vector aux = _ecs::DOOR;
	aux.setY(_ecs::DOOR.getY() - pos);

	new Thief(scene, RelativeToGlobal::pointPantry(aux), sprite, generalSpeed, escapeSpeed, canGetFreezer, pos);

	warningSound->play(-1);
	played = true;
}

void ThiefsManager::addFrequently() {
	if (thiefs->size() <= 0) {
		if (played) {
			played = false;
			warningSound->haltChannel();
		}
		elapsedTime += deltaTime;
		if (elapsedTime > timer * 1000) {
			elapsedTime = 0;
			timer = sdl->rand().nextInt(minFrec, maxFrec);
			allFalse();
			int auxNum = sdl->rand().nextInt(1, numThiefs + 1);
			for (int i = 0; i < auxNum; ++i) {
				createThief();
			}
		}
	}
}

int ThiefsManager::randomPos() {
	// posición random
	int pos = sdl->rand().nextInt(0, _ecs::MAX_THIEFS);
	// se comprueba si esa posición est?ocupada y si lo est? se coge la siguiente
	while (selectedPosition[pos]) {
		pos = (pos + 1) % _ecs::MAX_THIEFS;
	}
	selectedPosition[pos] = true;

	return pos;
}

ThiefsManager::ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, int numThiefs, float min, float max) :
	Manager(parent), sdl(SDLUtils::instance()), warningSound(&sdl->soundEffects().at("ALERT")), played(false),
	generalSpeed(generalSpeed), escapeSpeed(escapeSpeed), canGetFreezer(canGetFreezer), minFrec(min), maxFrec(max), numThiefs(numThiefs), elapsedTime(0), selectedPosition() {
	scene = parent->getScene();
	thiefs = scene->getGroup(_ecs::grp_THIEFS);
	timer = sdl->rand().nextInt(minFrec, maxFrec);
	warningSound->setVolume(40);
}

void ThiefsManager::update() {
	addFrequently();
}

void ThiefsManager::stopSound() {
	warningSound->haltChannel();
}