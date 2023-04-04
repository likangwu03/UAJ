#include "TimeOfDay.h".h"

#include "../structure/GameManager.h"
#include "../Scenes/Restaurant.h"
#include "../Components/ClockComponent.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/checkML.h"

TimeOfDay::TimeOfDay(Texture* aftTexture, Texture* nightTexture, GameObject* parent) :Component(parent,_ecs::cmp_INVALID), topTexture(nullptr),
	afternoon(aftTexture), night(nightTexture) {}

void TimeOfDay::update() {
	if (ClockComponent::get()->getRotation() >= AFTERNOON && ClockComponent::get()->getRotation() <= NIGHT)
		topTexture = afternoon;
	else if (ClockComponent::get()->getRotation() >= NIGHT)
		topTexture = night;
	else 
		topTexture = nullptr;
}

void TimeOfDay::render() {
	if (topTexture != nullptr) {
		topTexture->render( build_sdlrect( 0, 0, topTexture->width() * sdlutils().getResizeFactor(), topTexture->height() * sdlutils().getResizeFactor()));
	}
}
