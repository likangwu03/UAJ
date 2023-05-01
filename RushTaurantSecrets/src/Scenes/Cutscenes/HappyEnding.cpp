#include "HappyEnding.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

HappyEnding::HappyEnding() {
	dialogues = GameManager::get()->getDialogueInfo("HappyEnding.json");
	
	bg = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM");
	filter = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM_NIGHT");

	nightMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	black = &sdlutils().images().at("Filter_Black");
	door = &sdlutils().images().at("CINEMATIC_BG_ROOM_DOOR");
	top = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM_WALL");
}

void HappyEnding::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void HappyEnding::reset() {
	dialogueBox = nullptr;
	state = START;
	timer = 0;
	dialogueN = 0;
	doorFrame = 0;

	transform->setPos(RelativeToGlobal::pointRestaurant(Vector(8.8, 2)));
	transform->setMovState(sleeping);
	transform->setOrientation(south);

	anim->setTexture("Player_Casual", 0, 0, 0, 10);
	anim->setH(96 * 1.5);
	anim->setW(48 * 1.5);

	straightMovement->changeSpeed(5);
	straightMovement->stop();

	filter->setOpacity(80);
	nightAmbience->setVolume(60);

	//nightAmbience->play(-1);
	//nightMusic->play(-1);
	nightAmbience->haltChannel();
	nightMusic->haltMusic();

	bg = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM");
	top = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM_WALL");


	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void HappyEnding::update() {
	CinematicBaseScene::update();
	switch (state) {
	case HappyEnding::START:
		if (timer >= DELAY) {
			transform->setMovState(sitting);
			transform->setOrientation(east);
			state = WAKE;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case HappyEnding::WAKE:
		if (timer >= DELAY) {
			transform->setOrientation(east);
			state = WINDOW;
			timer = 0;
			addPath(paths[0]);
		}
		else timer += frameTime;
		break;
	case HappyEnding::WINDOW:
		if (straightMovement->hasFinishedPath()) {
			transform->setOrientation(north);
			if (timer >= DELAY) {
				dialogueBox = new Dialogue(this, Vector(150, 550), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
				state = D2;
				dialogueN++;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case HappyEnding::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
			state = CLOSET;
			dialogueN++;
		}
		break;
	case HappyEnding::CLOSET:
		if (Text::isTextFinished()) {
			addPath(paths[1]);
			state = FADEIN1;
		}
		break;
	case HappyEnding::FADEIN1:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			transform->setOrientation(north);
			transition = new ShowSkipTransitionScene(this, 1, true);
			GameManager::get()->pushScene(transition, true);
			state = FADEOUT1;
		}
		break;
	case HappyEnding::FADEOUT1:
		if (GameManager::get()->getCurrentScene() != transition) {
			anim->setTexture("Player_1", 6, 11, 1, 10);
			transform->setMovState(idle);
			transform->setOrientation(north);
			transition = new ShowSkipTransitionScene(this, 1);
			GameManager::get()->pushScene(transition, true);
			state = D3;
		}
		break;
	case HappyEnding::D3:
		if (GameManager::get()->getCurrentScene() != transition) {
			dialogueBox = new Dialogue(this, Vector(150, 500), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
			dialogueN++;
			state = D4;
		}
		break;
	case HappyEnding::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
			dialogueN++;
			state = WALKDOOR;
		}
		break;
	case HappyEnding::WALKDOOR:
		if (Text::isTextFinished()) {
			addPath(paths[2]);
			state = OPENDOOR;
		}
		break;
	case HappyEnding::OPENDOOR:
		if (straightMovement->hasFinishedPath()) {
			transform->setOrientation(south);
			if (timer >= DOORFREQ && doorFrame < DOORFRAMES - 1) {
				doorFrame++;
				timer = 0;
			}
			else if (doorFrame < DOORFRAMES - 1) timer += frameTime;
			else {
				timer = 0;
				state = D5;
			}
		}
		break;
	case HappyEnding::D5:
		dialogueBox = new Dialogue(this, Vector(150, 500), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
		dialogueN++;
		state = WALKOUT;
		break;
	case HappyEnding::WALKOUT:
		if (Text::isTextFinished()) {
			addPath(paths[3]);
			state = D6;
		}
		break;
	case HappyEnding::D6:
		if (straightMovement->hasFinishedPath()) {
			if (timer >= DELAY) {
				dialogueBox = new Dialogue(this, Vector(150, 550), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
				dialogueN++;
				state = D7;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case HappyEnding::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
			dialogueN++;
			state = FADEIN2;
		}
		break;
	case HappyEnding::FADEIN2:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new ShowSkipTransitionScene(this, 1, true);
			GameManager::get()->pushScene(transition, true);
			state = FADEOUT2;
			addPath(paths[4]);
		}
		break;
	case HappyEnding::FADEOUT2:
		if (GameManager::get()->getCurrentScene() != transition) {
			bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_HAPPY_ENDING");
			top = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_ISLAND");

			transform->setPos(RelativeToGlobal::pointRestaurant(Vector(29,4.5)));
			anim->setH(96 * RESTSIZE);
			anim->setW(48 * RESTSIZE);
			
			straightMovement->stop();
			addPath(paths[5]);

			transition = new ShowSkipTransitionScene(this, 1);
			GameManager::get()->pushScene(transition, true);
			state = RESTAURANT;
		}
		break;
	case HappyEnding::RESTAURANT:
		addPath(paths[5]);
		state = OUT;
		break;

	//case HappyEnding::OUT:
	//	if (Text::isTextFinished()) {
	//		dialogueBox = nullptr;
	//		transition = new TransitionScene(this, 3, true, true);
	//		GameManager::get()->pushScene(transition);
	//		state = NONE;
	//	}
	//	break;

	}
	
}

void HappyEnding::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	if (state < RESTAURANT) {
		if (state < WALKOUT) {
			player->render();
			door->render(build_sdlrect(DOORW * doorFrame, 0, DOORW, DOORH), DOORPOS);
		}
		else {
			door->render(build_sdlrect(DOORW * doorFrame, 0, DOORW, DOORH), DOORPOS);
			player->render();
		}
		top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
		filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	}
	else {
		player->render();
		top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	}

	if ((state == FADEOUT1 || state == FADEOUT2) && GameManager::get()->getCurrentScene() != transition) {
		black->setOpacity(100);
		black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	}
}


void HappyEnding::finishScene() {
	if(transition != nullptr)
		delete transition;
	nightMusic->haltMusic();
	nightAmbience->haltChannel();
//	GameManager::get()->changeScene(GameManager::get()->getScene(sc_INTRO3), false);
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);

}