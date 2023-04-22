#include "BadEnding1.h"
#include "MainMenu.h"
#include "../Utilities/checkML.h"
#include "BeforeDayStartScene.h"
#include "DailyMenuScene.h"

#include "ShowSkipTransitionScene.h"
#include "../Structure/GameManager.h"
#include "../GameObjects/Dialogue.h"

void BadEnding1::addPath(const vector<Vector>& points)
{
	straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
}

BadEnding1::BadEnding1()
{
	dialogues = GameManager::get()->getDialogueInfo("BadEnding1.json");

	state = START;
	nightMusic = &sdlutils().musics().at("GOOD_DAY_MUSIC");
	nightAmbience = &sdlutils().soundEffects().at("NIGHT_AMBIENCE");
	nightAmbience->setVolume(60);

	bg = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT");
	top = &sdlutils().images().at("CINEMATIC_BG_RESTAURANT_TOP");
	//filter = &sdlutils().images().at("CINEMATIC_BG_PARENTS_ROOM_NIGHT");
	//filter->setOpacity(80);

	player = new Player(this, 0);
	player->getComponent<PlayerMovementController>()->setActive(false);
	straightMovement = new StraightMovement(player, 5);

	//Scene* scene, string sprite, Vector origin, float speed
	client1 = new CinematicNPC(this, "Client_3", RelativeToGlobal::pointRestaurant({ 27, 15 }), 2);
	client2 = new CinematicNPC(this, "Client_5", RelativeToGlobal::pointRestaurant({ 25, 16 }), 2);

	transform = player->getComponent<Transform>();
	transform->setPos(Vector(1658, 772));
	transform->setMovState(walking);

	//auto anim = player->getComponent<CharacterAnimator>();
	//anim->setH(96 * 1.8);
	//anim->setW(48 * 1.8);
	//anim->setTexture("Player_Casual", 18, 10, 1);
	//anim->setframeRate(18);
}

void BadEnding1::callAfterCreating()
{
	GameManager::get()->changeScene(new ShowSkipTransitionScene(this, 3));
}

void BadEnding1::renderCinematic()
{
	bg->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	player->render();
	client1->render();
	client2->render();
	top->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
	//filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void BadEnding1::finishScene()
{
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
	GameManager::get()->getBeforeDayStart()->reset();
	GameManager::get()->getDailyMenu()->reset();
}

void BadEnding1::update()
{
	CinematicBaseScene::update();
	switch (state)
	{
	case BadEnding1::START:
		nightAmbience->play(-1);
		nightMusic->play(-1);
		addPath(_ecs::introPath[START].points);
		state = ENTERING;
		break;
	case BadEnding1::ENTERING:
		break;
	case BadEnding1::ARRIVE:
		break;
	case BadEnding1::NONE:
		break;
	default:
		break;
	}
}
