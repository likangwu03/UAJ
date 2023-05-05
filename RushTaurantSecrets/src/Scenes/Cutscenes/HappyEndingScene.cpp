#include "HappyEndingScene.h"
#include "../../Utilities/checkML.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"
#include "../../GameObjects/CinematicNPC.h"

HappyEndingScene::HappyEndingScene() {
	dialogues = GameManager::get()->getDialogueInfo("HappyEnding.json");
	
	filter = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM_NIGHT");

	cheer = &sdlutils().soundEffects().at("CHEER");

	black = &sdlutils().images().at("Filter_Black");
	door = &sdlutils().images().at("CINEMATIC_BG_ROOM_DOOR");
	top = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM_WALL");

	addClient("Client_1", Vector(5, 3.5), east);
	addClient("Client_2", Vector(5, 4.5), east);
	addClient("Client_3", Vector(9, 3.5), west);
	addClient("Client_4", Vector(9, 4.5), west);

	addClient("Client_5", Vector(12, 3.5), east);
	addClient("Client_6", Vector(12, 4.5), east);
	addClient("Client_7", Vector(16, 3.5), west);
	addClient("Client_8", Vector(16, 4.5), west);

	addClient("Client_9", Vector(8, 8.6), east);
	addClient("Client_10", Vector(12, 8.6), west);
	addClient("Client_11", Vector(10, 7), south);
	addClient("Client_12", Vector(10, 10.5), north);

	addClient("Client_13", Vector(15, 8.6), east);
	addClient("Client_1", Vector(19, 8.6), west);
	addClient("Client_8", Vector(17, 7), south);
	addClient("Client_4", Vector(17, 10.5), north);

	addClient("Client_7", Vector(6, 14.6), east);
	addClient("Client_3", Vector(10, 14.6), west);
	addClient("Client_13", Vector(8, 13), south);
	addClient("Client_11", Vector(8, 16.5), north);

	addClient("Client_14", Vector(13, 14.6), east);
	addClient("Client_15", Vector(17, 14.6), west);
	addClient("Client_16", Vector(15, 13), south);
	addClient("Client_17", Vector(15, 16.5), north);
	addClient("Client_18", Vector(17, 16), west, idle);

	addClient("Client_10", Vector(20, 14.6), east);
	addClient("Client_4", Vector(24, 14.6), west);
	addClient("Client_1", Vector(22, 13), south);
	addClient("Client_8", Vector(22, 16.5), north);


	waiter1 = new CinematicNPC(this, "Waiter_1", Vector(0, 0), 2);
	waiter1->getComponent<CharacterAnimator>()->setW(48 * RESTSIZE);
	waiter1->getComponent<CharacterAnimator>()->setH(96 * RESTSIZE);

	waiter2 = new CinematicNPC(this, "Waiter_2", Vector(0, 0), 2);
	waiter2->getComponent<CharacterAnimator>()->setW(48 * RESTSIZE);
	waiter2->getComponent<CharacterAnimator>()->setH(96 * RESTSIZE);
	
	guard1 = new CinematicNPC(this, "Guard_1", Vector(0, 0), 0);
	guard1->getComponent<CharacterAnimator>()->setW(48 * 1.5);
	guard1->getComponent<CharacterAnimator>()->setH(96 * 1.5);
	guard1->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointRestaurant({ 30,4 }));
	guard1->getComponent<Transform>()->setOrientation(west);

	guard2 = new CinematicNPC(this, "Guard_2", Vector(0, 0), 0);
	guard2->getComponent<CharacterAnimator>()->setW(48 * 1.5);
	guard2->getComponent<CharacterAnimator>()->setH(96 * 1.5);
	guard2->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointRestaurant({ 34,6 }));
	guard2->getComponent<Transform>()->setOrientation(south);


}

void HappyEndingScene::addPath(const vector<Vector>& points, GameObject* object) {
	object->getComponent<StraightMovement>()->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void HappyEndingScene::reset() {
	dialogueBox = nullptr;
	state = INIT;
	timer = 0;
	dialogueN = 0;
	doorFrame = 0;

	straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[0][0]));
	straightMovement->setIsWalking(false);
	transform->setMovState(sleeping);

	anim->setTexture("Player_Casual", 0, 0, 0, 10);
	anim->setH(96 * 1.6);
	anim->setW(48 * 1.6);

	straightMovement->changeSpeed(5);

	filter->setOpacity(80);
	
	music = &sdlutils().musics().at("HAPPY_MORNING_MUSIC");
	musicVol = 20;
	music->setMusicVolume(musicVol);

	ambience = &sdlutils().soundEffects().at("BIRDS");
	ambience->setVolume(60);
	cheer->setVolume(100);

	

	bg = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM");
	top = &sdlutils().images().at("CINEMATIC_BG_PROTA_ROOM_WALL");

	for (auto c : npcs) {
		c.npc->getComponent<StraightMovement>()->reset(c.pos);
		c.npc->getComponent<StraightMovement>()->setIsWalking(false);
		c.npc->getComponent<Transform>()->setOrientation(c.orientation);
		c.npc->getComponent<Transform>()->setMovState(c.state);
	}
	waiter1->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointRestaurant(waiterPaths[0][0]));
	waiter2->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointRestaurant(waiterPaths[1][0]));

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}


