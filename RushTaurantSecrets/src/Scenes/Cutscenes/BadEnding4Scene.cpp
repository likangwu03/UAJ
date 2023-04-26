#include "BadEnding4Scene.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Structure/GameManager.h"
#include "ShowSkipTransitionScene.h"

BadEnding4Scene::BadEnding4Scene() {
	dialogues = GameManager::get()->getDialogueInfo("Intro.json");
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY");
	//state = START;
	state = NONE; // BORRAR
	player = new Player(this, 0);
	thief = new CinematicNPC(this, "Thief_2", RelativeToGlobal::pointRestaurant({ 25, 14 }), 1); // CAMBIAR
}

void BadEnding4Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();

}

void BadEnding4Scene::finishScene() {

}

void BadEnding4Scene::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case BadEnding4Scene::START:
		if (straightMovement->hasFinishedPath()) {
			addPathPantry(BE4Path[START]);
		}
		//state = ENTERING;
		break;
	case BadEnding4Scene::NONE:

		break;
	}
}

void BadEnding4Scene::addPathPantry(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}

void BadEnding4Scene::callAfterCreating() {
	//state = START;
	state = NONE; // BORRAR
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}