#include "Day2EndingNoKill.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

Day2EndingNoKill::Day2EndingNoKill() {
	dialogues = GameManager::get()->getDialogueInfo("Intro.json");
	
	state = START;
	
	player = new Player(this, 0);
	straightMovement = new StraightMovement(player, 5);
	player->getComponent<PlayerMovementController>()->setActive(false);

	transform = player->getComponent<Transform>();
	transform->setPos(Vector(1658, 772));
	transform->setMovState(walking);
	
	auto anim = player->getComponent<CharacterAnimator>();
	anim->setH(96 * 1.8);
	anim->setW(48 * 1.8);
	anim->setTexture("Player_Casual", 18, 10, 1);
	anim->setframeRate(18);
}

void Day2EndingNoKill::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void Day2EndingNoKill::callAfterCreating() {
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}

void Day2EndingNoKill::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case Day2EndingNoKill::START:
		addPath(_ecs::introPath[START].points);
		state = NONE;
		break;
	case Day2EndingNoKill::NONE:
		
		break;
	
	}
	
}

void Day2EndingNoKill::renderCinematic() {
	

}


void Day2EndingNoKill::finishScene() {
	if(transition != nullptr)
		delete transition;
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart(), false);
}