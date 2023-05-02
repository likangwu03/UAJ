#include "PantryExitTrigger.h"
#include "../Structure/GameManager.h"
#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "../Scenes/GameScenes/Restaurant.h"
#include "Transform.h"
#include "../Scenes/GameScenes/Restaurant.h"
#include "Image.h"
#include "../Utilities/checkML.h"

PantryExitTrigger::PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_),
doorSound(&sdlutils().soundEffects().at("OPEN_DOOR")),
sdl(SDLUtils::instance()), pantryMusic(&sdl->musics().at("PANTRY_MUSIC")), restaurantMusic(&sdl->musics().at("RESTAURANT_MUSIC")) {
	gm = GameManager::get();
	playerPantry = parent->getScene()->getGameObject(_ecs::hdr_PLAYER);
	otherPPantryObj = parent->getScene()->getGameObject(_ecs::hdr_OTHERPLAYER);
	otherPPantryComp = otherPPantryObj->getComponent<OtherPlayerComp>();
	playerRestaurant = gm->getRestaurant()->getGameObject(_ecs::hdr_PLAYER);
	otherPRestObj = gm->getRestaurant()->getGameObject(_ecs::hdr_OTHERPLAYER);
	playerRestaurantTransform = playerRestaurant->getComponent<Transform>();
	image = parent->getComponent<Image>();
	image->setActive(false);
	pantryMusic->setMusicVolume(MUSIC_VOL);
	restaurantMusic->setMusicVolume(MUSIC_VOL);
}

void PantryExitTrigger::isOverlapping() {
	image->setActive(true);
	if ((ih->isKeyDown(SDLK_SPACE) || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A))) && GameManager::get()->canChangeScene()) {
		// se desactiva el jugador de la despensa
		playerPantry->setActives(false);
		otherPPantryObj->setActives(false);
		otherPPantryComp->sceneOut();
		// se cambia al restaurant
		gm->changeScene(gm->getScene(_ecs::sc_RESTAURANT));
		doorSound->play();
		pantryMusic->pauseMusic();
		restaurantMusic->play(-1);
		// se activa el jugador del restaurante y se recoloca
		playerRestaurant->setActives(true);
		otherPRestObj->setActives(true);
		playerRestaurantTransform->setPos(RESTAURANT_POS);
		playerRestaurantTransform->setOrientation(south);
	}
}

void PantryExitTrigger::onTriggerExit() {
	image->setActive(false);
}