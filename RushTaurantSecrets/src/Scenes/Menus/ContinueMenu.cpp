#include "ContinueMenu.h"
#include "../../Structure/GameManager.h"
#include "../GameScenes/DailyMenuScene.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../Cutscenes/Day1IntroScene.h"
#include "../../Utilities/checkML.h"


ContinueMenu::ContinueMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("CONTINUE_BG"));
	new Image(bg, image);

	buttonNewGame = new ButtonGO(this, "NEWGAME_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() / 4 - 130 / 2), 385, 130,
		[&] {
			GameManager::get()->changeScene(GameManager::get()->getScene(sc_INTRO1), true);
			GameManager::get()->newGame();
		});
	buttonNewGame->getComponent<ButtonComp>()->setHighlighted(true);

	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 3 / 4 - 130 / 2), 385, 130,
		[&] {
			GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), true);

		});

	buttonContinue = new ButtonGO(this, "CONTINUE_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 2 / 4 - 130 / 2), 385, 130,
		[&] {
			GameManager::get()->load();
		});
	button = 0;
}

ContinueMenu::~ContinueMenu() {

}

void ContinueMenu::handleEvents() {

	if (ih->joysticksInitialised()) {
		ih->refresh();
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
			|| ih->getHatState(UP) || (ih->yvalue(0, 1) < 0)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)
			|| ih->getHatState(DOWN) || (ih->yvalue(0, 1) > 0)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	else {
		if (ih->isKeyDown(SDL_SCANCODE_W)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->isKeyDown(SDL_SCANCODE_S)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	Scene::handleEvents();
}

void ContinueMenu::selectedButton(int selected) {
	buttonNewGame->getComponent<ButtonComp>()->setHighlighted(false);
	buttonContinue->getComponent<ButtonComp>()->setHighlighted(false);
	buttonMainMenu->getComponent<ButtonComp>()->setHighlighted(false);
	switch (selected)
	{
	case 0:
		buttonNewGame->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 1:
		buttonContinue->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 2:
		buttonMainMenu->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	}
}
