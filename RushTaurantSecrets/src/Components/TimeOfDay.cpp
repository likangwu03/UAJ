#include "TimeOfDay.h".h"

#include "../structure/GameManager.h"
#include "../Components/ClockComponent.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/checkML.h"

TimeOfDay::TimeOfDay(Texture* aftTexture, Texture* nightTexture, GameObject* parent) : 
	Component(parent, _ecs::cmp_INVALID), topTexture(nullptr), afternoon(aftTexture), night(nightTexture), lastDeg(0), currOpac(0), isAfternoon(false), isNight(false) {

	clock = ClockComponent::get();
}

void TimeOfDay::update() {
	if (clock->getRotation() < DAY && !isAfternoon && !isNight) {
		topTexture = nullptr;
		isAfternoon = false;
		isNight = false;
		currOpac = 0;
	}
	else if (clock->getRotation() >= DAY && clock->getRotation() && !isAfternoon) {
 		topTexture = afternoon;
		isAfternoon = true;
		currOpac = 0;
	}
	else if (clock->getRotation() >= AFTERNOON && !isNight) {
		topTexture = night;
		isNight = true;
		currOpac = 0;
	}
}

void TimeOfDay::render() {
	if (topTexture != nullptr) {
 		topTexture->setOpacity(currOpac);
		topTexture->render(build_sdlrect(0, 0, topTexture->width() * sdlutils().getResizeFactor(), topTexture->height() * sdlutils().getResizeFactor()));
		
		if (currOpac < 100) {
			if (topTexture == afternoon)
				currOpac += INC_OPAC_AFT;
			else if (topTexture == night)
				currOpac += INC_OPAC_NIGHT;
		}
	}
}