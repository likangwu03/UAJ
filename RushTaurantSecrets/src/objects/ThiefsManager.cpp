#include "./ThiefsManager.h"

void ThiefsManager::createThief() {
	string sprite = "Thief_" + to_string(sdl->rand().nextInt(1, 4));
	new Thief(scene, RelativeToGlobal::point(_ecs::DOOR), sprite, generalSpeed, canGetFreezer, escapeSpeed);
}

ThiefsManager::ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, float frequencyThiefs) :
	Manager(parent), generalSpeed(generalSpeed), escapeSpeed(escapeSpeed), canGetFreezer(canGetFreezer), timer(frequencyThiefs) {
	scene = parent->getScene();
	thiefs = scene->getGroup(_ecs::grp_THIEFS);
	sdl = SDLUtils::instance();
	lastThiefTime = sdl->currRealTime();
}

void ThiefsManager::update() {
	if (thiefs->size() < MAX_THIEFS) {
		float time = sdl->currRealTime() - lastThiefTime;
		if (time > timer) {
			createThief();
		}
	}
	else {
		lastThiefTime = sdl->currRealTime();
	}
}