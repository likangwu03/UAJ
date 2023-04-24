#include "EndingDay2NoKill.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

EndingDay2NoKill::EndingDay2NoKill() {
	dialogues = GameManager::get()->getDialogueInfo("EndingDay2NoKill.json");
	
	state = START;
	
	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");
	filter->setOpacity(80);

	player = new Player(this, 0);
	straightMovement = new StraightMovement(player, 7);
	player->getComponent<PlayerMovementController>()->setActive(false);

	transform = player->getComponent<Transform>();
	transform->setPos(RelativeToGlobal::pointRestaurant(Vector(19.5, 20)));
	transform->setMovState(walking);
	transform->setOrientation(north);
	
	auto anim = player->getComponent<CharacterAnimator>();
	anim->setH(96 * 1.4);
	anim->setW(48 * 1.4);
	anim->setframeRate(10);

	addPath(paths[START]);
	timer = 0;
}

void EndingDay2NoKill::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void EndingDay2NoKill::callAfterCreating() {
	timer = 0;
	state = START;
	addPath(paths[START]);
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}

void EndingDay2NoKill::update() {
	CinematicBaseScene::update();
	switch (state) {
	case EndingDay2NoKill::START:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			if (timer >= TURNAROUNDTIME) {
				transform->setOrientation(west);
				state = TURNTORIGHT;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case EndingDay2NoKill::TURNTORIGHT:
		if (timer >= TURNAROUNDTIME) {
			transform->setOrientation(south);
			state = NONE;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case EndingDay2NoKill::NONE:
		
		break;
	
	}
	
}

void EndingDay2NoKill::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

}


void EndingDay2NoKill::finishScene() {
	if(transition != nullptr)
		delete transition;
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart(), false);
}