#include "FirstDayAfterKillScene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

FirstDayAfterKillScene::FirstDayAfterKillScene() {
	dialogues = GameManager::get()->getDialogueInfo("FirstDayAfterKill.json");
	
	nightMusic = &sdlutils().musics().at("SILENT_CREEPY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM");
	top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
}

void FirstDayAfterKillScene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void FirstDayAfterKillScene::reset() {
	dialogueBox = nullptr;
	cont = 0;

	straightMovement->reset(Vector(576, 230));
	//transform->setPos(Vector(576, 230));
	//transform->setMovState(idle);
	transform->setOrientation(north);

	anim->setW(48 * 1.7);
	anim->setH(96 * 1.7);
	anim->setTexture("Player_Casual", 0, 0, 0, 10);

	nightAmbience->setVolume(60);
	filter->setOpacity(80);

	straightMovement->changeSpeed(3);
	//straightMovement->stop();
	state = INIT;

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, START_TIME);
		GameManager::get()->pushScene(transition, true);
	}
}

void FirstDayAfterKillScene::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case FirstDayAfterKillScene::INIT:
		nightAmbience->play(-1);
		nightMusic->play(-1);
		state = START;
		break;
	case FirstDayAfterKillScene::START:
		cont += frameTime;
		if (cont > START_TIME * 1000) {
			dialogueBox = new Dialogue(this, Vector(150, 420), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = M1;
		}
		break;
	case FirstDayAfterKillScene::M1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = P1;
		}
		break;
	case FirstDayAfterKillScene::P1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 420), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = M2;
		}
		break;
	case FirstDayAfterKillScene::M2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			state = P2;
		}
		break;
	case FirstDayAfterKillScene::P2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text);
			state = MOV1;

		}
		break;
	case FirstDayAfterKillScene::MOV1:
		if (Text::isTextFinished()) {
			straightMovement->addPath({ Vector(576,180) });
			straightMovement->changeSpeed(10);
			transform->setMovState(walking);
			state = M3;
		}
		break;


	case FirstDayAfterKillScene::M3:
		if (straightMovement->hasFinishedPath()) {
			//transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 420), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
			state = M4;
		}
		break;
	case FirstDayAfterKillScene::M4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text);
			state = BACKUP;
		}
		break;
	case FirstDayAfterKillScene::BACKUP:
		if (Text::isTextFinished()) {
			straightMovement->addPath({ Vector(576,250) });
			straightMovement->changeSpeed(1);
			transform->setOrientation(north);
			state = M5;
		}
		break;

	case FirstDayAfterKillScene::M5:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 420), 700, 0.01 * 1000,
				font, dialogues[7].portrait, dialogues[7].text);
			//transform->setMovState(idle);

			state = OUT;
		}
		break;

	case FirstDayAfterKillScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition);
		}
		break;
	case FirstDayAfterKillScene::NONE:
		break;
	default:
		break;
	}
}

void FirstDayAfterKillScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}


void FirstDayAfterKillScene::finishScene() {
	if (transition != nullptr)
		delete transition;

	nightMusic->haltMusic();
	nightAmbience->haltChannel();
	GameManager::get()->pushScene(GameManager::get()->getScene(sc_BEFOREDAYSTART));

}