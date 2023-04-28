#include "EndingDay1Scene.h"
#include "ShowSkipTransitionScene.h"
#include "../GameScenes/BeforeDayStartScene.h"

#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Utilities/checkML.h"

void EndingDay1Scene::addPath(const vector<Vector>& points)
{
	straightMovement->addPath(RelativeToGlobal::pointsHouse(points));
}

EndingDay1Scene::EndingDay1Scene() {
	dialogues = GameManager::get()->getDialogueInfo("EndingDay1.json");

	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");
	filter->setOpacity(80);

	player = new Player(this, 0);
	straightMovement = new StraightMovement(player, 3);
	player->getComponent<PlayerMovementController>()->setActive(false);

	transform = player->getComponent<Transform>();
	auto anim = player->getComponent<CharacterAnimator>();
	anim->setH(96 * 1.4);
	anim->setW(48 * 1.4);
	anim->setTexture("Player_Casual", 18, 10, 1);
	anim->setframeRate(10);
}

void EndingDay1Scene::reset() {
	transform->setPos(RelativeToGlobal::pointHouse(Vector(12, 13)));
	transform->setMovState(walking);
	transform->setOrientation(north);
	addPath(paths[START]);
	state = START;

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void EndingDay1Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void EndingDay1Scene::update()
{
	CinematicBaseScene::update();
	switch (state) {
	case EndingDay1Scene::START:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			transform->setOrientation(south);
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000, font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		break;
	case EndingDay1Scene::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000, font, dialogues[1].portrait, dialogues[1].text);
			state = OUT;
		}
		break;
	case EndingDay1Scene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
			if (transition != nullptr)
				delete transition;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition, true);
		}
	case EndingDay1Scene::NONE:

		break;

	}
}



void EndingDay1Scene::finishScene()
{
	dialogueBox = nullptr;
	if (transition != nullptr)
		delete transition;
	//GameManager::get()->changeScene(GameManager::get()->getScene(sc_INTRO2), false);
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);

}
