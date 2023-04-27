#pragma once
#include "../../Structure/Scene.h"
#include "../../GameObjects/Clock.h"

class UIPantry : public Scene
{
private:
	Clock* clock;

public:
	UIPantry() { clock = new Clock(this); };
};