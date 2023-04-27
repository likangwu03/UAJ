#include "IntroDay3ScareScene.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

void IntroDay3ScareScene::addPath(const vector<Vector>& points)
{
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

IntroDay3ScareScene::IntroDay3ScareScene()
{
	dialogues = GameManager::get()->getDialogueInfo("ConversationDay3Scare.json");

	state = START;
	creepyMusic = &sdlutils().musics().at("ATMOSPHERE_CREEPY_MUSIC");
	rainAmbience = &sdlutils().soundEffects().at("RAIN_AMBIENCE");
	rainAmbience->setVolume(50);
	bg = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_RAINY");
	top = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_TOP");
	filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	filter->setOpacity(80);
	black = &sdlutils().images().at("Filter_Black");

	player = new GameObject(this, _ecs::grp_PLAYER);
	transform = new Transform(player, RelativeToGlobal::pointRestaurant(Vector(50, 14)), Vector(0, 0), WIDTH, HEIGHT);
	straightMovement = new StraightMovement(player, 5);

	Animator::AnimParams ap;
	ap.initFrame = 18;
	ap.endFrame = 10;
	ap.currAnim = 1;
	ap.width = 48 * 1.8;
	ap.height = 96 * 1.8;
	ap.frameRate = 10;
	auto anim = new CharacterAnimator(player, "Player_Casual", ap);
	(&sdlutils().images().at("Filter_White"))->setOpacity(60);

	addPath(playerPaths[START]);
}

void IntroDay3ScareScene::reset()
{
	state = START;
	cont = 0;
	transition = new ShowSkipTransitionScene(this, 3);
	GameManager::get()->pushScene(transition, true);
}

void IntroDay3ScareScene::renderCinematic()
{
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void IntroDay3ScareScene::finishScene()
{
	black->setOpacity(100);
	black->render(build_sdlrect(0, 0, sdlutils().width(), sdlutils().height()));
	if (transition != nullptr)
		delete transition;
	creepyMusic->haltMusic();
	rainAmbience->haltChannel();
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);
}

void IntroDay3ScareScene::update()
{
	CinematicBaseScene::update();
	cont += frameTime;
	if (cont >= THUNDER_TIMER * 1000) {
		(&sdlutils().soundEffects().at("THUNDER"))->play();
		THUNDER_TIMER = sdlutils().rand().nextInt(20, 30);
		cont = 0;
	}
	switch (state)
	{
	case IntroDay3ScareScene::START:
		rainAmbience->play(-1);
		creepyMusic->play(-1);
		state = ENTERING;
		break;
	case IntroDay3ScareScene::ENTERING:
		if (straightMovement->hasFinishedPath()) {
			addPath(playerPaths[ENTERING]);
			state = ARRIVE;
			(&sdlutils().soundEffects().at("OPEN_DOOR"))->play();
		}
		break;
	case IntroDay3ScareScene::ARRIVE:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[0].portrait, dialogues[0].text);
			state = D1;
		}
		break;
	case IntroDay3ScareScene::D1:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[1].portrait, dialogues[1].text);
			state = D2;
		}
		break;
	case IntroDay3ScareScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[2].portrait, dialogues[2].text);
			state = D3;
		}
		break;
	case IntroDay3ScareScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 430), 700, 0.01 * 1000,
				font, dialogues[3].portrait, dialogues[3].text);
			state = D4;
		}
		break;
	case IntroDay3ScareScene::D4:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 440), 700, 0.01 * 1000,
				font, dialogues[4].portrait, dialogues[4].text);
			state = D5;
		}
		break;
	case IntroDay3ScareScene::D5:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[5].portrait, dialogues[5].text);
			state = D6;
		}
		break;
	case IntroDay3ScareScene::D6:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, Vector(150, 500), 700, 0.01 * 1000,
				font, dialogues[6].portrait, dialogues[6].text);
			state = OUT;
		}
		break;
	case IntroDay3ScareScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 1, true, true);
			GameManager::get()->pushScene(transition, true);
			state = NONE;
		}
		break;
	case IntroDay3ScareScene::NONE:
		break;
	default:
		break;
	}

}
