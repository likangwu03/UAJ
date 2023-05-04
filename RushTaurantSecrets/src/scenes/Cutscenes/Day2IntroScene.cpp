#include "Day2IntroScene.h"

#include "../../Utilities/checkML.h"
#include "../TransitionScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

void Day2IntroScene::addPath(const vector<Vector>& points)
{
	straightMovement->addPath(RelativeToGlobal::pointsHouse(points));
}

Day2IntroScene::Day2IntroScene(){
	dialogues = GameManager::get()->getDialogueInfo("Day2Intro.json");

	dayMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	phonecall = &sdlutils().soundEffects().at("TELEPHONE");
	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	top = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_TOP");
	black = &sdlutils().images().at("Filter_Black");
}

void Day2IntroScene::reset()
{
	dialogueBox = nullptr;
	straightMovement->reset(RelativeToGlobal::pointHouse(Vector(2, 1)));

	anim->setH(96 * 1.3);
	anim->setW(48 * 1.3);
	anim->setTexture("Player_Casual", 0, 0, 0, 10);

	phonecall->setVolume(60);

	addPath(paths[0]);
	state = START;

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void Day2IntroScene::renderCinematic()
{
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void Day2IntroScene::finishScene()
{
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if (transition != nullptr)
		delete transition;
	dayMusic->haltMusic();
	phonecall->haltChannel();
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);
	CinematicBaseScene::finishScene();
}

void Day2IntroScene::update()
{
	CinematicBaseScene::update();
	switch (state)
	{
	case Day2IntroScene::START:
		if (straightMovement->hasFinishedPath()) {
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
			addPath(paths[1]);
			state = ENTERING;
		}
		break;
	case Day2IntroScene::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[0].portrait, dialogues[0].text, dialogues[0].character);
			state = ARRIVE;
		}
		break;
	case Day2IntroScene::ARRIVE:
		if (Text::isTextFinished()) {
			addPath(paths[2]);
			state = D1;
		}
		break;
	case Day2IntroScene::D1:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[1].portrait, dialogues[1].text, dialogues[1].character);
			state = D2;
		}
		break;
	case Day2IntroScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[2].portrait, dialogues[2].text, dialogues[1].character);
			state = D3;
		}
		break;
	case Day2IntroScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[3].portrait, dialogues[3].text, dialogues[1].character);
			state = D4;
		}
		break;
	case Day2IntroScene::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[4].portrait, dialogues[4].text, dialogues[1].character);
			state = D5;
		}
		break;
	case Day2IntroScene::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[5].portrait, dialogues[5].text, dialogues[1].character);
			state = D6;
		}
		break;
	case Day2IntroScene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[6].portrait, dialogues[6].text, dialogues[1].character);
			state = D7;
		}
		break;
	case Day2IntroScene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[7].portrait, dialogues[7].text, dialogues[1].character);
			state = D8;
		}
		break;
	case Day2IntroScene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[8].portrait, dialogues[8].text, dialogues[1].character);
			state = D9;
		}
		break;
	case Day2IntroScene::D9:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[9].portrait, dialogues[9].text, dialogues[1].character);
			state = D10;
		}
		break;
	case Day2IntroScene::D10:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[10].portrait, dialogues[10].text, dialogues[1].character);
			state = D11;
		}
		break;
	case Day2IntroScene::D11:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[11].portrait, dialogues[11].text, dialogues[1].character);
			state = D12;
		}
		break;
	case Day2IntroScene::D12:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[12].portrait, dialogues[12].text, dialogues[1].character);
			state = D13;
		}
		break;
	case Day2IntroScene::D13:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000, font, dialogues[13].portrait, dialogues[13].text, dialogues[1].character);
			state = OUT;
		}
		break;
	case Day2IntroScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition, true);
		}
		break;
	case Day2IntroScene::NONE:
		break;
	default:
		break;
	}
}
