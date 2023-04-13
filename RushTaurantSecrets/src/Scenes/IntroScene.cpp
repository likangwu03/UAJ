#include "IntroScene.h"
#include "../Structure/GameManager.h"
#include "MainMenu.h"
#include "../Utilities/checkML.h"
#include "BeforeDayStartScene.h"
#include "DailyMenuScene.h"
#include "ShowSkipTransitionScene.h".h"

IntroScene::IntroScene() : WIDTH(sdlutils().width()), HEIGHT(sdlutils().height()) {
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	player = new Player(this, 0);
	auto tr = player->getComponent<Transform>();
	auto anim = player->getComponent<CharacterAnimator>();
	filter->setOpacity(80);
	anim->setH(96 * 1.8);
	anim->setW(48 * 1.8);
	anim->setTexture("Player_Casual", 18, 10, 1);
	anim->setframeRate(20);
	Scene::initRender();
	//dialogueInfo=GameManager::get()->getDialogueInfo("Intro.json");
	state = START;
}

void IntroScene::callAfterCreating() {
	GameManager::get()->changeScene(new ShowSkipTransitionScene(this,3));
}


void IntroScene::update() {
	/*switch (state)
	{
	case IntroScene::START:
		new Dialogue(this, Vector(150, 520), 700, 0.01 * 1000, 
			font,dialogueInfo[0].portrait,
			{ "Hi, this a demo of ResTaurant Secrets.", "Have fun cooking and killing people." });

		break;
	case IntroScene::ENTERING:
		break;
	case IntroScene::ARRIVE:
		break;
	case IntroScene::D1:
		break;
	case IntroScene::D2:
		break;
	case IntroScene::D3:
		break;
	case IntroScene::D4:
		break;
	case IntroScene::D5:
		break;
	case IntroScene::D6:
		break;
	case IntroScene::OUT:
		break;
	default:
		break;
	}*/
}

void IntroScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	Scene::renderLayer();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

//void IntroScene::handleEvents() {
//
//	CinematicBaseScene::handleEvents();
//}

void IntroScene::finishScene() {
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
	GameManager::get()->getDailyMenu()->reset();
}