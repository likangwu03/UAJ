#include "EndingDay2NoKillScene.h"
#include "../Menus/MainMenu.h"
#include "../../Utilities/checkML.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../GameScenes/DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Dialogue.h"

EndingDay2NoKillScene::EndingDay2NoKillScene() {
	dialogues = GameManager::get()->getDialogueInfo("EndingDay2NoKill.json");
	
	bg = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL");
	filter = &sdlutils().images().at("CINEMATIC_BG_ENTRANCE_GENERAL_NIGHT");
	filter->setOpacity(80);

	nightMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	nightAmbience->setVolume(60);

	player = new GameObject(this);
	transform = new Transform(player, Vector(0, 0), 0, 48, 96, 0);
	straightMovement = new StraightMovement(player, 7);

	auto anim = new CharacterAnimator(player, &sdlutils().images().at("Player_1"), AP);
	anim->setH(96 * 1.4);
	anim->setW(48 * 1.4);
	anim->setframeRate(10);
}

void EndingDay2NoKillScene::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

void EndingDay2NoKillScene::reset() {
	dialogueBox = nullptr;
	state = START;
	timer = 0;
	dialogueN = 0;
	transform->setPos(RelativeToGlobal::pointRestaurant(Vector(19.5, 20)));
	transform->setMovState(walking);
	transform->setOrientation(north);

	nightAmbience->play(-1);
	nightMusic->play(-1);

	if (GameManager::instance()->getCurrentScene() == this) {
		transition = new ShowSkipTransitionScene(this, 3);
		GameManager::get()->pushScene(transition, true);
	}
}

void EndingDay2NoKillScene::update() {
	CinematicBaseScene::update();
	switch (state) {
	case EndingDay2NoKillScene::START:
		addPath(paths[START]);
		state = TURN1;
		break;
	case EndingDay2NoKillScene::TURN1:
		if (straightMovement->hasFinishedPath()) {
			transform->setMovState(idle);
			if (timer >= TURNAROUNDTIME) {
				transform->setOrientation(west);
				state = TURN2;
				timer = 0;
			}
			else timer += frameTime;
		}
		break;
	case EndingDay2NoKillScene::TURN2:
		if (timer >= TURNAROUNDTIME) {
			transform->setOrientation(south);
			state = D1DELAY;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case EndingDay2NoKillScene::D1DELAY:
		if (timer >= TURNAROUNDTIME) {
			state = D1;
			timer = 0;
		}
		else timer += frameTime;
		break;
	case EndingDay2NoKillScene::D1:
		dialogueBox = new Dialogue(this, BOXPOS, 700, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
		dialogueN++;
		state = D2;
		break;
	case EndingDay2NoKillScene::D2:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, BOXPOS, 700, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
			dialogueN++;
			state = D3;
		}
		break;
	case EndingDay2NoKillScene::D3:
		if (Text::isTextFinished()) {
			dialogueBox = new Dialogue(this, BOXPOS, 700, LETTERFREQ, font, dialogues[dialogueN].portrait, dialogues[dialogueN].text);
			dialogueN++;
			state = OUT;
		}
		break;
	case EndingDay2NoKillScene::OUT:
		if (Text::isTextFinished()) {
			dialogueBox = nullptr;
			transition = new TransitionScene(this, 3, true, true);
 			GameManager::get()->pushScene(transition);
			state = NONE;
		}
		break;

	}
	
}

void EndingDay2NoKillScene::renderCinematic() {
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));

}


void EndingDay2NoKillScene::finishScene() {
	if(transition != nullptr)
		delete transition;
	nightMusic->haltMusic();
	nightAmbience->haltChannel();
//	GameManager::get()->changeScene(GameManager::get()->getScene(sc_INTRO3), false);
	GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART), false);

}