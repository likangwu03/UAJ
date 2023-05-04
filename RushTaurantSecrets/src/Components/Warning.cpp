#include "Warning.h"

void Warning::update() {
	if (thiefsManager->areThereThieves()) {
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

void Warning::nextDay() {
	thiefsManager->haltSound();
}