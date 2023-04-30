#include "Day1IntroScene.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

Day1IntroScene::Day1IntroScene() {
	dialogues = GameManager::get()->getDialogueInfo("Day1Intro.json");
	
	nightMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM");
	top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	black = &sdlutils().images().at("Filter_Black");
}

void Day1IntroScene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void Day1IntroScene::reset() {
	dialogueBox = nullptr;
	transform->setPos(RelativeToGlobal::pointRestaurant(Vector(50, 14)));

	anim->setW(48 * 1.7);
	anim->setH(96 * 1.7);
	anim->setTexture("Player_Casual", 0, 0, 0, 10);

	nightAmbience->setVolume(60);
	filter->setOpacity(80);

	straightMovement->stop();
	addPath(introPath[START]);
	state = START;

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void Day1IntroScene::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case Day1IntroScene::START:
		nightAmbience->play(-1);
		nightMusic->play(-1);
		state = ENTERING;
		break;
	case Day1IntroScene::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			addPath(introPath[ENTERING]);
			state = ARRIVE;
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
		}
		break;
	case Day1IntroScene::ARRIVE:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000, font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		break;
	case Day1IntroScene::D1:
		if (Text::isTextFinished()) {
			dialogueBox= new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000, font, dialogues[1].portrait, dialogues[1].text);
			state = D2;
		}
		break;
	case Day1IntroScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[2].portrait, dialogues[2].text);
			state = D3;
		}
		break;
	case Day1IntroScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox= new Dialogue(this, Vector(150,430), 700, 0.01 * 1000, font, dialogues[3].portrait, dialogues[3].text);
			state = D31;
		}
		break;
	case Day1IntroScene::D31:
		if (Text::isTextFinished()) {
			dialogueBox= new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000, font, dialogues[4].portrait, dialogues[4].text);
			state = D4;
		}
		break;
	case Day1IntroScene::D4:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 440), 700, 0.01 * 1000, font, dialogues[5].portrait, dialogues[5].text);
			state = D5;
		}
		break;
	case Day1IntroScene::D5:
		if (Text::isTextFinished()) {
 			dialogueBox=new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000, font, dialogues[6].portrait, dialogues[6].text);
			state = D51;
		}
		break;
	case Day1IntroScene::D51:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000, font, dialogues[7].portrait, dialogues[7].text);
			state = D6;
		}
		break;
	case Day1IntroScene::D6:
		if (Text::isTextFinished()) {
			dialogueBox=new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000, font, dialogues[8].portrait, dialogues[8].text);
			state = OUT;
		}
		break;
	case Day1IntroScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = D71;
			transition = new TransitionScene(this, 3, true, false);
			GameManager::get()->pushScene(transition, true);
		}
		break;
	case Day1IntroScene::D71:
		if (Text::isTextFinished() && GameManager::get()->getCurrentScene() != transition) {
			dialogueBox = new Dialogue(this, Vector(150, 400), 700, 0.01 * 1000, font, dialogues[9].portrait, dialogues[9].text);
			state = D72;
		}
		break;
	case Day1IntroScene::D72:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[10].portrait, dialogues[10].text);
			state = WAITD7;
		}
		break;
	case Day1IntroScene::WAITD7:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 1, true, true);
			GameManager::get()->pushScene(transition, true);
			state = NONE;
		}
		break;

	case Day1IntroScene::NONE:
		
		break;
	
	}
	
}

void Day1IntroScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

	if ((state >= D71 && state < NONE && GameManager::get()->getCurrentScene() != transition) || state == NONE) {
		black->setOpacity(100);
		black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	}
}


void Day1IntroScene::finishScene() {
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if(transition != nullptr)
		delete transition;
	nightMusic->haltMusic();
	nightAmbience->haltChannel();
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);
}