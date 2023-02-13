#pragma once
#include "SDL.h"
#include <iostream>
#include "src/utils/Vector2D.h"

class PlayerMovementController
{
private: // movimiento erratico aún
	int speed = 5;
	int JOYSTICK_DEAD_ZONE = 8000; // quizá gestionar con PlayerInputManager
	SDL_Joystick* gameController = NULL; // quizá gestionar con PlayerInputManager

	int dirSign;
	Vector2D dir;
	Vector2D pos; // deberá pertenecer al transform de player
public:
	PlayerMovementController() {
		//Cargar gameController
		gameController = SDL_JoystickOpen(0);
		if (gameController == NULL)
		{
			printf("Warning: Error al cargar el controller \n", SDL_GetError());
		}
	}
	~PlayerMovementController() {
		//Cerrar gameController
		SDL_JoystickClose(gameController);
		gameController = NULL;
	}

	void handleEvents(SDL_Event event) {
		if (event.type == SDL_JOYAXISMOTION) { // quizá añadir un else para colocar a 0 el input y no hacerlo en el update
			if (event.jaxis.axis == 0) { // x
				//Left of dead zone
				if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					dir = Vector2D(-dirSign, 0);
				}
				//Right of dead zone
				else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					dir = Vector2D(dirSign, 0);
				}
			}
			if (event.jaxis.axis == 1) { // y
				//Below of dead zone
				if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					dir = Vector2D(0, -dirSign);
				}
				//Above of dead zone
				else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					dir = Vector2D(0, dirSign);
				}
			}
		}
	}
	void update() {
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
};

