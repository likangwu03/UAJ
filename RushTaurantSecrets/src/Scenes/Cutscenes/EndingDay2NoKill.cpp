#include "EndingDay2NoKill.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

EndingDay2NoKill::EndingDay2NoKill() {
	//dialogues = GameManager::get()->getDialogueInfo("EndingDay2NoKill.json");
	
	state = START;
	
	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");
	filter->setOpacity(80);

	player = new Player(this, 0);
	straightMovement = new StraightMovement(player, 5);
	player->getComponent<PlayerMovementController>()->setActive(false);

	transform = player->getComponent<Transform>();
	transform->setPos(Vector(1658, 772));
	transform->setMovState(walking);
	transform->setOrientation(north);
	
	auto anim = player->getComponent<CharacterAnimator>();
	anim->setH(96 * 1.8);
	anim->setW(48 * 1.8);
	anim->setTexture("Player_Casual", 18, 10, 1);
	anim->setframeRate(18);
}

void EndingDay2NoKill::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void EndingDay2NoKill::callAfterCreating() {
	state = START;
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}

void EndingDay2NoKill::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case EndingDay2NoKill::START:
		addPath(_ecs::introPath[START].points);
		state = NONE;
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