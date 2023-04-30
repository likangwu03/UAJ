#include "BadEnding4Scene.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Structure/GameManager.h"
#include "ShowSkipTransitionScene.h"

BadEnding4Scene::BadEnding4Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding4.json");
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY");

	thief = new CinematicNPC(this, "Thief_2", RelativeToGlobal::pointPantry({ 17, 5 }), 1); 
	straightMovementThief = new StraightMovement(thief, 3);

	straightMovement = new StraightMovement(player, 2);

	playerPoints = { {Vector(20, 14)} };
	thiefPoints = { {Vector(23, 5)} };
	thiefPoints2 = { {Vector(7, 5)} };
	//thiefPoints2 = { {Vector(7, 8)} };
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
		straightMovementThief->addPath(RelativeToGlobal::pointsPantry(thiefPoints));
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
		// terminar animación de libro
		/*if (Text::isTextFinished()) {
			dialogueBox = nullptr;
		}*/

		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D3;
		}
		break;
	case BadEnding4Scene::D3:
		if (Text::isTextFinished()) {
			straightMovementThief->changeSpeed(8);
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(thiefPoints2));
				dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
					font, dialogues[2].portrait, dialogues[2].text);
				state = D4;
		}
		break;
	case BadEnding4Scene::D4:
		break;
	case BadEnding4Scene::NONE:
		break;
	}
}

void BadEnding4Scene::addPathPantry(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}