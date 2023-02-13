#pragma once
#include "SDL.h"
#include <iostream>
#include "../utils/Vector2D.h"
#include "../structure/Component.h"
#include "../sdlutils/InputHandler.h"

class PlayerMovementController : public Component
{
private:
	int speed = 5;

	InputHandler* input = InputHandler::instance();;

	int dirSign;
	Vector2D dir;
	Vector2D pos;
public:
	PlayerMovementController(GameObject* parent, _ecs::id_type id);
	~PlayerMovementController() { }
	virtual void handleEvents();
	virtual void update();
};


