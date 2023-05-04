#include "BadEnding2Scene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"
#include "../../GameObjects/CinematicNPC.h"

BadEnding2Scene::BadEnding2Scene() {
	dialogues = GameManager::get()->getDialogueInfo("HappyEnding.json");
	
	black = &sdlutils().images().at("Filter_Black");

}

void BadEnding2Scene::addPath(const vector<Vector>& points, GameObject* object) {
	object->getComponent<StraightMovement>()->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void BadEnding2Scene::reset() {
//	dialogueBox = nullptr;
//	state = SOUND;
//	timer = 0;
//	dialogueN = 0;
//
//	straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[0][0]));
//	straightMovement->setIsWalking(false);
//	transform->setMovState(sleeping);
//
//	anim->setTexture("Player_Casual", 0, 0, 0, 10);
//	anim->setH(96 * 1.6);
//	anim->setW(48 * 1.6);
//
//	straightMovement->changeSpeed(5);
//
//	filter->setOpacity(80);
//	
//	music = &sdlutils().musics().at("HAPPY_MORNING_MUSIC");
//	musicVol = 20;
//	music->setMusicVolume(musicVol);
//
//	ambience = &sdlutils().soundEffects().at("BIRDS");
//	ambience->setVolume(60);
//
//
//	bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT");
//	filter = sdlutils().getLoadedTilesets().at("restaurantNight");
//
//
//	if (GameManager::instance()->getCurrentScene() == this) {
//		transition = new ShowSkipTransitionScene(this, 3);
//		GameManager::get()->pushScene(transition, true);
//	}
}


void BadEnding2Scene::update() {
	CinematicBaseScene::update();
	switch (state) {
	case BadEnding2Scene::INIT:
		ambience->play(-1);
		music->play(-1);
		break;
	case BadEnding2Scene::START:
		if (timer >= DELAY * 2) {
			transform->setMovState(sitting);
			transform->setOrientation(east);
			//state = WAKE;
			timer = 0;
		}
		else timer += frameTime;
		break;


	case BadEnding2Scene::FADEIN1:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new ShowSkipTransitionScene(this, 1, true);
			GameManager::get()->pushScene(transition, true);
			state = FADEOUT1;
			addPath(paths[4], player);
		}
		break;
	case BadEnding2Scene::FADEOUT1:
		if (GameManager::get()->getCurrentScene() != transition) {
			bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_HAPPY_ENDING");

			straightMovement->changeSpeed(2);
			straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[5][0]));
			anim->setH(96 * RESTSIZE);
			anim->setW(48 * RESTSIZE);
			

			transition = new ShowSkipTransitionScene(this, 1);
			GameManager::get()->pushScene(transition, true);
			state = OUT;
		}
		break;


	case BadEnding2Scene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition);
			state = NONE;
		}
		break;
	case BadEnding2Scene::NONE:
		if (musicVol > 0) musicVol-= 0.1;
		else if (musicVol < 0) musicVol = 0;
		music->setMusicVolume(musicVol);
		break;
	}
	
}


void BadEnding2Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
}


void BadEnding2Scene::finishScene() {
	if(transition != nullptr)
		delete transition;
	music->haltMusic();
	ambience->haltChannel();

	GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), false);
	CinematicBaseScene::finishScene();
}