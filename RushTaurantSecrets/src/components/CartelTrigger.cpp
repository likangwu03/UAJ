#include "CartelTrigger.h"
#include "../utils/checkML.h"
#include "../structure/CartelManager.h"
#include "../scenes/SuperMarket.h"

CartelTrigger::CartelTrigger(GameObject* parent, _ecs::_ingredients_id id, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_), ingId(id), highlighted(false),
	cartelManager(static_cast<SuperMarket*>(parent->getScene())->getCartelManager())
{
	unHighlight();
}
void CartelTrigger::isOverlapping() {
	if (!highlighted) return; //si no es aprobado por cartelManager
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return;
	//abrir el hud
	cartelManager->openMenu();
}
void CartelTrigger::onTriggerEnter() {
	cartelManager->signIn(this);
}
void CartelTrigger::onTriggerExit() {
	cartelManager->signOut(this);
	cartelManager->closeMenu();
}
void CartelTrigger::highlight() {
	parent->setActive<Image>(highlighted = true);
}
void CartelTrigger::unHighlight() {
	parent->setActive<Image>(highlighted = false);
}