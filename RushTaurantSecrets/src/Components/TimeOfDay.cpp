#include "TimeOfDay.h".h"

#include "../structure/GameManager.h"
#include "../Components/ClockComponent.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/checkML.h"

TimeOfDay::TimeOfDay(Texture* aftTexture, Texture* nightTxtTexture, GameObject* parent) :
	Component(parent, _ecs::cmp_INVALID), afternoonTxt(aftTexture), nightTxt(nightTxtTexture), increaseOpac(0),
	lastDeg(0), aftOpac(0), nightOpac(0), isAfternoon(false), isNight(false)
{
	clock = ClockComponent::get();
	increaseOpac = (100.0f / clock->timeToReachDeg(AFTERNOON)) * 10;
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
		afternoonTxt->setOpacity(aftOpac);
		afternoonTxt->render(build_sdlrect(0, 0, afternoonTxt->width() * sdlutils().getResizeFactor(), afternoonTxt->height() * sdlutils().getResizeFactor()));
		if (aftOpac < 100)
			aftOpac += increaseOpac;
		else aftOpac = 100;
	}
	else if (isNight) {
		afternoonTxt->setOpacity(aftOpac);
		afternoonTxt->render(build_sdlrect(0, 0, afternoonTxt->width() * sdlutils().getResizeFactor(), afternoonTxt->height() * sdlutils().getResizeFactor()));
		if (aftOpac > 0)
			aftOpac -= increaseOpac;
		else aftOpac = 0;

		nightTxt->setOpacity(nightOpac);
		nightTxt->render(build_sdlrect(0, 0, nightTxt->width() * sdlutils().getResizeFactor(), nightTxt->height() * sdlutils().getResizeFactor()));
		if (nightOpac < 100)
			nightOpac += increaseOpac;
		else nightOpac = 100;
	}
	lastDeg = clock->getRotation();
}