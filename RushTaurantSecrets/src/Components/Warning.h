#pragma once

#include "../Structure/Component.h"
#include "Image.h"
#include "../Managers/ThiefsManager.h"

class Warning : public Component {
private:
	Image* image;
	ThiefsManager* thiefsManager;
	float elapsedTime;
	const float TIMER=400;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_WARNING;

	Warning(GameObject* parent) :
		Component(parent, id), thiefsManager(ThiefsManager::get()), elapsedTime(0) {
		image = parent->getComponent<Image>();
	}

	virtual void update() {
		if (thiefsManager->isThereThieves()) {
			elapsedTime += deltaTime;
			if (elapsedTime > TIMER) {
				elapsedTime = 0;
				image->setActive(!image->isActive());
			}
		}
		else {
			image->setActive(false);
		}
	}
	virtual void nextDay() {
		thiefsManager->stopSound();
	}
};