#include "PlayerMovementController.h"

PlayerMovementController::PlayerMovementController(GameObject* parent, _ecs::id_type id) : Component(parent, id) {}

void PlayerMovementController::handleEvents() {
	input->refresh();
	if (input->controllerXEvent()) {
		//Left of dead zone
		if (input->controllerInput().first < -JOYSTICK_DEAD_ZONE)
		{
			dir = Vector2D(-dirSign, 0);
			std::cout << "hola" << std::endl;
		}
		//Right of dead zone
		else if (input->controllerInput().first > JOYSTICK_DEAD_ZONE)
		{
			dir = Vector2D(dirSign, 0);
		}
	}
	if (input->controllerYEvent()) {

		if (input->controllerInput().second < -JOYSTICK_DEAD_ZONE)
		{
			dir = Vector2D(0, -dirSign);
		}
		//Above of dead zone
		else if (input->controllerInput().second > JOYSTICK_DEAD_ZONE)
		{
			dir = Vector2D(0, dirSign);
		}
	}
}

void PlayerMovementController::update() {
	if (dir.getX() > 0) // derecha
		pos = pos + Vector2D(speed, 0);
	else if (dir.getX() < 0) // izquierda
		pos = pos + Vector2D(-speed, 0);
	else if (dir.getY() < 0) // abajo
		pos = pos + Vector2D(0, -speed);
	else if (dir.getY() > 0) // arriba
		pos = pos + Vector2D(0, speed);
	dir = Vector2D(0, 0);
}