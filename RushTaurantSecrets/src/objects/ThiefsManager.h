#pragma once

#include "../gameObjects/Thief.h"
#include "../structure/Manager.h"
#include "../structure/Scene.h"
#include "../objects/RelativeToGlobal.h"

class ThiefsManager : public Manager<ThiefsManager> {

	friend Manager<ThiefsManager>;

private:
	const int MAX_THIEFS = 1;
	Scene* scene;
	vector<GameObject*>* thiefs;
	SDLUtils* sdl;
	float generalSpeed;
	float escapeSpeed;
	bool canGetFreezer;
	float timer;
	float lastThiefTime;

	void createThief();

	ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, float frequencyThiefs);

public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_THIEFS_MANAGER;

	bool isThereThieves() const {
		return !thiefs->size();
	}

	virtual void update();
};