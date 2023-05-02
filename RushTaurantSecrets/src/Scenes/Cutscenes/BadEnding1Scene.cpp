#include "BadEnding1Scene.h"
#include "../../Utilities/checkML.h"
#include "../TransitionScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

void BadEnding1Scene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

BadEnding1Scene::BadEnding1Scene() {
	dialogues = GameManager::get()->getDialogueInfo("BadEnding1.json");

	playerPoints = { {Vector(26, 11)} };
	playerPoints2 = { {Vector(19, 14)} };
	client1Points = { {Vector(40, 14)} };
	client2Points = { {Vector(40, 15)} };

	dramaticMusic = &sdlutils().musics().at("DRAMATIC_MUSIC");

	bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT");
	top = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_TOP");

	transition = nullptr;
	cont = 0;

	/*
	player = new GameObject(this);
	transform = new Transform(player, RelativeToGlobal::pointRestaurant(Vector(20, 11)), Vector(0, 0), 48, 96);
	straightMovement = new StraightMovement(player, 5);
	Animator::AnimParams ap;
	ap.initFrame = 18;
	ap.endFrame = 18;
	ap.currAnim = 1;
	auto anim = new CharacterAnimator(player, "Player_1", ap);
	*/

	phonecall = &sdlutils().soundEffects().at("PHONECALL");
	
	client1 = new CinematicNPC(this, "Client_3", Vector(0, 0), 1);
	straightMovementc1 = new StraightMovement(client1, 3);
	client2 = new CinematicNPC(this, "Client_5", Vector(0,0), 1);
	straightMovementc2 = new StraightMovement(client2, 3);

	auto clAnim = client1->getComponent<CharacterAnimator>();
	clAnim->setW(48 * RESIZEFACTOR);
	clAnim->setH(96 * RESIZEFACTOR);

	clAnim = client2->getComponent<CharacterAnimator>();
	clAnim->setW(48 * RESIZEFACTOR);
	clAnim->setH(96 * RESIZEFACTOR);
}

void BadEnding1Scene::reset() {
	dialogueBox = nullptr;
	state = START;
	transition = nullptr;
	cont = 0;

	straightMovement->reset(RelativeToGlobal::pointRestaurant({ 20, 11 }));
	//transform->setPos(RelativeToGlobal::pointRestaurant({ 20, 11 }));
	//transform->setMovState(walking);

	anim->setW(48 * RESIZEFACTOR);
	anim->setH(96 * RESIZEFACTOR);

	StraightMovement* s1 = client1->getComponent<StraightMovement>();
	s1->reset(RelativeToGlobal::pointRestaurant({ 25, 14 }));
	StraightMovement* s2 = client2->getComponent<StraightMovement>();
	s2->reset(RelativeToGlobal::pointRestaurant({ 25, 15 }));
	/*
	auto tr = client1->getComponent<Transform>();
	tr->setPos(RelativeToGlobal::pointRestaurant({ 25, 14 }));
	tr = client2->getComponent<Transform>();
	tr->setPos(RelativeToGlobal::pointRestaurant({ 25, 15 }));
	*/

	//straightMovement->stop();

	bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT");
	top = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_TOP");

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}

}

void BadEnding1Scene::renderCinematic()
{
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	client1->render();
	client2->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void BadEnding1Scene::finishScene() {
	if (transition != nullptr)
		delete transition;
	//GameManager::get()->changeScene(GameManager::get()->getScene(sc_GAMEOVER));
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART));

	dramaticMusic->haltMusic();
}

