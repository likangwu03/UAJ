#pragma once
#include "SDL.h"
#include <iostream>
#include "../structure/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../structure/GameObject.h"
#include "../structure/Structure_def.h"
#include "Transform.h"
#include <string>

enum DPAD_XBOX { UP, DOWN, RIGHT, LEFT};

class PlayerMovementController : public Component
{
private:
	int offset = 6;
	Vector speed = (0,0);
	Vector aux = speed;

	SDL_Joystick* _joy;
	const char* controller;
	SDL_GameController* gamecont = nullptr;

	Transform* transform = nullptr;
	InputHandler* input;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	PlayerMovementController(GameObject* parent) : Component(parent, id) {
		transform = parent->getComponent<Transform>();
		input = InputHandler::instance();
		if(input->joysticksInitialised())
			input->initialiseJoysticks(_joy);
		controller = SDL_JoystickName(_joy);
	}
	~PlayerMovementController() { 
		input->clean();
	}
	virtual void handleEvents() {	
		// Descomentar si se quiere comprobar el binding de un mando
		/*gamecont = SDL_GameControllerOpen(0);
		std::cout << SDL_GameControllerMapping(gamecont) << std::endl;*/
		if (input->joysticksInitialised())
		{
			input->refresh();
			// eje x mando 1
			if ((input->xvalue(0, 1) > 0 || input->xvalue(0, 1) < 0) && !input->keyDownEvent()) {
				speed.setX(offset * input->xvalue(0,1));
				transform->setMovState(walking);
				if (input->xvalue(0, 1) < 0)
					transform->setOrientation(west);
				else
					transform->setOrientation(east);
			}
			// eje y mando 1
			else if (input->yvalue(0, 1) > 0 || input->yvalue(0, 1) < 0 && !input->keyDownEvent()) {
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
			if (std::string(controller) == "Controller (Xbox One For Windows)") {
				// derecha
				if (input->getHatState(RIGHT)) {
					moveRight();
				}
				// izquierda
				if (input->getHatState(LEFT)) {
					moveLeft();
				}
				// arriba		
				if (input->getHatState(UP)) {
					moveUp();
				}
				// abajo
				if (input->getHatState(DOWN)) {
					moveDown();
				}		
				input->setFalseJoyhat();
			}
			else {
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
				moveUp();
			}
			// izquierda
			if (input->isKeyDown(SDL_SCANCODE_A)) {
				moveLeft();
			}
			// abajo
			if (input->isKeyDown(SDL_SCANCODE_S)) {
				moveDown();
			}
			// derecha
			if (input->isKeyDown(SDL_SCANCODE_D)) {
				moveRight();
			}
		}
	}
	virtual void update() {
		if (!nonKeyPressed() && input->keyUpEvent()) {
			speed = Vector(0, 0);
			transform->setMovState(idle);
		}	
		transform->setVel(speed);
		if (input->joysticksInitialised()) {		
			speed = Vector(0, 0);
		}
	}

	bool nonKeyPressed() {
		if (!input->joysticksInitialised()) {
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			bool pressed = false;
			if (currentKeyStates[SDL_SCANCODE_D])
			{
				moveRight();
				pressed = true;
			}
			if (currentKeyStates[SDL_SCANCODE_S])
			{
				moveDown();
				pressed = true;
			}
			if (currentKeyStates[SDL_SCANCODE_A])
			{
				moveLeft();
				pressed = true;
			}
			if (currentKeyStates[SDL_SCANCODE_W])
			{
				moveUp();
				pressed = true;
			}
			//return (currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_D]);
			return pressed;
		}
		else
			return true;
	}

	void moveUp() {
		speed = Vector(0, 0);
		speed.setY(-offset);
		transform->setOrientation(north);
		transform->setMovState(walking);
	}

	void moveDown() {
		speed = Vector(0, 0);
		speed.setY(offset);
		transform->setOrientation(south);
		transform->setMovState(walking);
	}

	void moveRight() {
		speed = Vector(0, 0);
		speed.setX(offset);
		transform->setOrientation(east);
		transform->setMovState(walking);
	}

	void moveLeft() {
		speed = Vector(0, 0);
		speed.setX(-offset);
		transform->setOrientation(west);
		transform->setMovState(walking);
	}
};




