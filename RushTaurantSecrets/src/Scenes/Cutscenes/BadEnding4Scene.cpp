#include "BadEnding4Scene.h"
#include "../../GameObjects/Dialogue.h"
#include "../../Structure/GameManager.h"
#include "ShowSkipTransitionScene.h"

BadEnding4Scene::BadEnding4Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding4.json");
	bg = &sdlutils().images().at("CINEMATIC_BG_PANTRY");
	top = &sdlutils().images().at("CINEMATIC_BG_PANTRY_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");
	tvFilter = &sdlutils().images().at("CINEMATIC_TV_FILTER");
	lectern = &sdlutils().images().at("CINEMATIC_PANTRY_LECTERN");
	reading = false; night = false; stolenBook = false;

	book = new GameObject(this);
	new Transform(book, Vector(RelativeToGlobal::pointPantry({ 23, 5 })), Vector(0,0), 48, 96);
	ap.height = 96;
	ap.width = 48;
	ap.initFrame = 15;
	ap.endFrame = 26;
	ap.currAnim = 7;
	new UIAnimator(book, "Player_1", ap, Vector(RelativeToGlobal::pointPantry({ 25, 5 })));

	thief = new CinematicNPC(this, "Thief_2", RelativeToGlobal::pointPantry({ 17, 5 }), 1);
	straightMovementThief = new StraightMovement(thief, 3);

	straightMovement = new StraightMovement(player, 2);

	playerPoints = { {Vector(20, 14)} };

	apNight.initFrame = 18;
	apNight.endFrame = 10;
	apNight.currAnim = 1;
	apNight.width = 48;
	apNight.height = 96;
	apNight.frameRate = 10;
}

void BadEnding4Scene::reset() {
	dialogueBox = nullptr;
	state = START;

	transform->setPos(RelativeToGlobal::pointPantry({ 20, 14 }));
	transform->setMovState(walking);
	straightMovement->changeSpeed(2);
	straightMovement->stop();

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

}

