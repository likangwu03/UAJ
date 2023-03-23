#pragma once
#include "SDL.h"
#include <iostream>
#include "../Structure/Component.h"
#include "../Utilities/InputHandler.h"
#include "../Structure/GameObject.h"
#include "../Definitions/Structure_def.h"
#include "Transform.h"
#include <string>

enum DPAD_XBOX { UP, DOWN, RIGHT, LEFT };

class PlayerMovementController : public Component
{
private:
	int offset = 6;
	bool keyboard;
	Vector speed = (0,0);
	Vector aux = speed;

	int player; // num de player

	SDL_Joystick* _joy;
	const char* controller = "";
	bool xbox;
	SDL_GameController* gamecont = nullptr;

	Transform* transform = nullptr;
	InputHandler* input;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	PlayerMovementController(GameObject* parent, int _player);
	~PlayerMovementController();

	// cleon: no sé si es aquí, pero frametime. frametime es felicidad. frametime es maravilloso. frametime, por lo visto, es vuestro padre (no son mis palabras).
	virtual void handleEvents();
	virtual void update();

	bool nonKeyPressed();

	void initP();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	const char* getControllerType();
};