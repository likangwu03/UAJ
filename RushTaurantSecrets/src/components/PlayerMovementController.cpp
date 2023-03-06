#include "PlayerMovementController.h"

PlayerMovementController::PlayerMovementController(GameObject* parent) : Component(parent, id) {
	transform = parent->getComponent<Transform>();
	input = InputHandler::instance();
	if (!input->joysticksInitialised()) {
		input->initialiseJoysticks(_joy);
		controller = SDL_JoystickName(_joy);
	}
	keyboard = input->getControls();
}

PlayerMovementController::~PlayerMovementController() {
	input->clean();
}

void PlayerMovementController::handleEvents() {
	// Descomentar si se quiere comprobar el binding de un mando
	/*gamecont = SDL_GameControllerOpen(0);
	std::cout << SDL_GameControllerMapping(gamecont) << std::endl;*/
	if (input->joysticksInitialised() && !keyboard)
	{
		input->refresh();
		// eje x mando 1
		if ((input->xvalue(0, 1) > 0 || input->xvalue(0, 1) < 0) && !input->keyDownEvent()) {
			speed.setX(offset * input->xvalue(0, 1));
			transform->setMovState(walking);
			if (input->xvalue(0, 1) < 0)
				transform->setOrientation(west);
			else
				transform->setOrientation(east);
		}
		// eje y mando 1
		else if (input->yvalue(0, 1) > 0 || input->yvalue(0, 1) < 0 && !input->keyDownEvent()) {
			speed.setY(offset * input->yvalue(0, 1));
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
			if (input->getHatEvent()) {
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
			}
			else input->setFalseJoyhat();
		}
		else { // PS4 Controller
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
	if (input->keyDownEvent()) {
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		// arriba
		if (input->isKeyDown(SDL_SCANCODE_W)) {
			moveUp();
		}
		// izquierda
		if (input->isKeyDown(SDL_SCANCODE_A)) {
			moveLeft();
		}
		// derecha
		if (input->isKeyDown(SDL_SCANCODE_D)) {
			moveRight();
		}
		// abajo
		if (input->isKeyDown(SDL_SCANCODE_S)) {
			moveDown();
		}
	}
}

void PlayerMovementController::update() {
	if (!nonKeyPressed() && input->keyUpEvent()) {
		speed = Vector(0, 0);
		transform->setMovState(idle);
	}
	transform->setVel(speed);
	if (input->joysticksInitialised() && !keyboard) {
		speed = Vector(0, 0);
	}
}

bool PlayerMovementController::nonKeyPressed() {
	bool pressed = false;
	if (!input->joysticksInitialised() || keyboard) {
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_S])
		{
			moveDown();
			pressed = true;
		}
		if (currentKeyStates[SDL_SCANCODE_D])
		{
			moveRight();
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
	if (input->joysticksInitialised()) {
		if (std::string(controller) == "Controller (Xbox One For Windows)") {
			if (input->getHatEvent()) {
				// abajo
				if (input->getHatState(DOWN)) {
					moveDown();
					pressed = true;
				}
				// arriba		
				if (input->getHatState(UP)) {
					moveUp();
					pressed = true;
				}
				// izquierda
				if (input->getHatState(LEFT)) {
					moveLeft();
					pressed = true;
				}
				// derecha
				if (input->getHatState(RIGHT)) {
					moveRight();
					pressed = true;
				}
			}
			else
				input->setFalseJoyhat();
			return pressed;
		}
	}
	else
		return true;
}

void PlayerMovementController::moveUp() {
	speed = Vector(0, 0);
	speed.setY(-offset);
	transform->setOrientation(north);
	transform->setMovState(walking);
}

void PlayerMovementController::moveDown() {
	speed = Vector(0, 0);
	speed.setY(offset);
	transform->setOrientation(south);
	transform->setMovState(walking);
}

void PlayerMovementController::moveRight() {
	speed = Vector(0, 0);
	speed.setX(offset);
	transform->setOrientation(east);
	transform->setMovState(walking);
}

void PlayerMovementController::moveLeft() {
	speed = Vector(0, 0);
	speed.setX(-offset);
	transform->setOrientation(west);
	transform->setMovState(walking);
}
