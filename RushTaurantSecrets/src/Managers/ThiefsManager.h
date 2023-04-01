#pragma once

#include "../GameObjects/Thief.h"
#include "../Structure/Manager.h"
#include "../Structure/Scene.h"
#include "../Utilities/RelativeToGlobal.h"
#include "../Utilities/checkML.h"

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
	float minFrec, maxFrec;
	float elapsedTime;
	int numThiefs;
	bool played;
	SoundEffect* warningSound;
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

	ThiefsManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, int numThiefs, float min, float max);

public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_MANAGER;

	bool isThereThieves() const {
		return !thiefs->empty();
	}

	void setFrec(float min, float max) {
		minFrec = min;
		maxFrec = max;
	}

	virtual void update();
	void stopSound();
};