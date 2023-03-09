#include "./ThiefsManager.h"

void ThiefsManager::createThief() {
	string sprite = "Thief_" + to_string(sdl->rand().nextInt(1, 4));
	new Thief(scene, RelativeToGlobal::point(_ecs::DOOR), sprite, generalSpeed, canGetFreezer, escapeSpeed);
}

ThiefsManager::ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, float frequencyThiefs, int n) :
	Manager(parent), generalSpeed(generalSpeed), escapeSpeed(escapeSpeed), canGetFreezer(canGetFreezer), timer(frequencyThiefs), n(n), elapsedTime(0) {
	scene = parent->getScene();
	thiefs = scene->getGroup(_ecs::grp_THIEFS);
	sdl = SDLUtils::instance();
}

void ThiefsManager::update() {
	elapsedTime += deltaTime;

	if (thiefs->size() <= 0) {
		if (elapsedTime > timer) {
			elapsedTime = 0;
			for (int i = 0; i < n; ++i) {
				createThief();
			}
		}
	}
}