void BadEnding1Scene::update()
{
	CinematicBaseScene::update();
	switch (state)
	{
	case BadEnding1Scene::START:
		dramaticMusic->play(-1);
		addPath(playerPoints);
		straightMovementc1->addPath(RelativeToGlobal::pointsRestaurant(client1Points));
		straightMovementc2->addPath(RelativeToGlobal::pointsRestaurant(client2Points));
		state = ARRIVE;
		break;
	case BadEnding1Scene::ARRIVE:
		/*
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
		}
		*/
		if (straightMovementc1->hasFinishedPath() && straightMovementc2->hasFinishedPath()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			client1->setAlive(false);
			client2->setAlive(false);
			state = D1;
		}
		break;
	case BadEnding1Scene::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D2;
		}
		break;
	case BadEnding1Scene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = RESTAURANT_FADEOUT;
		}
		break;
	case BadEnding1Scene::RESTAURANT_FADEOUT:
		if (Text::isTextFinished()) {
			transition = new TransitionScene(this, START_TIME, true);
			GameManager::get()->pushScene(transition, true);
			state = D3;
			cont = 0;
		}
		break;
	case BadEnding1Scene::D3:
		cont += frameTime;
		if (cont > START_TIME * 1000 * 2) {

			straightMovement->reset(Vector(RelativeToGlobal::pointRestaurant(Vector(19, 22))));
			//transform->setPos(Vector(RelativeToGlobal::pointRestaurant(Vector(19, 22))));
			anim->setW(48);
			anim->setH(96);

			bg = &sdlutils().images().at("CINEMATIC_BG_HOUSE");
			top->setOpacity(0.0f);
			addPath(playerPoints2);
			transform->setOrientation(north);
			state = PHONECALL;
		}
		break;
	case BadEnding1Scene::PHONECALL:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(phone);
			dialogueBox = new Dialogue(this, Vector(145, 550), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			phonecall->play(-1);
			state = D4;
		}
		break;
	case BadEnding1Scene::D4:
		cont += frameTime;
		if (cont > START_TIME * 1000) {
			if (Text::isTextFinished()) {
				dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
					font, dialogues[4].portrait, dialogues[4].text);
				phonecall->haltChannel();
				state = D5;
			}
		}
		break;
	case BadEnding1Scene::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
			state = D6;
		}
		break;
	case BadEnding1Scene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text);
			state = D7;
		}
		break;
	case BadEnding1Scene::D7:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[7].portrait, dialogues[7].text);
			state = D8;
		}
		break;
	case BadEnding1Scene::D8:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[8].portrait, dialogues[8].text);
			state = D9;
		}
		break;
	case BadEnding1Scene::D9:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[9].portrait, dialogues[9].text);
			state = D10;
		}
		break;
	case BadEnding1Scene::D10:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[10].portrait, dialogues[10].text);
			state = D11;
		}
		break;
	case BadEnding1Scene::D11:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[11].portrait, dialogues[11].text);
			state = D12;
		}
		break;
	case BadEnding1Scene::D12:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[12].portrait, dialogues[12].text);
			state = D13;
		}
		break;
	case BadEnding1Scene::D13:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[13].portrait, dialogues[13].text);
			state = D14;
		}
		break;
	case BadEnding1Scene::D14:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[14].portrait, dialogues[14].text);
			state = D15;
		}
		break;
	case BadEnding1Scene::D15:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[15].portrait, dialogues[15].text);
			state = D16;
		}
		break;
	case BadEnding1Scene::D16:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[16].portrait, dialogues[16].text);
			state = D17;
		}
		break;
	case BadEnding1Scene::D17:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[17].portrait, dialogues[17].text);
			state = D18;
		}
		break;
	case BadEnding1Scene::D18:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[18].portrait, dialogues[18].text);
			state = D19;
		}
		break;
		//aqui
	case BadEnding1Scene::D19:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[19].portrait, dialogues[19].text);
			state = BEDROOM_FADEOUT;
		}
		break;
	case BadEnding1Scene::BEDROOM_FADEOUT:
		if (Text::isTextFinished()) {
			if (transition != nullptr)
				delete transition;
			transition = new TransitionScene(this, START_TIME, true);
			GameManager::get()->pushScene(transition, true);
			state = RESTAURANT_FADEIN;
			cont = 0;
		}
		break;
	case BadEnding1Scene::RESTAURANT_FADEIN:
		cont += frameTime;
		if (cont > START_TIME * 1000) {
			cont = 0;
			state = D20;
		}
		break;
	case BadEnding1Scene::D20:
		cont += frameTime;
		if (cont > START_TIME * 1000) {
			anim->setW(48 * RESIZEFACTOR);
			anim->setH(96 * RESIZEFACTOR);

			straightMovement->reset(RelativeToGlobal::pointRestaurant({ 20, 11 }));
			//transform->setPos(RelativeToGlobal::pointRestaurant({ 20, 11 }));
			bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT");
			transform->setOrientation(south);
			dialogueBox = new Dialogue(this, Vector(145, 500), 700, 0.01 * 1000,
				font, dialogues[20].portrait, dialogues[20].text);
			state = D21;
		}
		break;
	case BadEnding1Scene::D21:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[21].portrait, dialogues[21].text);
			state = D22;
		}
		break;
	case BadEnding1Scene::D22:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[22].portrait, dialogues[22].text);
			state = D23;
		}
		break;
	case BadEnding1Scene::D23:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[23].portrait, dialogues[23].text);
			state = D24;
		}
		break;
	case BadEnding1Scene::D24:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[24].portrait, dialogues[24].text);
			state = D25;
		}
		break;
	case BadEnding1Scene::D25:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[25].portrait, dialogues[25].text);
			state = D26;
		}
		break;
	case BadEnding1Scene::D26:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 550), 700, 0.01 * 1000,
				font, dialogues[26].portrait, dialogues[26].text);
			state = D27;
		}
		break;
	case BadEnding1Scene::D27:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[27].portrait, dialogues[27].text);
			state = OUT;
		}
		break;
	case BadEnding1Scene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			state = NONE;
			if (transition != nullptr)
				delete transition;
			transition = new TransitionScene(this, 3, true, true);
			GameManager::get()->pushScene(transition, true);
		}
		break;
	case BadEnding1Scene::NONE:
		break;
	}
}
