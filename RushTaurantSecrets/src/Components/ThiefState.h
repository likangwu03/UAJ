#pragma once
#include "../Structure/Component.h"
#include "../Utilities/SDLUtils.h"
#include "FreezerComp.h"
#include "../Structure/Scene.h"
#include "../Structure/GameManager.h"

class ThiefState : public Component {
public:
	enum States {
		OBJECTIVE_SECRET,
		OBJECTIVE_FREEZER,
		SECRET,
		FREEZER,
		DEAD,
		ESCAPE
	};

private:
	SDLUtils* sdl;
	States currentState;
	GameManager* gm;
	FreezerComp* freezer;
	float elapsedTime;
	float deadTime;
	SoundEffect* fridgeSound;
	SoundEffect* formulaSound;
	States randomObjective(bool canGetFreezer) {
		int max = canGetFreezer ? 2 : 1;
		return (States)sdl->rand().nextInt(0, max);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_STATE;

	ThiefState(GameObject* parent, bool canGetFreezer);

	inline States getState() const {
		return currentState;
	}

	inline void setState(States state) {
		currentState = state;
	}

	inline void hasReachObjective() {
		currentState = (States)((int)currentState + 2);
	}

	virtual void update();
};