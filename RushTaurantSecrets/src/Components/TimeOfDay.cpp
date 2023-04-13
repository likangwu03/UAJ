#include "TimeOfDay.h".h"

#include "../structure/GameManager.h"
#include "../Components/ClockComponent.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/checkML.h"

TimeOfDay::TimeOfDay(Texture* aftTexture, Texture* nightTexture, GameObject* parent) : 
	Component(parent, _ecs::cmp_INVALID), afternoon(aftTexture), night(nightTexture), lastDeg(0), aftOpac(0), nightOpac(0), isAfternoon(false), isNight(false) {

	clock = ClockComponent::get();
}

void TimeOfDay::update() {
	if (clock->getRotation() < DAY) {
		isAfternoon = false;
		isNight = false;
		aftOpac = 0;
		nightOpac = 0;
	}
	else if (clock->getRotation() >= DAY && clock->getRotation() && !isAfternoon)
		isAfternoon = true;
	else if (clock->getRotation() >= AFTERNOON && !isNight) 
		isNight = true;
}

void TimeOfDay::render() {
	if (isAfternoon && !isNight) {
		afternoon->setOpacity(aftOpac);
		afternoon->render(build_sdlrect(0, 0, afternoon->width() * sdlutils().getResizeFactor(), afternoon->height() * sdlutils().getResizeFactor()));
		if (aftOpac < 100)
			aftOpac += INC_OPAC_AFT;
		else aftOpac = 100;
	}
	else if (isNight) {
		afternoon->setOpacity(aftOpac);
		afternoon->render(build_sdlrect(0, 0, afternoon->width() * sdlutils().getResizeFactor(), afternoon->height() * sdlutils().getResizeFactor()));
		if (aftOpac > 0)
			aftOpac -= INC_OPAC_AFT;
		else aftOpac = 0;

		night->setOpacity(nightOpac);
		night->render(build_sdlrect(0, 0, night->width() * sdlutils().getResizeFactor(), night->height() * sdlutils().getResizeFactor()));
		if (nightOpac < 100)
			nightOpac += INC_OPAC_NIGHT;
		else nightOpac = 100;
	}

}