#include "GoToPantryTrigger.h"
#include "../Utilities/InputHandler.h"
#include "../Structure/GameManager.h"
#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "../Scenes/GameScenes/Pantry.h"
#include "../Components/Image.h"
#include "Transform.h"
#include "../Utilities/checkML.h"

GoToPantryTrigger::GoToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_),
	doorSound(&sdlutils().soundEffects().at("OPEN_DOOR")),
	sdl(SDLUtils::instance()), pantryMusic(&sdl->musics().at("PANTRY_MUSIC")), restaurantMusic(&sdl->musics().at("RESTAURANT_MUSIC")) {
	gm = GameManager::get();
	playerRestaurant = parent->getScene()->getGameObject(_ecs::hdr_PLAYER);
	otherPRestObj = parent->getScene()->getGameObject(_ecs::hdr_OTHERPLAYER);
	otherPRestComp = otherPRestObj->getComponent<OtherPlayerComp>();
	playerPantry = gm->getPantry()->getGameObject(_ecs::hdr_PLAYER);
	otherPPantryObj = gm->getPantry()->getGameObject(_ecs::hdr_OTHERPLAYER);
	playerPantryTransform = playerPantry->getComponent<Transform>();
	image = parent->getComponent<Image>();
	image->setActive(false);
	pantryMusic->setMusicVolume(MUSIC_VOL);
	restaurantMusic->setMusicVolume(MUSIC_VOL);
}

void GoToPantryTrigger::isOverlapping() {
	image->setActive(true);
	if ((ih->isKeyDown(SDLK_SPACE) || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A))) && GameManager::get()->canChangeScene()) {
		// se desactiva el jugador del restaurant
		playerRestaurant->setActives(false);
		otherPRestObj->setActives(false);
		otherPRestComp->sceneOut();
		// se activa y recoloca el jugador de la despensa
		playerPantry->setActives(true);
		otherPPantryObj->setActives(true);
		playerPantryTransform->setPos(PANTRY_POS);
		playerPantryTransform->setOrientation(north);
		doorSound->play();
		// se cambia a la escena de la despensa
		gm->changeScene(gm->getScene(_ecs::sc_PANTRY));
		restaurantMusic->pauseMusic();
		pantryMusic->play(-1);
	}
}

void GoToPantryTrigger::onTriggerExit() {
	image->setActive(false);
}
