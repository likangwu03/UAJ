#include "BadEnding3Scene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"
#include "../../GameObjects/CinematicNPC.h"

BadEnding3Scene::BadEnding3Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding3.json");
	
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY");
	top = &sdlutils().images().at("CINEMATIC_BG_PANTRY_TOP");

	music = &sdlutils().musics().at("PANTRY_MUSIC");

	black = &sdlutils().images().at("Filter_Black");

}

void BadEnding3Scene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}

void BadEnding3Scene::reset() {
	dialogueBox = nullptr;
	state = INIT;
	timer = 0;
	dialogueN = 0;

	//straightMovement->reset(RelativeToGlobal::pointPantry(paths[0][0]));
	straightMovement->setIsWalking(false);
	transform->setMovState(idle);
	transform->setOrientation(south);


	anim->setTexture("Player_1", 0, 0, 0, 10);
	anim->setH(96 * PANTRYSIZE);
	anim->setW(48 * PANTRYSIZE);

	straightMovement->changeSpeed(3);

	musicVol = 20;
	music->setMusicVolume(musicVol);


	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}


void BadEnding3Scene::update() {
	CinematicBaseScene::update();
	switch (state) {
	case BadEnding3Scene::INIT:
		music->play(-1);
		state = START;
		break;
	case BadEnding3Scene::START:



	case BadEnding3Scene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
		}
		break;
	case BadEnding3Scene::NONE:
		if (musicVol > 0) musicVol-= 0.1;
		else if (musicVol <= 0) {
			musicVol = 0;
			finishScene();
		}
		music->setMusicVolume(musicVol);
		break;
	}
	
}


void BadEnding3Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	
}


void BadEnding3Scene::finishScene() {
	if(transition != nullptr)
		delete transition;
	music->haltMusic();

	GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), false);
	GameManager::get()->getScene(sc_MAINMENU)->resumeSound();
	CinematicBaseScene::finishScene();
}