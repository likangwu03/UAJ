#include "BadEnding4Scene.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Structure/GameManager.h"
#include "ShowSkipTransitionScene.h"

BadEnding4Scene::BadEnding4Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding4.json");
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY");
	state = START;
	player = new Player(this, 0);
	player->getComponent<PlayerMovementController>()->setActive(false);
	thief = new CinematicNPC(this, "Thief_2", RelativeToGlobal::pointPantry({ 19, 5 }), 1); // CAMBIAR
	straightMovement = new StraightMovement(player, 5);

	playerPoints = { {Vector(20, 15)} };
	transform = player->getComponent<Transform>();
	transform->setMovState(idle);
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
		state = ARRIVE;
		break;
	case BadEnding4Scene::ARRIVE:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		break;
	case BadEnding4Scene::D1:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
		}
		break;
	case BadEnding4Scene::NONE:
		break;
	}
}

void BadEnding4Scene::addPathPantry(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}

void BadEnding4Scene::reset() {
	state = START;
	//state = NONE; // BORRAR
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}