#include "BadEnding4Scene.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Structure/GameManager.h"
#include "ShowSkipTransitionScene.h"

BadEnding4Scene::BadEnding4Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding4.json");
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY");
	top = &sdlutils().images().at("CINEMATIC_BG_PANTRY_TOP");
	reading = false;

	book = new GameObject(this);
	new Transform(book, Vector(RelativeToGlobal::pointPantry({ 23, 5 })), Vector(0,0), 48, 96);
	Animator::AnimParams ap;
	ap.height = 96;
	ap.width = 48;
	ap.initFrame = 15;
	ap.endFrame = 26;
	ap.currAnim = 7;
	new UIAnimator(book, "Player_1", ap, Vector(RelativeToGlobal::pointPantry({ 25, 5 })));

	thief = new CinematicNPC(this, "Thief_2", RelativeToGlobal::pointPantry({ 17, 5 }), 1);
	straightMovementThief = new StraightMovement(thief, 3);

	straightMovement = new StraightMovement(player, 2);

	playerPoints = { {Vector(20, 14)} };
}

void BadEnding4Scene::reset() {
	dialogueBox = nullptr;
	state = START;

	transform->setPos(RelativeToGlobal::pointPantry({ 20, 14 }));
	transform->setMovState(walking);
	straightMovement->changeSpeed(2);
	straightMovement->stop();

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 1);
		GameManager::get()->pushScene(transition, true);
	}
}

void BadEnding4Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	thief->render();
	if (reading)
		book->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void BadEnding4Scene::finishScene() {

}

void BadEnding4Scene::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case BadEnding4Scene::START:
		addPathPantry(playerPoints);
		addPathPantry(BE4PathPlayer[START]);
		straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[0]));
		state = D1;
		break;
	case BadEnding4Scene::D1:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = D2;
		}
		break;
	case BadEnding4Scene::D2:
		if (Text::isTextFinished()) {
			thief->getComponent<Transform>()->setOrientation(south);
			reading = true;
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D3;
		}
		break;
	case BadEnding4Scene::D3:
		if (Text::isTextFinished()) {
			reading = false;
			straightMovementThief->changeSpeed(8);
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[1]));
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = D4;
		}
		break;
	case BadEnding4Scene::D4:
		if (straightMovementThief->hasFinishedPath()) {
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[2]));
			transform->setOrientation(west);
			state = D5;
		}
		break;
	case BadEnding4Scene::D5:
		if (straightMovementThief->hasFinishedPath()) {
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[3]));
			state = D6;
		}
		break;
	case BadEnding4Scene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			state = D7;
		}
		break;
	case BadEnding4Scene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text);
			state = D8;
		}
		break;
	case BadEnding4Scene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
			state = D9;
		}
		break;
	case BadEnding4Scene::D9:
		break;
	case BadEnding4Scene::NONE:
		break;
	}
}

void BadEnding4Scene::addPathPantry(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}