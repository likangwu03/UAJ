#include "IntroScene.h"
#include "../Structure/GameManager.h"
#include "MainMenu.h"
#include "../Utilities/checkML.h"
#include "BeforeDayStartScene.h"
#include "DailyMenuScene.h"
#include "TransitionScene.h"

IntroScene::IntroScene(): WIDTH(sdlutils().width()), HEIGHT(sdlutils().height()) {
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	player = new Player(this, 0);	
	auto tr=player->getComponent<Transform>();
	auto anim=player->getComponent<CharacterAnimator>();
	filter->setOpacity(80);
	anim->setH(96 *1.8);
	anim->setW(48 * 1.8);
	anim->setTexture("Player_Casual", 18, 10, 1);
	anim->setframeRate(20);
	Scene::initRender();
}

void IntroScene::callAfterCreating() {
	GameManager::get()->changeScene(new TransitionScene(this, 5));
}

void IntroScene::render() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	Scene::renderLayer();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}
void IntroScene::handleEvents() {

	if ((ih->joysticksInitialised() && ih->getButtonState(0, SDL_JOYBUTTONDOWN)) || ih->keyDownEvent()) {
		GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
		GameManager::get()->getDailyMenu()->reset();
	}
}
