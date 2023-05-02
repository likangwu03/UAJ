#include "Day1EndingScene.h"
#include "ShowSkipTransitionScene.h"

#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Utilities/checkML.h"

void Day1EndingScene::addPath(const vector<Vector>& points)
{
	straightMovement->addPath(RelativeToGlobal::pointsHouse(points));
}

Day1EndingScene::Day1EndingScene() {
	dialogues = GameManager::get()->getDialogueInfo("Day1Ending.json");

	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");
}

void Day1EndingScene::reset() {
	dialogueBox = nullptr;

	transform->setPos(RelativeToGlobal::pointHouse(Vector(12.5, 15)));
	transform->setMovState(walking);
	transform->setOrientation(north);
	
	anim->setH(96 * 1.3);
	anim->setW(48 * 1.3);
	anim->setTexture("Player_Casual", 0, 0, 0, 10);

	filter->setOpacity(80);

	straightMovement->changeSpeed(3);
	straightMovement->stop();
	addPath(paths[START]);
	state = START;

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void Day1EndingScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void Day1EndingScene::update()
{
	CinematicBaseScene::update();
	switch (state) {
	case Day1EndingScene::START:
		if (straightMovement->hasFinishedPath()) {
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
			addPath(paths[ENTERING]);
			state = ENTERING;
		}
		break;
	case Day1EndingScene::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			transform->setOrientation(south);
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000, font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		break;
	case Day1EndingScene::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000, font, dialogues[1].portrait, dialogues[1].text);
			state = OUT;
		}
		break;
	case Day1EndingScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition, true);
		}
	case Day1EndingScene::NONE:

		break;

	}
}



void Day1EndingScene::finishScene()
{
	dialogueBox = nullptr;
	if (transition != nullptr)
		delete transition;
	//GameManager::get()->changeScene(GameManager::get()->getScene(sc_INTRO2), false);
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);

}