void BadEnding4Scene::update() {
	CinematicBaseScene::update();
	switch (state)
	{
	case BadEnding4Scene::START:
		straightMovement->addPath(RelativeToGlobal::pointsPantry(BE4PathPlayer[1]));
		straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[0]));
		state = D1;
		break;
	case BadEnding4Scene::D1:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = D2;
		}
		break;
	case BadEnding4Scene::D2:
		if (Text::isTextFinished() && straightMovementThief->hasFinishedPath()) {
			thief->getComponent<Transform>()->setOrientation(south);
			reading = true; stolenBook = true;
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D3;
		}
		break;
	case BadEnding4Scene::D3:
		if (Text::isTextFinished()) {
			reading = false;
			straightMovementThief->changeSpeed(8);
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[1]));
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = D4;
		}
		break;
	case BadEnding4Scene::D4:
		if (straightMovementThief->hasFinishedPath()) {
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[2]));
			transform->setOrientation(west);
			state = D5;
		}
		break;
	case BadEnding4Scene::D5:
		if (straightMovementThief->hasFinishedPath()) {
			straightMovementThief->addPath(RelativeToGlobal::pointsPantry(BE4PathThief[3]));
			state = D6;
		}
		break;
	case BadEnding4Scene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			state = D7;
		}
		break;
	case BadEnding4Scene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text);
			state = D8;
		}
		break;
	case BadEnding4Scene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
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
			night = true; stolenBook = false;
			auto anim = new CharacterAnimator(player, "Player_Casual", apNight);
			bg = &sdlutils().images().at("CINEMATIC_BG_HOUSE");
			transform->setOrientation(north);
			transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text);
			state = D11;
		}
		break;
	case BadEnding4Scene::D11:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[7].portrait, dialogues[7].text);
			state = D12;
		}
		break;
	case BadEnding4Scene::D12:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[8].portrait, dialogues[8].text);
			state = D13;
		}
		break;
	case BadEnding4Scene::D13:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[9].portrait, dialogues[9].text);
			state = D14;
		}
		break;
	case BadEnding4Scene::D14:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[10].portrait, dialogues[10].text);
			state = D15;
		}
		break;
	case BadEnding4Scene::D15:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[11].portrait, dialogues[11].text);
			state = D16;
		}
	case BadEnding4Scene::D16:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[12].portrait, dialogues[12].text);
			state = D17;
		}
	case BadEnding4Scene::D17:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[13].portrait, dialogues[13].text);
			state = D18;
		}
	case BadEnding4Scene::D18:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[14].portrait, dialogues[14].text);
			state = D19;
		}
	case BadEnding4Scene::D19:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[15].portrait, dialogues[15].text);
			state = D20;
		}
	case BadEnding4Scene::D20:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[16].portrait, dialogues[16].text);
			state = D21;
		}
	case BadEnding4Scene::D21:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[17].portrait, dialogues[17].text);
			state = D22;
		}
	case BadEnding4Scene::D22:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[18].portrait, dialogues[18].text);
			state = D23;
		}
	case BadEnding4Scene::D23:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[19].portrait, dialogues[19].text);
			state = D24;
		}
	case BadEnding4Scene::D24:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[20].portrait, dialogues[20].text);
			state = D25;
		}
	case BadEnding4Scene::D25:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[21].portrait, dialogues[21].text);
			state = D26;
		}
	case BadEnding4Scene::D26:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[22].portrait, dialogues[22].text);
			state = D27;
		}
	case BadEnding4Scene::D27:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[23].portrait, dialogues[23].text);
			state = D28;
		}
		break;
	case BadEnding4Scene::D28:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[24].portrait, dialogues[24].text);
			state = D29;
		}
		break;
	case BadEnding4Scene::D29:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[25].portrait, dialogues[25].text);
			state = D30;
		}
		break;
	case BadEnding4Scene::D30:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[26].portrait, dialogues[26].text);
			state = D31;
		}
		break;
	case BadEnding4Scene::D31:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[27].portrait, dialogues[27].text);
			state = D32;
		}
		break;
	case BadEnding4Scene::D32:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[28].portrait, dialogues[28].text);
			state = D33;
		}
		break;
	case BadEnding4Scene::D33:
		transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[29].portrait, dialogues[29].text);
			state = D34;
		}
		break; 
	case BadEnding4Scene::D34:
			transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
			if (Text::isTextFinished()) {
				dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
					font, dialogues[30].portrait, dialogues[30].text);
				state = D35;
			}
			break;
	case BadEnding4Scene::D35:
		if (Text::isTextFinished()) {
			straightMovement->addPath(RelativeToGlobal::pointsHouse(BE4PathPlayer[4]));
			state = D36;
		}
		else
			transform->setPos(RelativeToGlobal::pointHouse({ 23,7 }));
		break;
	case BadEnding4Scene::D36:
		if (straightMovement->hasFinishedPath()) {
			straightMovement->addPath(RelativeToGlobal::pointsHouse(BE4PathPlayer[5]));
			state = D37;
		}
		break;
	case BadEnding4Scene::D37:
		if (straightMovement->hasFinishedPath()) {
			transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[31].portrait, dialogues[31].text);
			state = D38;
		}
		break;
	case BadEnding4Scene::D38:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[32].portrait, dialogues[32].text);
			state = D39;
		}
		break;
	case BadEnding4Scene::D39:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 450), 700, 0.01 * 1000,
				font, dialogues[33].portrait, dialogues[33].text);
			state = D40;
		}
		break;
	case BadEnding4Scene::D40:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[34].portrait, dialogues[34].text);
			state = D41;
		}
		break;
	case BadEnding4Scene::D41:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[35].portrait, dialogues[35].text);
			state = D42;
		}
		break;
	case BadEnding4Scene::D42:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[36].portrait, dialogues[36].text);
			state = D43;
		}
		break;
	case BadEnding4Scene::D43:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[37].portrait, dialogues[37].text);
			state = D44;
		}
		break;
	case BadEnding4Scene::D44:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[38].portrait, dialogues[38].text);
			state = D45;
		}
		break;
		//
	case BadEnding4Scene::D45:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[39].portrait, dialogues[39].text);
			state = D46;
		}
		break;
	case BadEnding4Scene::D46:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[40].portrait, dialogues[40].text);
			state = D47;
		}
		break;
	case BadEnding4Scene::D47:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[41].portrait, dialogues[41].text);
			state = D48;
		}
		break;
	case BadEnding4Scene::D48:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[42].portrait, dialogues[42].text);
			state = D49;
		}
		break;
	case BadEnding4Scene::D49:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[43].portrait, dialogues[43].text);
			state = D50;
		}
		break;
	case BadEnding4Scene::D50:
		transform->setPos(RelativeToGlobal::pointHouse({ 21,5 }));
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 600), 700, 0.01 * 1000,
				font, dialogues[44].portrait, dialogues[44].text);
			state = LAST;
		}
		break;
	case BadEnding4Scene::LAST:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 1, true, true);
			GameManager::get()->pushScene(transition, true);
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