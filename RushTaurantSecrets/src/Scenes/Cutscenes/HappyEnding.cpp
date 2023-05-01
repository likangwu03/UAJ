#include "HappyEnding.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

HappyEnding::HappyEnding() {
	//dialogues = GameManager::get()->getDialogueInfo("HappyEnding.json");
	
	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");

	nightMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
}

void HappyEnding::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void HappyEnding::reset() {
	dialogueBox = nullptr;
	state = START;
	timer = 0;
	dialogueN = 0;

	transform->setPos(RelativeToGlobal::pointRestaurant(Vector(19.5, 25)));
	transform->setMovState(walking);
	transform->setOrientation(north);

	anim->setH(96 * 1.3);
	anim->setW(48 * 1.3);

	straightMovement->changeSpeed(6);
	straightMovement->stop();
	addPath(paths[START]);

	filter->setOpacity(80);
	nightAmbience->setVolume(60);

	nightAmbience->play(-1);
	nightMusic->play(-1);

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void HappyEnding::update() {
	CinematicBaseScene::update();
	//switch (state) {
	//case HappyEnding::START:
	//	if (straightMovement->hasFinishedPath()) {
	//		(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
	//		addPath(paths[ENTERING]);
	//		state = ENTERING;
	//	}
	//	break;
	//case HappyEnding::ENTERING:
	//	if (straightMovement->hasFinishedPath()) {
	//		transform->setMovState(idle);
	//		if (timer >= TURNAROUNDTIME) {
	//			transform->setOrientation(west);
	//			state = TURN;
	//			timer = 0;
	//		}
	//		else timer += frameTime;
	//	}
	//	break;
	//case HappyEnding::OUT:
	//	if (Text::isTextFinished()) {
	//		dialogueBox = nullptr;
	//		transition = new TransitionScene(this, 3, true, true);
 //			GameManager::get()->pushScene(transition);
	//		state = NONE;
	//	}
	//	break;

	//}
	
}

void HappyEnding::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

}


void HappyEnding::finishScene() {
	if(transition != nullptr)
		delete transition;
	nightMusic->haltMusic();
	nightAmbience->haltChannel();
//	GameManager::get()->changeScene(GameManager::get()->getScene(sc_INTRO3), false);
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);

}