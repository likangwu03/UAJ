#pragma once
#include "SDL.h"
#include <iostream>
#include "../structure/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../structure/GameObject.h"
#include "Transform.h"

const int JOYSTICK_DEAD_ZONE = 9000;

class PlayerMovementController : public Component
{
private:
	int speed = 10;

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
		if (input->getControllerXEvent()) {
			//Left of dead zone
			if (input->controllerInput() < -JOYSTICK_DEAD_ZONE)
			{
				transform->setVel(Vector(-speed, 0));
			}
			//Right of dead zone
			else if (input->controllerInput() > JOYSTICK_DEAD_ZONE)
			{
				transform->setVel(Vector(speed, 0));
			}
			else
				transform->setVel(Vector(0, 0));
		}
		if (input->getControllerYEvent()) {
			if (input->controllerInput() < -JOYSTICK_DEAD_ZONE)
			{
				transform->setVel(Vector(0, -speed));
			}
			//Above of dead zone
			else if (input->controllerInput() > JOYSTICK_DEAD_ZONE)
			{
				transform->setVel(Vector(0, speed));
			}
			else
				transform->setVel(Vector(0, 0));
		}
		input->setControllerXEvent(false);
		input->setControllerYEvent(false);
	}
	virtual void update() {
		//if (transform->getVel().getX() > 0) // derecha
		//	transform->getPos() = transform->getPos() + Vector(speed, 0);
		//else if (transform->getVel().getX() < 0) // izquierda
		//	transform->getPos() = transform->getPos() + Vector(-speed, 0);
		//else if (transform->getVel().getY() < 0) // abajo
		//	transform->getPos() = transform->getPos() + Vector(0, -speed);
		//else if (transform->getVel().getY() > 0) // arriba
		//	transform->getPos() = transform->getPos() + Vector(0, speed);
		//transform->getVel() = Vector(0, 0);
	}
};


