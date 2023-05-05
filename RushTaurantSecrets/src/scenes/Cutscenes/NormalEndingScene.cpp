#include "NormalEndingScene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

void NormalEndingScene::addPath(const vector<Vector>& points)
{
	straightMovement->addPath(RelativeToGlobal::pointsHouse(points));
}

NormalEndingScene::NormalEndingScene()
{
	dialogues = GameManager::get()->getDialogueInfo("NormalEnding.json");

	creepyMusic = &sdlutils().musics().at("SILENT_CREEPY_MUSIC");
	bg = &sdlutils().images().at("CINEMATIC_BG_HOUSE");
	top = &sdlutils().images().at("CINEMATIC_BG_HOUSE_TOP");
	black = &sdlutils().images().at("Filter_Black");
}

void NormalEndingScene::reset()
{
	dialogueBox = nullptr;
	straightMovement->reset(RelativeToGlobal::pointHouse(Vector(13, 16)));

	anim->setTexture("Player_Casual", 0, 0, 0, 10);

	addPath(path[START]);
	state = START;

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void NormalEndingScene::renderCinematic()
{
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

	if ((state >= CARCRASH && state < NONE && GameManager::get()->getCurrentScene() != transition) || state == NONE) {
		black->setOpacity(100);
		black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	}
}

void NormalEndingScene::finishScene()
{
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if (transition != nullptr)
		delete transition;
	creepyMusic->haltMusic();
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU));
	GameManager::get()->getScene(sc_MAINMENU)->resumeSound();
	CinematicBaseScene::finishScene();
}

void NormalEndingScene::update()
{
	CinematicBaseScene::update();

	switch (state)
	{
	case NormalEndingScene::START:
		creepyMusic->play(-1);
		state = ENTERING;
		(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
		break;
	case NormalEndingScene::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[0].portrait, dialogues[0].text, dialogues[0].character);
			state = D1;
		}
		break;
	case NormalEndingScene::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[1].portrait, dialogues[1].text, dialogues[1].character);
			state = ROOM;
		}
		break;
	case NormalEndingScene::ROOM:
		if (Text::isTextFinished()) {
			addPath(path[1]);
			state = D2;
		}
		break;
	case NormalEndingScene::D2:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[2].portrait, dialogues[2].text, dialogues[2].character);
			state = D3;
		}
		break;
	case NormalEndingScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[3].portrait, dialogues[3].text, dialogues[3].character);
			state = D4;
		}
		break;
	case NormalEndingScene::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[4].portrait, dialogues[4].text, dialogues[4].character);
			state = D5;
		}
		break;
	case NormalEndingScene::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[5].portrait, dialogues[5].text, dialogues[5].character);
			state = D6;
		}
		break;
	case NormalEndingScene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[6].portrait, dialogues[6].text, dialogues[6].character);
			state = D7;
		}
		break;
	case NormalEndingScene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[7].portrait, dialogues[7].text, dialogues[7].character);
			state = D8;
		}
		break;
	case NormalEndingScene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[8].portrait, dialogues[8].text, dialogues[8].character);
			state = D9;
		}
		break;
	case NormalEndingScene::D9:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[9].portrait, dialogues[9].text, dialogues[9].character);
			state = D10;
		}
		break;
	case NormalEndingScene::D10:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[10].portrait, dialogues[10].text, dialogues[10].character);
			state = D11;
		}
		break;
	case NormalEndingScene::D11:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[11].portrait, dialogues[11].text, dialogues[11].character);
			state = D12;
		}
		break;
	case NormalEndingScene::D12:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[12].portrait, dialogues[12].text, dialogues[12].character);
			state = D13;
		}
		break;
	case NormalEndingScene::D13:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[13].portrait, dialogues[13].text, dialogues[13].character);
			state = D14;
		}
		break;
	case NormalEndingScene::D14:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[14].portrait, dialogues[14].text, dialogues[14].character);
			state = MOVE;
		}
		break;
	case NormalEndingScene::MOVE:
		if (Text::isTextFinished()) {
			straightMovement->reset(RelativeToGlobal::pointHouse(path[1][2]));
			addPath(path[2]);
			straightMovement->enableRoundTripByLaps(1);
			state = D15;
		}
		break;
	case NormalEndingScene::D15:
		if (straightMovement->roundTripEnded()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[15].portrait, dialogues[15].text, dialogues[15].character);
			state = MOVE2;
		}
		break;
	case NormalEndingScene::MOVE2:
		if (Text::isTextFinished()) {
			addPath(path[3]);
			state = D16;
		}
		break;
	case NormalEndingScene::D16:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[16].portrait, dialogues[16].text, dialogues[16].character);
			state = D17;
		}
		break;
	case NormalEndingScene::D17:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[17].portrait, dialogues[17].text, dialogues[17].character);
			state = D18;
		}
		break;
	case NormalEndingScene::D18:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[18].portrait, dialogues[18].text, dialogues[18].character);
			state = MOVE3;
		}
		break;
	case NormalEndingScene::MOVE3:
		if (Text::isTextFinished()) {
			addPath(path[4]);
			state = D19;
		}
		break;
	case NormalEndingScene::D19:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[19].portrait, dialogues[19].text, dialogues[19].character);
			state = MOVE4;
		}
		break;	
	case NormalEndingScene::MOVE4:
		if (Text::isTextFinished()) {
			addPath(path[5]);
			state = D20;
		}
		break;
	case NormalEndingScene::D20:
		if (straightMovement->hasFinishedPath()) {
			transform->setOrientation(east);
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[20].portrait, dialogues[20].text, dialogues[20].character);
			state = OUTSIDE;
		}
		break;
	case NormalEndingScene::OUTSIDE:
		if (Text::isTextFinished()) {
			addPath(path[6]);
			state = D21;
		}
		break;
	case NormalEndingScene::D21:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[21].portrait, dialogues[21].text, dialogues[21].character);
			state = D22;
		}
		break;
	case NormalEndingScene::D22:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[22].portrait, dialogues[22].text, dialogues[22].character);
			state = D23;
		}
		break;
	case NormalEndingScene::D23:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 410), 700, 0.01 * 1000, font, dialogues[23].portrait, dialogues[23].text, dialogues[23].character);
			state = BRBKMS;
		}
		break;
	case NormalEndingScene::BRBKMS:
		if (Text::isTextFinished()) {
			addPath(path[7]);
			state = CARCRASH;
		}
		break;
	case NormalEndingScene::CARCRASH:
		if (straightMovement->hasFinishedPath()) {
			(&sdlutils().soundEffects().at("TYRE_SCREECH"))->play();
			cont = 0;
			state = BEEP;
		}
		break;
	case NormalEndingScene::BEEP:
		cont += frameTime;
		if (cont > BEEP_TIMER * 1000) {
			(&sdlutils().soundEffects().at("CAR_HORN"))->play();
			cont = 0;
			state = WAITCARCRASH;
		}
		break;
	case NormalEndingScene::WAITCARCRASH:
		cont += frameTime;
		if (cont > CARCRUSH_TIMER * 1000) {
			(&sdlutils().soundEffects().at("BUMP"))->play();
			cont = 0;
			state = OUT;
		}
		break;
	case NormalEndingScene::OUT:
		cont += frameTime;
		if (cont > FINISH_TIMER * 1000) {
			dialogueBox = nullptr;
			if (transition != nullptr)
				delete transition;
			transition = new TransitionScene(this, 1, true, true);
			GameManager::get()->pushScene(transition, true);
			state = NONE;
		}
		break;
	case NormalEndingScene::NONE:
		break;
	default:
		break;
	}
}