void HappyEndingScene::update() {
	CinematicBaseScene::update();
	switch (state) {
	case HappyEndingScene::INIT:
		ambience->play(-1);
		music->play(-1);
		state = START;
		break;
	case HappyEndingScene::START:
		if (timer >= DELAY * 2) {
			transform->setMovState(sitting);
			transform->setOrientation(east);
			state = WAKE;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case HappyEndingScene::WAKE:
		if (timer >= DELAY) {
			transform->setOrientation(east);
			state = WINDOW;
			timer = 0;
			addPath(paths[0], player);
		}
		else timer += frameTime;
		break;
	case HappyEndingScene::WINDOW:
		if (straightMovement->hasFinishedPath()) {
			transform->setOrientation(north);
			if (timer >= DELAY) {
				dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
				state = D2;
				dialogueN++;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case HappyEndingScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = CLOSET;
			dialogueN++;
		}
		break;
	case HappyEndingScene::CLOSET:
		if (Text::isTextFinished()) {
			addPath(paths[1], player);
			state = FADEIN1;
		}
		break;
	case HappyEndingScene::FADEIN1:
		if (straightMovement->hasFinishedPath()) {
			transform->setOrientation(north);
			transition = new TransitionScene(this, 1, true);
			GameManager::get()->pushScene(transition, true);
			state = FADEOUT1;
		}
		break;
	case HappyEndingScene::FADEOUT1:
		if (GameManager::get()->getCurrentScene() != transition) {
			(&sdlutils().soundEffects().at("CLOTHES"))->play();
			anim->setTexture("Player_1", 6, 11, 1, 10);
			transform->setOrientation(north);
			transition = new TransitionScene(this, 1);
			GameManager::get()->pushScene(transition, true);
			state = D3;
		}
		break;
	case HappyEndingScene::D3:
		if (GameManager::get()->getCurrentScene() != transition) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			dialogueN++;
			state = D4;
		}
		break;
	case HappyEndingScene::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			dialogueN++;
			state = WALKDOOR;
		}
		break;
	case HappyEndingScene::WALKDOOR:
		if (Text::isTextFinished()) {
			addPath(paths[2], player);
			state = OPENDOOR;
		}
		break;
	case HappyEndingScene::OPENDOOR:
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
				(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
			}
		}
		break;
	case HappyEndingScene::D5:
		dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
		dialogueN++;
		state = WALKOUT;
		break;
	case HappyEndingScene::WALKOUT:
		if (Text::isTextFinished()) {
			addPath(paths[3], player);
			state = D6;
		}
		break;
	case HappyEndingScene::D6:
		if (straightMovement->hasFinishedPath()) {
			if (timer >= DELAY) {
				dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
				dialogueN++;
				state = D7;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case HappyEndingScene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			dialogueN++;
			state = FADEIN2;
		}
		break;
	case HappyEndingScene::FADEIN2:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 1, true);
			GameManager::get()->pushScene(transition, true);
			state = FADEOUT2;
			addPath(paths[4], player);
		}
		break;
	case HappyEndingScene::FADEOUT2:
		if (GameManager::get()->getCurrentScene() != transition) {
			bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_HAPPY_ENDING");
			top = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_ISLAND");

			straightMovement->changeSpeed(2);
			straightMovement->reset(RelativeToGlobal::pointRestaurant(paths[5][0]));
			anim->setH(96 * RESTSIZE);
			anim->setW(48 * RESTSIZE);
			
			addPath(paths[5], player);
			straightMovement->enableRoundTripByLaps(1);
			addPath(waiterPaths[0], waiter1);
			addPath(waiterPaths[1], waiter2);

			ambience->haltChannel();
			ambience = &sdlutils().soundEffects().at("CROWD");
			ambience->setVolume(80);
			ambience->play();

			transition = new TransitionScene(this, 1);
			GameManager::get()->pushScene(transition, true);
			state = RESTAURANT;
		}
		break;
	case HappyEndingScene::RESTAURANT:
		if (waiter2->getComponent<StraightMovement>()->hasFinishedPath()) {
			state = FADEIN3;
		}
		break;
	case HappyEndingScene::FADEIN3:
		transition = new TransitionScene(this, 1, true);
		GameManager::get()->pushScene(transition, true);
		state = FADEOUT3;
		break;
	case HappyEndingScene::FADEOUT3:
		if (GameManager::get()->getCurrentScene() != transition) {
			bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY_HAPPY_ENDING");
			transition = new TransitionScene(this, 1);
			
			ambience->setVolume(60);

			GameManager::get()->pushScene(transition, true);
			state = PANTRY;
		}
		break;
	case HappyEndingScene::PANTRY:
		if (timer >= DELAY * 2) {
			timer = 0;
			state = FADEIN4;
		}
		else timer += frameTime;
		break;
	case HappyEndingScene::FADEIN4:
		transition = new TransitionScene(this, 1, true);
		GameManager::get()->pushScene(transition, true);
		state = FADEOUT4;
		break;
	case HappyEndingScene::FADEOUT4:
		if (GameManager::get()->getCurrentScene() != transition) {
			bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_HAPPY_ENDING");
			transition = new TransitionScene(this, 1);

			straightMovement->reset(RelativeToGlobal::pointRestaurant({ 28,14 }));
			transform->setOrientation(west);

			waiter1->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointRestaurant({ 28,13 }));
			waiter1->getComponent<Transform>()->setOrientation(west);

			waiter2->getComponent<StraightMovement>()->reset(RelativeToGlobal::pointRestaurant({ 28,15 }));
			waiter2->getComponent<Transform>()->setOrientation(west);

			ambience->setVolume(80);

			GameManager::get()->pushScene(transition, true);
			state = CELEBRATE;
		}
		break;
	case HappyEndingScene::CELEBRATE:
		if (timer >= DELAY * 2) {
			timer = 0;
			state = D8;
		}
		else timer += frameTime;
		break;
	case HappyEndingScene::D8:
		dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
		state = D9;
		dialogueN++;
		break;
	case HappyEndingScene::D9:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D10;
			dialogueN++;
		}
		break;
	case HappyEndingScene::D10:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D11;
			dialogueN++;
		}
		break;
	case HappyEndingScene::D11:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = D12;
			dialogueN++;
		}
		break;
	case HappyEndingScene::D12:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), BOXW, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text, dialogues[dialogueN].character);
			state = OUT;
			dialogueN++;
			cheer->play();
		}
		break;
	case HappyEndingScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition);
			state = NONE;
		}
		break;
	case HappyEndingScene::NONE:
		if (musicVol > 0) musicVol-= 0.1;
		else if (musicVol < 0) musicVol = 0;
		music->setMusicVolume(musicVol);
		break;
	}
	
}


