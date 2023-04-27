#include "GameOverScene.h"
#include "../../Structure/GameManager.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"


GameOverScene::GameOverScene() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("PAUSE_BG"));
	new Image(bg, image);


	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2.8 * SDLUtils::instance()->height() / 5), 385, 130, 
		[&]() {
			GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU));
		});
}

GameOverScene::~GameOverScene() {
}


void GameOverScene::setGameOver(endingType type) {
	switch (type)
	{
	case _ecs::BadRep:
		break;
	case _ecs::Broke:
		break;
	case _ecs::Caught:
		break;
	case _ecs::Robbed:
		break;
	case _ecs::Normal:
		break;
	case _ecs::Happy:
		break;
	default:
		break;
	}
}