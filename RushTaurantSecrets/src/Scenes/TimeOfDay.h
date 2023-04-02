#pragma once

#include "../Structure/Scene.h"
class Texture;
class ClockComponent;
using namespace std;

class TimeOfDay : public Scene {
private:
	const int AFTERNOON = 130, NIGHT = 230, END = 360;
	Texture* afternoon;
	Texture* night;
	Texture* topTexture;

	ClockComponent* clock;
	
public:
	TimeOfDay(Texture* aftTexture, Texture* nightTexture);
	void update();
	void render();
};