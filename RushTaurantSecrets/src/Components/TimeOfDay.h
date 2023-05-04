#pragma once
#include "../Structure/Component.h"
class Texture;
class ClockComponent;
using namespace std;

class TimeOfDay : public Component {
private:
	const int DAY = 15, AFTERNOON = 130, NIGHT = 230, END = 360;
	float increaseOpac;

	ClockComponent* clock;
	Texture* afternoonTxt;
	Texture* nightTxt;
	bool isAfternoon, isNight;
	float aftOpac, nightOpac;

public:
	TimeOfDay(Texture* aftTexture, Texture* nightTexture, GameObject* parent);
	void update();
	void render();
};