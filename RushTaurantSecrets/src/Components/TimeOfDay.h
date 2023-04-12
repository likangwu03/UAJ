#pragma once
#include "../Structure/Component.h"
class Texture;
class ClockComponent;
using namespace std;

class TimeOfDay : public Component {
private:
	const int DAY = 15, AFTERNOON = 130, NIGHT = 230, END = 360;
	const float INC_OPAC_AFT = AFTERNOON / 100.0f, INC_OPAC_NIGHT = (NIGHT-AFTERNOON) / 100.0f;
	
	ClockComponent* clock;
	Texture* afternoon;
	Texture* night;
	Texture* topTexture; 
	bool isAfternoon, isNight;
	int lastDeg;
	float currOpac;

public:
	TimeOfDay(Texture* aftTexture, Texture* nightTexture, GameObject* parent);
	void update();
	void render();
};