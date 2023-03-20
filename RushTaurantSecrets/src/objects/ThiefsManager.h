#pragma once

#include "../gameObjects/Thief.h"
#include "../structure/Manager.h"
#include "../structure/Scene.h"
#include "../objects/RelativeToGlobal.h"
#include "../utils/checkML.h"

class ThiefsManager : public Manager<ThiefsManager> {

	friend Manager<ThiefsManager>;

private:
	const int MAX_THIEFS = 2;
	Scene* scene;
	vector<GameObject*>* thiefs;
	SDLUtils* sdl;
	float generalSpeed;
	float escapeSpeed;
	bool canGetFreezer;
	float timer;
	float elapsedTime;
	int numThiefs;
	// array que se utiliza para saber que posición de las puerta han sido ocupadas y cuales no
	array<bool, _ecs::MAX_THIEFS> selectedPosition;

	void createThief();

	void addFrequently();

	void allFalse() {
		for (int i = 0; i < selectedPosition.size(); ++i) {
			selectedPosition[i] = false;
		}
	}

	int randomPos();

	Objective randomObjective();

	ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, float frequencyThiefs, int numThiefs);

public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_THIEFS_MANAGER;

	bool isThereThieves() const {
		return !thiefs->empty();
	}

	virtual void update();
};