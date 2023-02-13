#pragma once
#include "SDL.h"
#include <iostream>
#include "../../src/utils/Vector2D.h"

class PlayerMovementController
{
private:
	int speed;
	Vector2D pos;
public:
	void handleEvents(SDL_Event event) {
		if (event.type == SDL_JOYAXISMOTION) {
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
		if (dir.getX() > 0 && pos.getX() + width < game->getGameConfig().WIN_WIDTH - game->getGameConfig().WALL_WIDTH) // derecha
			pos = pos + Vector2D(dis, 0);
		else if (dir.getX() < 0 && pos.getX() > game->getGameConfig().WALL_WIDTH) // izquierda
			pos = pos + Vector2D(-dis, 0);
		else if ()

		else if ()

			dir = Vector2D(0, 0);
	}

	void move() {

	}

};

