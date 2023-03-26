#pragma once

#include "../Structure/Component.h"
#include "StraightMovement.h"
#include "ThiefState.h"
#include "Transform.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/InputHandler.h"
#include "../Definitions/Paths_def.h"
#include <vector>

class ThiefMovement : public Component {
private:
	StraightMovement* straightMovement;
	Transform* transform;
	ThiefState* thiefState;
	SDLUtils* sdl;
	float escapeSpeed;

	void addPath(const vector<Vector>& points);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	ThiefMovement(GameObject* parent, int pos, float escapeSpeed);

	// se tendría que llamar al pulsar el botón de matar
	void die();

	// se tendría que llamar al pulsar el botón de escapar
	void escape();

	virtual void update();

};