void HappyEndingScene::addClient(string txt, Vector pos, GOOrientation orientation, movementState state) {
	CinematicNPC* cl = new CinematicNPC(this, txt, Vector(0, 0), 0);
	cl->getComponent<CharacterAnimator>()->setW(48 * RESTSIZE);
	cl->getComponent<CharacterAnimator>()->setH(96 * RESTSIZE);
	const vector<Vector> pt = RelativeToGlobal::pointsRestaurant({ pos });
	npcs.push_back({ cl, pt[0], state, orientation});
}

void HappyEndingScene::renderCinematic() {
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
	else if (state < PANTRY) {
		player->render();
		top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
		waiter1->render();
		waiter2->render();

		for (auto c : npcs) {
			c.npc->render();
		}
	}
	else if (state < CELEBRATE) {
		guard1->render();
		guard2->render();
	}
	else {	
		top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
		waiter1->render();
		player->render();
		waiter2->render();

		for (auto c : npcs) {
			c.npc->render();
		}
	}

	if ((state == FADEOUT1 || state == FADEOUT2 || state == FADEOUT3 || state == FADEOUT4) && GameManager::get()->getCurrentScene() != transition) {
		black->setOpacity(100);
		black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	}
}


void HappyEndingScene::finishScene() {
	if(transition != nullptr)
		delete transition;
	music->haltMusic();
	ambience->haltChannel();
	cheer->haltChannel();

	GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), false);
	GameManager::get()->getScene(sc_MAINMENU)->resumeSound();
	CinematicBaseScene::finishScene();

}