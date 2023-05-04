#include "BadEnding2Scene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"
#include "../../GameObjects/CinematicNPC.h"

BadEnding2Scene::BadEnding2Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding2.json");
	
	black = &sdlutils().images().at("Filter_Black");
	phonecall = &sdlutils().soundEffects().at("TELEPHONE");
}

void BadEnding2Scene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void BadEnding2Scene::reset() {
	dialogueBox = nullptr;
	state = INIT;
	timer = 0;
	dialogueN = 0;

	straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[0][0]));
	//straightMovement->setIsWalking(false);
	//transform->setMovState(idle);
	//transform->setOrientation(south);


	anim->setTexture("Player_1", 0, 0, 0, 10);
	anim->setH(96 * RESTSIZE);
	anim->setW(48 * RESTSIZE);

	straightMovement->changeSpeed(3);

	
	music = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	musicVol = 20;
	music->setMusicVolume(musicVol);

	ambience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	ambience->setVolume(60);

	bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT");
	top = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_TOP_BAD_ENDING_2");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	filter->setOpacity(80);


	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}


void BadEnding2Scene::update() {
	CinematicBaseScene::update();
	switch (state) {
	case BadEnding2Scene::INIT:
		ambience->play(-1);
		music->play(-1);
		state = START;
		break;
	case BadEnding2Scene::START:
		if (GameManager::get()->getCurrentScene() != transition) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D2;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D3;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D4;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D5;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D6;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D7;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D8;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = WALKOUT;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::WALKOUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			addPath(paths[0]);
			state = FADEIN1;
		}
		break;
	case BadEnding2Scene::FADEIN1:
		if (straightMovement->hasFinishedPath()) {
			transition = new TransitionScene(this, 1, true);
			GameManager::get()->pushScene(transition, true);
			state = FADEOUT1;
		}
		break;
	case BadEnding2Scene::FADEOUT1:
		if (GameManager::get()->getCurrentScene() != transition) {
			bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM");
			top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");

			anim->setTexture("Player_Casual", 0, 0, 0, 10);
			//transform->setMovState(idle);
			//transform->setOrientation(west);

			anim->setH(96 * 1.7);
			anim->setW(48 * 1.7);
			
			straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[1][0]));
			addPath(paths[1]);
			straightMovement->changeSpeed(5);
			
			transition = new TransitionScene(this, 1);
			GameManager::get()->pushScene(transition, true);
			state = WALKIN;
		}
		break;
	case BadEnding2Scene::WALKIN:
		if (straightMovement->hasFinishedPath()) {
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
			addPath(paths[2]);
			state = D9;
		}
		break;
	case BadEnding2Scene::D9:
		if (straightMovement->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D10;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D10:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D11;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D11:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D12;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D12:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = FADEIN2;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::FADEIN2:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			
			transition = new TransitionScene(this, 3, true);
			GameManager::get()->pushScene(transition, true);


			addPath(paths[3]);
			state = RING;
		}
		break;
	case BadEnding2Scene::RING:
		if (GameManager::get()->getCurrentScene() != transition) {
			bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
			filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");

			ambience->haltChannel();
			ambience = &sdlutils().soundEffects().at("BIRDS");
			ambience->play(-1);

			anim->setTexture("Player_1", 0, 0, 0, 10);
			//transform->setMovState(idle);
			//transform->setOrientation(west);

			anim->setH(96 * 1.3);
			anim->setW(48 * 1.3);

			straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[4][0]));
			state = D13;
		}
		break;
	case BadEnding2Scene::D13:
		if (GameManager::get()->getCurrentScene() != transition && timer >= DELAY) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D14;
			dialogueN++;

			timer = 0;
			phonecall->play(-1);
		}
		else timer += frameTime;
		break;
	case BadEnding2Scene::D14:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D15;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D15:
		if (Text::isTextFinished()) {
			phonecall->haltChannel();
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D16;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D16:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D17;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D17:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D18;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D18:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D19;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D19:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D20;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D20:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D21;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D21:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D22;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D22:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D23;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D23:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			if (GameManager::get()->getHasEverKilled().first) {
				state = D24;
				dialogueN++;
			}
			else {
				state = FADEOUT2;
				dialogueN += 4;
			}
		}
		break;
	case BadEnding2Scene::D24:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D25;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D25:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D26;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::D26:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = FADEOUT2;
			dialogueN++;
		}
		break;
	case BadEnding2Scene::FADEOUT2:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;

			ambience->haltChannel();
			ambience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
			ambience->play(-1);

			addPath(paths[4]);
			transition = new TransitionScene(this, 2);
			GameManager::get()->pushScene(transition, true);
			state = D27;
		}
		break;

	case BadEnding2Scene::D27:
		if (GameManager::get()->getCurrentScene() != transition) {
			if (timer >= DELAY * 2) {
				dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
				state = FADEIN3;
				dialogueN++;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case BadEnding2Scene::FADEIN3:
		if (straightMovement->hasFinishedPath() && Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 2, true);
			GameManager::get()->pushScene(transition, true);
			addPath(paths[5]);
			state = FADEOUT3;
		}
		break;
	case BadEnding2Scene::FADEOUT3:
		if (GameManager::get()->getCurrentScene() != transition) {

			anim->setH(96 * RESTSIZE);
			anim->setW(48 * RESTSIZE);

			bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT");
			top = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_TOP_BAD_ENDING_2");
			//transform->setMovState(idle);
			//transform->setOrientation(west);

			straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[6][0]));
			addPath(paths[6]);

			transition = new TransitionScene(this, 2);
			GameManager::get()->pushScene(transition, true);
			state = D28;
		}
		break;
	case BadEnding2Scene::D28:
		if (straightMovement->hasFinishedPath()) {
			if (timer >= DELAY) {
				dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
				state = FADEIN4;
				dialogueN++;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case BadEnding2Scene::FADEIN4:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 2, true);
			GameManager::get()->pushScene(transition, true);
			state = D29;
		}
		break;
	case BadEnding2Scene::D29:
		if (GameManager::get()->getCurrentScene() != transition) {
			if (timer >= DELAY) {
				(&sdlutils().soundEffects().at("START_FIRE"))->play();

				dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
				state = OUT;
				dialogueN++;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case BadEnding2Scene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
		}
		break;
	case BadEnding2Scene::NONE:
		if (musicVol > 0) musicVol-= 0.1;
		else if (musicVol <= 0) {
			musicVol = 0;
			finishScene();
		}
		music->setMusicVolume(musicVol);
		break;
	}
	
}


void BadEnding2Scene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	
	if(state <= FADEOUT2 || (state > FADEOUT3 && black->getOpacity() < 100) ) top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	if (state > FADEOUT1 && state <= FADEOUT3) filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

	if ( ((state == FADEOUT1 || state == FADEOUT2 || state == FADEOUT3) && GameManager::get()->getCurrentScene() != transition) 
		|| ( ((state > FADEIN2 && state <= FADEOUT2) || state >= FADEIN4) && black->getOpacity() >= 100)) {
		black->setOpacity(100);
		black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	}
}


void BadEnding2Scene::finishScene() {
	if(transition != nullptr)
		delete transition;
	music->haltMusic();
	ambience->haltChannel();

	GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), false);
	GameManager::get()->getScene(sc_MAINMENU)->resumeSound();
	CinematicBaseScene::finishScene();
}