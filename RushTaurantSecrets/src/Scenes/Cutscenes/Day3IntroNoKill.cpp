#include "Day3IntroNoKill.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

void Day3IntroNoKill::addPath(const vector<Vector>& points)
{
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

Day3IntroNoKill::Day3IntroNoKill() {
	dialogues = GameManager::get()->getDialogueInfo("Day3IntroNoKill.json");

	creepyMusic = &sdlutils().musics().at("ATMOSPHERE_CREEPY_MUSIC");
	rainAmbience = &sdlutils().soundEffects().at("RAIN_AMBIENCE");
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_RAINY");
	top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	black = &sdlutils().images().at("Filter_Black");
}

void Day3IntroNoKill::reset() {
	dialogueBox = nullptr;

	transform->setPos(RelativeToGlobal::pointRestaurant(Vector(50, 14)));
	transform->setMovState(walking);
	transform->setOrientation(north);

	anim->setH(96 * 1.7);
	anim->setW(48 * 1.7);
	anim->setTexture("Player_Casual", 0, 0, 0, 10);
	(&sdlutils().images().at("Filter_White"))->setOpacity(60);
	filter->setOpacity(80);
	
	rainAmbience->setVolume(50);

	straightMovement->changeSpeed(5);
	state = START;
	cont = 0;

	straightMovement->stop();
	addPath(playerPaths[START]);

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void Day3IntroNoKill::renderCinematic()
{
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void Day3IntroNoKill::finishScene()
{
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if (transition != nullptr)
		delete transition;
	creepyMusic->haltMusic();
	rainAmbience->haltChannel();
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);
}

void Day3IntroNoKill::update()
{
	CinematicBaseScene::update();
	cont += frameTime;
	if (cont >= THUNDER_TIMER * 1000) {
		(&sdlutils().soundEffects().at("THUNDER"))->play();
		THUNDER_TIMER = sdlutils().rand().nextInt(20, 30);
		cont = 0;
	}
	switch (state)
	{
	case Day3IntroNoKill::START:
		rainAmbience->play(-1);
		creepyMusic->play(-1);
		state = ENTERING;
		break;
	case Day3IntroNoKill::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			addPath(playerPaths[ENTERING]);
			state = ARRIVE;
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
		}
		break;
	case Day3IntroNoKill::ARRIVE:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		break;
	case Day3IntroNoKill::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D2;
		}
		break;
	case Day3IntroNoKill::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = D3;
		}
		break;
	case Day3IntroNoKill::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			state = D4;
		}
		break;
	case Day3IntroNoKill::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 440), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text);
			state = D5;
		}
		break;
	case Day3IntroNoKill::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
			state = D6;
		}
		break;
	case Day3IntroNoKill::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text);
			state = OUT;
		}
		break;
	case Day3IntroNoKill::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 1, true, true);
			GameManager::get()->pushScene(transition, true);
			state = NONE;
		}
		break;
	case Day3IntroNoKill::NONE:
		break;
	default:
		break;
	}

}
