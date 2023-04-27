#include "Day2KillEndingScene.h"

#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"


void Day2KillEndingScene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsHouse(points));
}

Day2KillEndingScene::Day2KillEndingScene() {
	dialogues = GameManager::get()->getDialogueInfo("EndingDay2Kill.json");
	enterPoints = { {Vector(13, 6)} };
	phonePoints = { {Vector(13, 13)}, {Vector(12, 13)} };

	state = START;
	bg = &sdlutils().images().at("CINEMATIC_BG_HOUSE");
	black = &sdlutils().images().at("Filter_Black");
	phonecall = &sdlutils().soundEffects().at("PHONECALL");

	player = new Player(this, 0);
	player->getComponent<PlayerMovementController>()->setActive(false);
	straightMovement = new StraightMovement(player, 5);

	transform = player->getComponent<Transform>();
	transform->setPos(RelativeToGlobal::pointHouse({ 13, 14 }));
	transform->setMovState(walking);
	addPath(enterPoints);

	auto anim = player->getComponent<CharacterAnimator>();
	anim->setH(96);
	anim->setW(48);
	anim->setTexture("Player_Casual", 18, 10, 1);
	anim->setframeRate(18);
}

void Day2KillEndingScene::reset()
{
	state = START;
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}

void Day2KillEndingScene::renderCinematic()
{
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
}

void Day2KillEndingScene::finishScene()
{
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if (transition != nullptr)
		delete transition;
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);
}

void Day2KillEndingScene::update()
{
	CinematicBaseScene::update();
	switch (state)
	{
	case Day2KillEndingScene::START:
		//transform->setOrientation(north);
		(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
		state = D1;
		break;
	case Day2KillEndingScene::D1:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = PHONE;
		}
		break;
	case Day2KillEndingScene::PHONE:
		if (Text::isTextFinished()) {
			phonecall->play(-1);
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			cont = 0;
			state = PATHING;
		}
		break; 
	case Day2KillEndingScene::PATHING:
		cont += frameTime;
		if (cont > START_TIME * 1000) {
			addPath(phonePoints);
			state = D2;
		}
		break;
	case Day2KillEndingScene::D2:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			if (Text::isTextFinished()) {
				phonecall->haltChannel();
				dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
					font, dialogues[2].portrait, dialogues[2].text);
				state = OUT;
			}
		}
		break;
	case Day2KillEndingScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
			if (transition != nullptr)
				delete transition;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition, true);
		}
		break;
	case Day2KillEndingScene::NONE:
		break;
	}
}
