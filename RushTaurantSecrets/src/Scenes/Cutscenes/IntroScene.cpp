#include "IntroScene.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

IntroScene::IntroScene() {
	dialogues = GameManager::get()->getDialogueInfo("Intro.json");
	
	state = START;
	nightMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	nightAmbience->setVolume(60);
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM");
	top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	filter->setOpacity(80);
	black = &sdlutils().images().at("Filter_Black");

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
	anim->setframeRate(10);
}

void IntroScene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void IntroScene::callAfterCreating() {
	state = START;
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}

void IntroScene::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case IntroScene::START:
		nightAmbience->play(-1);
		nightMusic->play(-1);
		addPath(_ecs::introPath[START].points);
		state = ENTERING;
		break;
	case IntroScene::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			addPath(_ecs::introPath[ENTERING].points);
			state = ARRIVE;
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
		}
		break;
	case IntroScene::ARRIVE:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox=new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		break;
	case IntroScene::D1:
		if (Text::isTextFinished()) {
			dialogueBox= new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D2;
		}
		break;
	case IntroScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = D3;
		}
		break;
	case IntroScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox= new Dialogue(this, Vector(150,430), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			state = D31;
		}
		break;
	case IntroScene::D31:
		if (Text::isTextFinished()) {
			dialogueBox= new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text);
			state = D4;
		}
		break;
	case IntroScene::D4:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 440), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
			state = D5;
		}
		break;
	case IntroScene::D5:
		if (Text::isTextFinished()) {
 			dialogueBox=new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text);
			state = D51;
		}
		break;
	case IntroScene::D51:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[7].portrait, dialogues[7].text);
			state = D6;
		}
		break;
	case IntroScene::D6:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[8].portrait, dialogues[8].text);
			state = OUT;
		}
		break;
	case IntroScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = D71;
			transition = new TransitionScene(this, 3, true, false);
			GameManager::get()->pushScene(transition, true);
		}
		break;
	case IntroScene::D71:
		if (Text::isTextFinished() && GameManager::get()->getCurrentScene() != transition) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[9].portrait, dialogues[9].text);
			state = D72;
		}
		break;
	case IntroScene::D72:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[10].portrait, dialogues[10].text);
			state = WAITD7;
		}
		break;
	case IntroScene::WAITD7:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 1, true, true);
			GameManager::get()->pushScene(transition, true);
			state = NONE;
		}
		break;

	case IntroScene::NONE:
		
		break;
	
	}
	
}

void IntroScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

	if ((state >= D71 && state < NONE && GameManager::get()->getCurrentScene() != transition) || state == NONE) {
		black->setOpacity(100);
		black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	}
}


void IntroScene::finishScene() {
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if(transition != nullptr)
		delete transition;
	nightMusic->haltMusic();
	nightAmbience->haltChannel();
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart(), false);
}