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
	Vector speed = (0,0);
	Vector aux = speed;

	Transform* transform = nullptr;
	InputHandler* input;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	PlayerMovementController(GameObject* parent) : Component(parent, id) {
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
			// eje x mando 1
			if (input->xvalue(0, 1) > 0 || input->xvalue(0, 1) < 0) {
				speed.setX(offset * input->xvalue(0,1));
				transform->setMovState(walking);
				if (input->xvalue(0, 1) < 0)
					transform->setOrientation(west);
				else
					transform->setOrientation(east);
			}
			// eje y mando 1
			else if (input->yvalue(0, 1) > 0 || input->yvalue(0, 1) < 0) {
				speed.setY(offset * input->yvalue(0,1));
				transform->setMovState(walking);
				if (input->yvalue(0, 1) < 0)
					transform->setOrientation(north);
				else
					transform->setOrientation(south);
			}
			else if (input->xvalue(0, 1) == 0 && input->yvalue(0, 1) == 0) {
				transform->setMovState(idle);
			}
			if (input->numButtons() >= 11) {
				// derecha
				if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
					transform->setMovState(walking);
					speed.setX(offset);
					transform->setOrientation(east);
				}
				// izquierda
				else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
					transform->setMovState(walking);
					speed.setX(-offset);
					transform->setOrientation(west);
				}
				// arriba		
				else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
					transform->setMovState(walking);
					speed.setY(-offset);
					transform->setOrientation(north);
				}
				// abajo
				else if (input->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
					transform->setMovState(walking);
					speed.setY(offset);
					transform->setOrientation(south);
				}
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
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			// arriba
			if (input->isKeyDown(SDL_SCANCODE_W)) {
				speed = Vector(0, 0);
				speed.setY(-offset);
				transform->setOrientation(north);
				transform->setMovState(walking);
			}
			// izquierda
			if (input->isKeyDown(SDL_SCANCODE_A)) {
				speed = Vector(0, 0);
				speed.setX(-offset);
				transform->setOrientation(west);
				transform->setMovState(walking);
			}
			// abajo
			if (input->isKeyDown(SDL_SCANCODE_S)) {
				speed = Vector(0, 0);
				speed.setY(offset);
				transform->setOrientation(south);
				transform->setMovState(walking);
			}
			// derecha
			if (input->isKeyDown(SDL_SCANCODE_D)) {
				speed = Vector(0, 0);
				speed.setX(offset);
				transform->setOrientation(east);
				transform->setMovState(walking);
			}

		}
	}
	virtual void update() {
		if (input->joysticksInitialised() || (!nonKeyPressed() && input->keyUpEvent())) {
			speed = Vector(0, 0);
			transform->setMovState(idle);
		}	
		input->refresh();
		transform->setVel(speed);
	}

	bool nonKeyPressed() {
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		bool pressed = false;
		if (currentKeyStates[SDL_SCANCODE_D])
		{
			speed = Vector(0, 0);
			speed.setX(offset);
			transform->setOrientation(east);
			transform->setMovState(walking);
			pressed = true;
		}
		if (currentKeyStates[SDL_SCANCODE_S])
		{
			speed = Vector(0, 0);
			speed.setY(offset);
			transform->setOrientation(south);
			transform->setMovState(walking);
			pressed = true;
		}
		if (currentKeyStates[SDL_SCANCODE_A])
		{
			speed = Vector(0, 0);
			speed.setX(-offset);
			transform->setOrientation(west);
			transform->setMovState(walking);
			pressed = true;
		}
		if (currentKeyStates[SDL_SCANCODE_W])
		{
			speed = Vector(0, 0);
			speed.setY(-offset);
			transform->setOrientation(north);
			transform->setMovState(walking);
			pressed = true;
		}	
		//return (currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_D]);
		return pressed;
	}
};


