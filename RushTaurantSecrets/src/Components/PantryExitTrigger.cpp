#include "PantryExitTrigger.h"
#include "../Structure/GameManager.h"
#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "../Scenes/Restaurant.h"
#include "Transform.h"
#include "../Scenes/Restaurant.h"
#include "Image.h"
#include "../Utilities/checkML.h"

PantryExitTrigger::PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_),
doorSound(&sdlutils().soundEffects().at("OPEN_DOOR")) {
	gm = GameManager::get();
	playerPantry = parent->getScene()->getGameObject(_ecs::hdr_PLAYER);
	playerRestaurant = gm->getRestaurant()->getGameObject(_ecs::hdr_PLAYER);
	playerRestaurantTransform = playerRestaurant->getComponent<Transform>();
	image = parent->getComponent<Image>();
	image->setActive(false);
}

void PantryExitTrigger::isOverlapping() {
	image->setActive(true);
	if (ih->isKeyDown(SDLK_SPACE) || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A))) {
		// se desactiva el jugador de la despensa
		playerPantry->setActives(false);
		// se cambia al restaurant
		gm->changeScene(gm->getRestaurant());
		doorSound->play();
		// se activa el jugador del restaurante y se recoloca
		playerRestaurant->setActives(true);
		playerRestaurantTransform->setPos(RESTAURANT_POS);
		playerRestaurantTransform->setOrientation(south);
	}
}

void PantryExitTrigger::onTriggerExit() {
	image->setActive(false);
}