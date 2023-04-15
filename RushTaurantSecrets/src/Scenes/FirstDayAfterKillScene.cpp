#include "FirstDayAfterKillScene.h"
#include "MainMenu.h"
#include "../Utilities/checkML.h"
#include "BeforeDayStartScene.h"
#include "DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../Structure/GameManager.h"
#include "../GameObjects/Dialogue.h"

FirstDayAfterKillScene::FirstDayAfterKillScene() {
	dialogues = GameManager::get()->getDialogueInfo("Intro.json");

	state = START;
	nightMusic = &sdlutils().musics().at("NIGHT_CHILL_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	nightAmbience->setVolume(60);
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM");
	top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	filter->setOpacity(80);

	player = new Player(this, 0);
	straightMovement = new StraightMovement(player, 5);

	transform = player->getComponent<Transform>();
	transform->setPos(Vector(1658, 772));
	transform->setMovState(walking);

	auto anim = player->getComponent<CharacterAnimator>();
	anim->setH(96 * 1.8);
	anim->setW(48 * 1.8);
	anim->setTexture("Player_Casual", 18, 10, 1);
	anim->setframeRate(18);
	//Scene::initRender();
}

void FirstDayAfterKillScene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void FirstDayAfterKillScene::callAfterCreating() {
	GameManager::get()->changeScene(new ShowSkipTransitionScene(this, 3));
}

void FirstDayAfterKillScene::update() {
	CinematicBaseScene::update();
	/*switch (state)
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
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		else
			break;
	case IntroScene::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D2;
		}
		break;
	case IntroScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = D3;
		}
		break;
	case IntroScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			state = D31;
		}
		break;
	case IntroScene::D31:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text);
			state = D4;
		}
		break;
	case IntroScene::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 440), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
			state = D5;
		}
		break;
	case IntroScene::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text);
			state = D51;
		}
		break;
	case IntroScene::D51:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[7].portrait, dialogues[7].text);
			state = D6;
		}
		break;
	case IntroScene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[8].portrait, dialogues[8].text);
			state = OUT;
		}
		break;
	case IntroScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;

			nightMusic->haltMusic();
			nightAmbience->haltChannel();
			GameManager::get()->changeScene(new TransitionScene(this, 3, true, true));
			state = NONE;
		}
		break;
	case IntroScene::NONE:

		break;

	}*/
}

void FirstDayAfterKillScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}


void FirstDayAfterKillScene::finishScene() {
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());

}