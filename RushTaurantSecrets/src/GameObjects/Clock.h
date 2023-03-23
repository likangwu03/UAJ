#pragma once
#include "../Structure/GameObject.h"
#include "../Components/ClockComponent.h"

class Clock : public GameObject {
private:

public:
	Clock(Scene* scene) : GameObject(scene, _ecs::grp_ICONS, _ecs::hdr_CLOCK) {
		new ClockComponent(this);
	}
};