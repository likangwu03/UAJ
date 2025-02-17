#pragma once

#include "../Structure/Component.h"
#include "Image.h"
#include "../Managers/ThievesManager.h"

class Warning : public Component {
private:
	Image* image;
	ThievesManager* thiefsManager;
	float elapsedTime;
	const float TIMER = 400;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_WARNING;

	Warning(GameObject* parent) :
		Component(parent, id), thiefsManager(ThievesManager::get()), elapsedTime(0) {
		image = parent->getComponent<Image>();
	}

	virtual void update();

	virtual void nextDay();
};