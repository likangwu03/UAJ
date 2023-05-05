#include "CartelTrigger.h"
#include "../Utilities/checkML.h"
#include "../Managers/CartelManager.h"

#include "../Structure/GameManager.h"
#include "../Scenes/GameScenes/SuperMarket.h"

CartelTrigger::CartelTrigger(GameObject* parent, _ecs::_ingredients_id id, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_), ingId(id), highlighted(false),
	cartelManager(GameManager::get()->getSupermarket()->getCartelManager())
{
	unHighlight();
}
void CartelTrigger::isOverlapping() {
	if (!highlighted) return; //si no es aprobado por cartelManager
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) return;
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