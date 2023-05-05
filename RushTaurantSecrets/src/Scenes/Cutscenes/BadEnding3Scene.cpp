#include "BadEnding3Scene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"
#include "../../GameObjects/CinematicNPC.h"

BadEnding3Scene::BadEnding3Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding3.json");
	
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY_FREEZER");
	top = &sdlutils().images().at("CINEMATIC_BG_PANTRY_TOP");

	music = &sdlutils().musics().at("PANTRY_MUSIC");
	siren = &sdlutils().soundEffects().at("SIREN");

	black = &sdlutils().images().at("Filter_Black");


	thief = new CinematicNPC(this, "Thief_3", Vector(0, 0), 3);
	thief->getComponent<CharacterAnimator>()->setW(48 * PANTRYSIZE);
	thief->getComponent<CharacterAnimator>()->setH(96 * PANTRYSIZE);
	
	police = new CinematicNPC(this, "Police_1", Vector(0, 0), 3);
	police->getComponent<CharacterAnimator>()->setW(48 * PANTRYSIZE);
	police->getComponent<CharacterAnimator>()->setH(96 * PANTRYSIZE);
	police->getComponent<StraightMovement>()->changeSpeed(4);

	anim->setTexture("Player_1", 0, 0, 0, 10);
	anim->setH(96 * PANTRYSIZE);
	anim->setW(48 * PANTRYSIZE);
}

void BadEnding3Scene::addPath(const vector<Vector>& points, GameObject* object) {
	object->getComponent<StraightMovement>()->addPath(RelativeToGlobal::pointsPantry(points));
}

void BadEnding3Scene::reset() {
	dialogueBox = nullptr;
	state = INIT;
	timer = 0;
	dialogueN = 0;

	straightMovement->reset(RelativeToGlobal::pointPantry(paths[0][0]));
	/*
	straightMovement->setIsWalking(false);
	transform->setMovState(idle);
	transform->setOrientation(south);
	*/

	straightMovement->changeSpeed(3);

	thief->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointPantry(thiefPaths[0][0]));
	// thief->getComponent<StraightMovement>()->setIsWalking(false);
	thief->getComponent<StraightMovement>()->changeSpeed(1);
	// thief->getComponent<Transform>()->setMovState(idle);
	// thief->getComponent<Transform>()->setOrientation(north);

	police->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointPantry(policePaths[0][0]));
	/*
	police->getComponent<Transform>()->setMovState(idle);
	police->getComponent<StraightMovement>()->setIsWalking(false);
	*/

	music->setMusicVolume(GameManager::instance()->getMasterVolume());
	siren->setVolume(GameManager::instance()->getSoundEffectsVolume());
	(&sdlutils().soundEffects().at("OPEN_DOOR"))->setVolume(GameManager::instance()->getSoundEffectsVolume());

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}


void BadEnding3Scene::update() {
	CinematicBaseScene::update();

	if(state >= GUN && police->getComponent<StraightMovement>()->hasFinishedPath())
		police->getComponent<Transform>()->setMovState(shooting);

	switch (state) {
	case BadEnding3Scene::INIT:
		music->play(-1);
		state = START;
		break;
	case BadEnding3Scene::START:
		if (GameManager::get()->getCurrentScene() != transition) {
			addPath(thiefPaths[0], thief);
			//thief->getComponent<StraightMovement>()->setIsWalking(true);
			state = WALK;
		}
		break;
	case BadEnding3Scene::WALK:
		thief->getComponent<Transform>()->setOrientation(north);
		if (thief->getComponent<StraightMovement>()->hasFinishedPath()){
			state = ENTER;
			addPath(paths[0], player);
			//straightMovement->setIsWalking(true);
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
		}
		break;
	case BadEnding3Scene::ENTER:
		if (straightMovement->hasFinishedPath()) {
			thief->getComponent<Transform>()->setOrientation(south);
			if (timer >= DELAY) {
				dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
				state = D2;
				dialogueN++;
				timer = 0;
			}
			else timer += frameTime;
		}
		else thief->getComponent<Transform>()->setOrientation(north);
		break;
	case BadEnding3Scene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D3;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D4;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = RUN;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::RUN:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			addPath(thiefPaths[1], thief);
			straightMovement->changeSpeed(5);
			thief->getComponent<StraightMovement>()->changeSpeed(5);
			addPath(paths[1], player);
			state = FALL;
		}
		break;
	case BadEnding3Scene::FALL:
		if (thief->getComponent<StraightMovement>()->hasFinishedPath()) {
			// se cae
			thief->getComponent<Transform>()->setMovState(fallen);

			// corregir la posición
			thief->getComponent<StraightMovement>()->setActive(false);
			Transform* thiefTransform = thief->getComponent<Transform>();
			Vector thiefPos = thiefTransform->getPos();
			thiefTransform->setPos(Vector(thiefPos.getX(), thiefPos.getY() + thiefTransform->getW() / 2));

			state = GETUP;
		}
		break;
	case BadEnding3Scene::GETUP:
		if (timer >= DELAY) {
			// se levanta
			// devolver a la posición original
			Transform* thiefTransform = thief->getComponent<Transform>();
			Vector thiefPos = thiefTransform->getPos();
			thiefTransform->setPos(Vector(thiefPos.getX(), thiefPos.getY() - thiefTransform->getW() / 2));
			thief->getComponent<StraightMovement>()->setActive(true);
			
			state = GETOUT;
			timer = 0;
			addPath(thiefPaths[2], thief);
		}
		else timer += frameTime;
		break;

	case BadEnding3Scene::GETOUT:
		if (straightMovement->hasFinishedPath()) {
			transform->setOrientation(west);
			if (timer >= DELAY) {
				siren->play(-1);
				state = D5;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case BadEnding3Scene::D5:
		if (timer >= DELAY) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D6;
			dialogueN++;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case BadEnding3Scene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D7;
			dialogueN++;
			addPath(policePaths[0], police);
		}
		break;
	case BadEnding3Scene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = GUN;

		}
		break;
	case BadEnding3Scene::GUN:
		if (timer >= DELAY * 2) {
			state = D8;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case BadEnding3Scene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D9;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::D9:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D10;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::D10:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D11;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::D11:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D12;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::D12:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D13;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::D13:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D14;
			dialogueN++;

			transition = new ShowSkipTransitionScene(this, 2, true);
			GameManager::get()->pushScene(transition, true);
		}
		break;
	case BadEnding3Scene::D14:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = OUT;
			dialogueN++;
		}
		break;
	case BadEnding3Scene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
		}
		break;
	case BadEnding3Scene::NONE:
		if (musicVol > 0) musicVol-= 0.1;
		else if (musicVol <= 0) {
			musicVol = 0;
			finishScene();
		}
		music->setMusicVolume(musicVol);
		siren->setVolume(musicVol);
		break;
	}
	
}


void BadEnding3Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	thief->render();
	police->render();

	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

	if (state >= D13 && black->getOpacity() >= 100 ) {
		black->setOpacity(100);
		black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	}
}


void BadEnding3Scene::finishScene() {
	if(transition != nullptr)
		delete transition;
	music->haltMusic();
	siren->haltChannel();

	GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), false);
	GameManager::get()->getScene(sc_MAINMENU)->resumeSound();
	CinematicBaseScene::finishScene();
}