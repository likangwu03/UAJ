#pragma once
#include "SDL.h"
#include <iostream>
#include "../structure/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../structure/GameObject.h"
#include "Transform.h"


class PlayerMovementController : public Component
{
private:
	int offset = 8;
	Vector speed = (0,0);

	Transform* transform = nullptr;
	InputHandler* input;
public:
	PlayerMovementController(GameObject* parent, _ecs::_cmp_id id) : Component(parent, id) {
		transform = parent->getComponent<Transform>();
		input = InputHandler::instance();
		input->initialiseJoysticks();
	}
	~PlayerMovementController() { 
		input->clean();
	}
	virtual void handleEvents() {
		input->refresh();
		if (input->joysticksInitialised())
		{
			if (input->xvalue(0, 1) > 0 || input->xvalue(0, 1) < 0)
			{
				speed.setX(offset * input->xvalue(0,1));
			}
			else if (input->yvalue(0, 1) > 0 || input->yvalue(0, 1) < 0)
			{
				speed.setY(offset * input->yvalue(0,1));
			}
			else if (input->xvalue(0, 2) > 0 || input->xvalue(0, 2) < 0)
			{
				speed.setX(offset * input->xvalue(0,2));
			}
			else if (input->yvalue(0, 2) > 0 || input->yvalue(0, 2) < 0)
			{
				speed.setY(offset * input->yvalue(0,2));
			}
		}
	}
	virtual void update() {
		
		transform->setVel(speed);
		speed = Vector(0,0);
	}
};


