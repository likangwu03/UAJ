#include "Day3IntroNoKill.h"
#include "../../Utilities/checkML.h"

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
	rainAmbience = &sdlutils().soundEffects().at("THUNDERSTORM");
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_RAINY");
	top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	black = &sdlutils().images().at("Filter_Black");
}

void Day3IntroNoKill::reset() {
	dialogueBox = nullptr;

	straightMovement->reset(RelativeToGlobal::pointRestaurant(Vector(50, 14)));

	anim->setH(96 * 1.7);
	anim->setW(48 * 1.7);
	anim->setTexture("Player_Casual", 0, 0, 0, 10);
	
	filter->setOpacity(80);
	rainAmbience->setVolume(50);

	straightMovement->changeSpeed(5);
	addPath(playerPaths[START]);
	state = START;
	cont = 0;

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
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART));
	CinematicBaseScene::finishScene();
}

void Day3IntroNoKill::update()
{
	CinematicBaseScene::update();
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
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text, dialogues[0].character);
			state = D1;
		}
		break;
	case Day3IntroNoKill::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text, dialogues[1].character);
			state = D2;
		}
		break;
	case Day3IntroNoKill::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text, dialogues[2].character);
			state = D3;
		}
		break;
	case Day3IntroNoKill::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text, dialogues[3].character);
			state = D4;
		}
		break;
	case Day3IntroNoKill::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text, dialogues[4].character);
			state = D5;
		}
		break;
	case Day3IntroNoKill::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text, dialogues[5].character);
			state = D6;
		}
		break;
	case Day3IntroNoKill::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text, dialogues[6].character);
			state = D7;
		}
		break;	case Day3IntroNoKill::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[7].portrait, dialogues[7].text, dialogues[7].character);
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
