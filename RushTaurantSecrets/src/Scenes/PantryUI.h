#pragma once
#include "../Structure/Scene.h"
#include "../GameObjects/Clock.h"

class PantryUI : public Scene
{
private:
	Clock* clock;

public:
	PantryUI() { clock = new Clock(this); };
};