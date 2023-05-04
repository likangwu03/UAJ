#include "BadEnding4Scene.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Structure/GameManager.h"
#include "ShowSkipTransitionScene.h"

BadEnding4Scene::BadEnding4Scene() : finish(false), contText(7) {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding4.json");
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY");
	top = &sdlutils().images().at("CINEMATIC_BG_PANTRY_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");
	tvFilter = &sdlutils().images().at("CINEMATIC_TV_FILTER");
	lectern = &sdlutils().images().at("CINEMATIC_PANTRY_LECTERN");
	black = &sdlutils().images().at("Filter_Black");

	pantryMusic = &sdlutils().musics().at("PANTRY_MUSIC");
	homeMusic = &sdlutils().musics().at("SILENT_CREEPY_MUSIC");

	reading = false; night = false; stolenBook = false;

	book = new GameObject(this);
	new Transform(book, Vector(RelativeToGlobal::pointPantry({ 23, 5 })), Vector(0, 0), 48, 96);
	Animator::AnimParams ap;
	ap.height = 96;
	ap.width = 48;
	ap.initFrame = 15;
	ap.endFrame = 26;
	ap.currAnim = 7;
	new UIAnimator(book, "Player_1", ap, Vector(RelativeToGlobal::pointPantry({ 25, 5 })));

	thief = new CinematicNPC(this, "Thief_2", RelativeToGlobal::pointPantry({ 17, 5 }), 1);
	thief->getComponent<StraightMovement>()->changeSpeed(3);
	straightMovementThief = thief->getComponent<StraightMovement>();
	straightMovementThief->changeSpeed(3);
}

void BadEnding4Scene::reset() {
	dialogueBox = nullptr;
	state = START;

	straightMovement->reset(RelativeToGlobal::pointPantry({ 20, 14 }));
	straightMovement->changeSpeed(2);

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 1);
		GameManager::get()->pushScene(transition, true);
	}
}

void BadEnding4Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	if (!night) {
		thief->render();
		top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	}
	if (reading)
		book->render();
	if (night) {
		filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
		tvFilter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	}
	if (stolenBook)
		lectern->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void BadEnding4Scene::finishScene() {
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if (transition != nullptr)
		delete transition;
	pantryMusic->haltMusic();
	homeMusic->haltMusic();

	GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), false);
	GameManager::get()->getScene(sc_MAINMENU)->resumeSound();

	CinematicBaseScene::finishScene();
}

void BadEnding4Scene::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case BadEnding4Scene::START:
		pantryMusic->play(-1);
		straightMovement->addPath(RelativeToGlobal::pointsPantry(BE4PathPlayer[0]));
		straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[0]));
		state = D1;
		break;
	case BadEnding4Scene::D1:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text, dialogues[0].character);
			state = D2;
		}
		break;
	case BadEnding4Scene::D2:
		if (Text::isTextFinished() && straightMovementThief->hasFinishedPath()) {
			thief->getComponent<Transform>()->setOrientation(south);
			reading = true; stolenBook = true;
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text, dialogues[1].character);
			state = D3;
		}
		break;
	case BadEnding4Scene::D3:
		if (Text::isTextFinished()) {
			reading = false;
			straightMovementThief->changeSpeed(8);
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[1]));
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text, dialogues[2].character);
			state = D6;
		}
		break;
	case BadEnding4Scene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text, dialogues[3].character);
			state = D7;
		}
		break;
	case BadEnding4Scene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text, dialogues[4].character);
			state = D8;
		}
		break;
	case BadEnding4Scene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text, dialogues[5].character);
			state = D9;
		}
		break;
	case BadEnding4Scene::D9:
		if (Text::isTextFinished()) {
			transition = new TransitionScene(this, 3, true);
			GameManager::get()->pushScene(transition, true);
			cont = 0;
			state = D10;
		}
		break;
	case BadEnding4Scene::D10:
		cont += frameTime;
		if (cont > 3 * 1000 * 2) {
			// fondo
			bg = &sdlutils().images().at("CINEMATIC_BG_HOUSE");
			// música
			pantryMusic->pauseMusic();
			homeMusic->play(-1);
			// otros
			night = true; stolenBook = false;

			// protagonista
			anim->setTexture("Player_Casual", 6, 11, 1, 10);
			anim->setW(48);
			anim->setH(96);
			transform->setOrientation(north);
			straightMovement->reset(RelativeToGlobal::pointHouse({ 23, 7 }));

			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text, dialogues[6].character);
			state = D11;
		}
		break;
	case BadEnding4Scene::D11:
		finish = false;
		while (Text::isTextFinished() && !finish) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[contText].portrait, dialogues[contText].text, dialogues[contText].character);
			++contText;

			if (contText >= 30) {
				state = D35;
				finish = true;
			}
		}
		break;
	case BadEnding4Scene::D35:
		if (Text::isTextFinished()) {
			straightMovement->addPath(RelativeToGlobal::pointsHouse(BE4PathPlayer[1]));
			state = D37;
		}
		break;
	case BadEnding4Scene::D37:
		if (straightMovement->hasFinishedPath()) {
			contText = 31;

			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[contText].portrait, dialogues[contText].text, dialogues[contText].character);
			state = D38;
		}
		break;
	case BadEnding4Scene::D38:
		finish = false;
		while (Text::isTextFinished() && !finish) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[contText].portrait, dialogues[contText].text, dialogues[contText].character);
			++contText;

			if (contText >= 44) {
				state = LAST;
				finish = true;
			}
		}
		break;
	case BadEnding4Scene::LAST:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 1, true, true);
			GameManager::get()->pushScene(transition, true);
			homeMusic->pauseMusic();
			state = NONE;
		}
		break;
	case BadEnding4Scene::NONE:
		break;
	}
}

void BadEnding4Scene::addPathPantry(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}