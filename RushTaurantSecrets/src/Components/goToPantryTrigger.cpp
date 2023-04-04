#include "GoToPantryTrigger.h"
#include "../Utilities/InputHandler.h"
#include "../Structure/GameManager.h"
#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "../Scenes/Pantry.h"
#include "../Components/Image.h"
#include "Transform.h"
#include "../Utilities/checkML.h"

GoToPantryTrigger::GoToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_),
	doorSound(&sdlutils().soundEffects().at("OPEN_DOOR")),
	sdl(SDLUtils::instance()), pantryMusic(&sdl->musics().at("PANTRY_MUSIC")) {
	gm = GameManager::get();
	playerRestaurant = parent->getScene()->getGameObject(_ecs::hdr_PLAYER);
	playerPantry = gm->getPantry()->getGameObject(_ecs::hdr_PLAYER);
	playerPantryTransform = playerPantry->getComponent<Transform>();
	image = parent->getComponent<Image>();
	image->setActive(false);
	pantryMusic->setMusicVolume(MUSIC_VOL);
}

void GoToPantryTrigger::isOverlapping() {
	image->setActive(true);
	if (ih->isKeyDown(SDLK_SPACE) || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A))) {
		// se desactiva el jugador del restaurant
		playerRestaurant->setActives(false);
		// se activa y recoloca el jugador de la despensa
		playerPantry->setActives(true);
		playerPantryTransform->setPos(PANTRY_POS);
		playerPantryTransform->setOrientation(north);
		doorSound->play();
		// se cambia a la escena de la despensa
		gm->changeScene(gm->getPantry());
		pantryMusic->play();
	}
}

void GoToPantryTrigger::onTriggerExit() {
	image->setActive(false);
}
