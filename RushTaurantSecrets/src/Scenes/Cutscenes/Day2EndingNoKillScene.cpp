#include "Day2EndingNoKillScene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

Day2EndingNoKillScene::Day2EndingNoKillScene() {
	dialogues = GameManager::get()->getDialogueInfo("Day2EndingNoKill.json");
	
	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");

	nightMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
}

void Day2EndingNoKillScene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void Day2EndingNoKillScene::reset() {
	dialogueBox = nullptr;
	state = INIT;
	timer = 0;
	dialogueN = 0;

	straightMovement->reset(RelativeToGlobal::pointRestaurant(Vector(19.5, 25)));

	anim->setH(96 * 1.3);
	anim->setW(48 * 1.3);

	straightMovement->changeSpeed(6);
	addPath(paths[0]);

	filter->setOpacity(80);
	nightAmbience->setVolume(60);


	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void Day2EndingNoKillScene::update() {
	CinematicBaseScene::update();
	switch (state) {
	case Day2EndingNoKillScene::INIT:
		nightAmbience->play(-1);
		nightMusic->play(-1);
		state = START;
		break;
	case Day2EndingNoKillScene::START:
		if (straightMovement->hasFinishedPath()) {
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
			addPath(paths[1]);
			state = ENTERING;
		}
		break;
	case Day2EndingNoKillScene::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			if (timer >= TURNAROUNDTIME) {
				transform->setOrientation(west);
				state = TURN;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case Day2EndingNoKillScene::TURN:
		if (timer >= TURNAROUNDTIME) {
			transform->setOrientation(south);
			state = D1DELAY;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case Day2EndingNoKillScene::D1DELAY:
		if (timer >= TURNAROUNDTIME) {
			state = D1;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case Day2EndingNoKillScene::D1:
		dialogueBox = new Dialogue(this, BOXPOS, 700, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
		dialogueN++;
		state = D2;
		break;
	case Day2EndingNoKillScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, BOXPOS, 700, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			dialogueN++;
			state = D3;
		}
		break;
	case Day2EndingNoKillScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, BOXPOS, 700, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			dialogueN++;
			state = OUT;
		}
		break;
	case Day2EndingNoKillScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 3, true, true);
 			GameManager::get()->pushScene(transition);
			state = NONE;
		}
		break;

	}
	
}

void Day2EndingNoKillScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

}


void Day2EndingNoKillScene::finishScene() {
	if(transition != nullptr)
		delete transition;
	nightMusic->haltMusic();
	nightAmbience->haltChannel();
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_INTRO3NOKILL), true);
	GameManager::get()->getScene(sc_INTRO3NOKILL)->reset();
	CinematicBaseScene::finishScene();

}