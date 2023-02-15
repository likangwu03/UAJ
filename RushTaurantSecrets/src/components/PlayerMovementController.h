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
			// eje x mando 1
			if (input->xvalue(0, 1) > 0 || input->xvalue(0, 1) < 0)
			{
				speed.setX(offset * input->xvalue(0,1));
			}
			// eje y mando 1
			else if (input->yvalue(0, 1) > 0 || input->yvalue(0, 1) < 0)
			{
				speed.setY(offset * input->yvalue(0,1));
			}
			//// eje x mando 2
			//else if (input->xvalue(0, 2) > 0 || input->xvalue(0, 2) < 0)
			//{
			//	speed.setX(offset * input->xvalue(0,2));
			//}
			//// eje y mando 2
			//else if (input->yvalue(0, 2) > 0 || input->yvalue(0, 2) < 0)
			//{
			//	speed.setY(offset * input->yvalue(0,2));
			//}
		}
		if (input->joysticksInitialised())
		{
			// derecha
			if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) 
				speed.setX(offset);
			// izquierda
			else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) 
				speed.setX(-offset);
			// arriba		
			else if(input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP))
				speed.setY(-offset);
			// abajo
			else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) 
				speed.setY(offset);
		}
	}
	virtual void update() {
		
		transform->setVel(speed);
		speed = Vector(0,0);
	}
};


