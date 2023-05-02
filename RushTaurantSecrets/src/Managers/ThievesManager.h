#pragma once

#include "../GameObjects/Thief.h"
#include "../Structure/Manager.h"
#include "../Structure/Scene.h"
#include "../Utilities/RelativeToGlobal.h"
#include "../Utilities/checkML.h"

class ThievesManager : public Manager<ThievesManager> {

	friend Manager<ThievesManager>;

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
	// ladrón con el que est?interactuando el jugador
	GameObject* thiefInteractWith;

	void createThief(int sprite, int pos);

	void addFrequently();

	inline void allFalse() {
		for (int i = 0; i < selectedPosition.size(); ++i) {
			selectedPosition[i] = false;
		}
	}

	int randomPos();

	ThievesManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, int numThiefs, float min, float max);

public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_MANAGER;

	inline bool areThereThieves() const {
		return !thiefs->empty();
	}

	inline void setFrec(float min, float max) {
		minFrec = min;
		maxFrec = max;
	}

	inline GameObject* getThiefInteractWith() const {
		return thiefInteractWith;
	}

	inline void setThiefInteractWith(GameObject* thief) {
		thiefInteractWith = thief;
	}

	vector<GameObject*> canInteractWith();

	virtual void update();

	void nextDay()override;

	void receive(const Message&);

	void haltSound();
	void pauseSound();
	void resumeSound();
};