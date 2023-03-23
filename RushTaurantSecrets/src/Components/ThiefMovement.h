#pragma once

#include "../Structure/Component.h"
#include "StraightMovement.h"
#include "Transform.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/InputHandler.h"
#include "../Definitions/Paths_def.h"
#include "FreezerComp.h"
#include <vector>

enum Objective { Secret, Freezer };

class ThiefMovement : public Component {
public:
	enum States { OBJECTIVE, FREEZER, SECRET, DEAD, ESCAPE };

private:
	States currentState;
	StraightMovement* straightMovement;
	Transform* transform;
	SDLUtils* sdl;
	GameManager* gm;
	Objective objective;
	FreezerComp* freezer;
	float elapsedTime;
	float deadTime;
	float escapeSpeed;

	void addPath(const vector<Vector>& points);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	ThiefMovement(GameObject* parent, Objective objective, int pos, float escapeSpeed);
	// se tendría que llamar al pulsar el botón de matar
	void die();

	// se tendría que llamar al pulsar el botón de escapar
	void escape();

	States getState() const {
		return currentState;
	}

	virtual void update();

};