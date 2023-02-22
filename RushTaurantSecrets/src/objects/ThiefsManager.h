#pragma once

#include "../gameObjects/Thief.h"
#include "../structure/Manager.h"
#include "../structure/Scene.h"

class ThiefsManager : public Manager<ThiefsManager> {

	friend Manager<ThiefsManager>;

private:
	Scene* scene;
	vector<GameObject*>* thiefs;
	SDLUtils* sdl;
	float generalSpeed;
	float escapeSpeed;
	bool canGetFreezer;
	float timer;
	float lastThiefTime;

	void createThief() {
		string sprite = "Thief_" + to_string(sdl->rand().nextInt(1, 4));
		new Thief(scene, relativeToGlobal(pathsThief[Origin].front()), sprite, generalSpeed, canGetFreezer, escapeSpeed);
	}

	Vector relativeToGlobal(const Vector& point) {
		int fWidth = sdl->width() / 40;
		int fHeight = sdl->height() / 23;
		return Vector(point.getX() * fWidth, point.getY() * fHeight);
	}

	ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, float frequencyThiefs) :
		Manager(parent), generalSpeed(generalSpeed), escapeSpeed(escapeSpeed), canGetFreezer(canGetFreezer), timer(frequencyThiefs) {
		scene = parent->getScene();
		thiefs = scene->getGroup(_ecs::grp_THIEFS);
		sdl = SDLUtils::instance();
		lastThiefTime = sdl->currRealTime();
	}

public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_THIEFS_MANAGER;


	virtual void update() {
		if (thiefs->size() < 1) {
			float time = sdl->currRealTime() - lastThiefTime;
			if (time > timer) {
				createThief();
			}
		}
		else {
			lastThiefTime = sdl->currRealTime();
		}
	}
};