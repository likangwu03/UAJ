#pragma once
#include "../Structure/Component.h"
class Texture;
class ClockComponent;
using namespace std;

class TimeOfDay : public Component {
private:
	const int AFTERNOON = 130, NIGHT = 230, END = 360;
	Texture* afternoon;
	Texture* night;
	Texture* topTexture;

public:
	TimeOfDay(Texture* aftTexture, Texture* nightTexture, GameObject* parent);
	void update();
	void render();
};