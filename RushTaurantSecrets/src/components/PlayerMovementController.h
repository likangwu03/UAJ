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
	int offset = 6;
	bool key = false;
	Vector speed = (0,0);
	Vector aux = speed;

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
		if (input->joysticksInitialised())
		{
			input->refresh();
			// eje x mando 1
			if (input->xvalue(0, 1) > 0 || input->xvalue(0, 1) < 0)
				speed.setX(offset * input->xvalue(0,1));
			// eje y mando 1
			else if (input->yvalue(0, 1) > 0 || input->yvalue(0, 1) < 0)
				speed.setY(offset * input->yvalue(0,1));
			else if (input->numButtons() >= 11) {
				// derecha
				if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
					speed.setX(offset);
				// izquierda
				else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
					speed.setX(-offset);
				// arriba		
				else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP))
					speed.setY(-offset);
				// abajo
				else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
					speed.setY(offset);
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
		else if (input->keyDownEvent()){
			key = true;
			// arriba
			if (input->isKeyDown(SDLK_w))
				speed.setY(-offset);
			// izquierda
			else if (input->isKeyDown(SDLK_a))
				speed.setX(-offset);
			// abajo
			else if (input->isKeyDown(SDLK_s))
				speed.setY(offset);
			// derecha
			else if (input->isKeyDown(SDLK_d))
				speed.setX(offset);
		}
	}
	virtual void update() {	
		transform->setVel(speed);
		if (input->keyUpEvent())
			key = false;
		if (!key || (speed.getX() - aux.getX() != 0 && speed.getY() - aux.getY() != 0)) {
			speed = Vector(0, 0);
			aux = speed;
		}
	}
};


