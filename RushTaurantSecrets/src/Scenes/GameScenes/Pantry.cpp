#include "Pantry.h"
#include "Restaurant.h"
#include "EndOfDayScene.h"
#include "../../Structure/GameManager.h"
#include "../../Components/MapCreator.h" 
#include "../../GameObjects/Player.h"
#include "../../Managers/ThievesManager.h"
#include "../../GameObjects/TimeOfDayObj.h"
#include "EndOfDayScene.h"
#include "../../GameObjects/OtherPlayer.h"
#include "../../Utilities/checkML.h"

Pantry::Pantry(UIPantry* pUI) : rest(nullptr), pantryUI(pUI), sdl(SDLUtils::instance()), restaurantMusic(&sdl->musics().at("RESTAURANT_MUSIC")), 
pantryMusic(&sdl->musics().at("PANTRY_MUSIC"))
{ 
	init();
	pantryMusic->setMusicVolume(MUSIC_VOL);
	restaurantMusic->setMusicVolume(MUSIC_VOL);
}

Pantry::~Pantry() {
	delete collisionsManager;
	delete pantryUI;
}


void Pantry::init() {
	collisionsManager = new CollisionsManager(this);

	player = new Player(this, 0);
	player->getComponent<PlayerMovementController>()->initP();
	new OtherPlayer(this, 1);
	new TimeOfDayObj(this, { 0,100 }, sdlutils().getLoadedTilesets().at("pantryAfternoon"), sdlutils().getLoadedTilesets().at("pantryNight"));
	// el update no se ejecuta hasta que se esté en la escena
	// por lo que no se crean ni se destruyen ladrones cuando no se está la despensa
	GameObject* managerContainer = new GameObject(this);
	ThievesManager::init(managerContainer, 2, 6, GameManager::get()->getHasKill(), 2, 20, 30);

	initRender();
}

void Pantry::createMap() {
	Scene::createMap("assets/tilemaps/pantry.tmx", Down, Vector());
	Scene::createMap("assets/tilemaps/pantry_top_walls.tmx", Top, Vector());
	Scene::createMap("assets/tilemaps/pantry_top_bottom.tmx", Middle, Vector(0, 14 * 48 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/pantry_top_middle.tmx", Middle, Vector(0, 11 * 48 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/pantry_top_bottom_2.tmx", Middle, Vector(0, 16 * 48 * RESIZEFACTOR));
}


void Pantry::callAfterCreating() {
	rest = GameManager::get()->getRestaurant();
	createMap();
	initRender();
}

void Pantry::render() {
	Scene::renderLayer();
	pantryUI->render();
}

void Pantry::update() {
	rest->_update();
	collisionsManager->update();
	_update();
}

void Pantry::_update() {
	Scene::update();
}

void Pantry::haltSound() {
	pantryMusic->haltMusic();
	ThievesManager::get()->haltSound();
}

void Pantry::handleEvents() {
	if (ih->isKeyDown(SDLK_ESCAPE) &&active) {
		GameManager::get()->pushScene((GameManager::get()->getScene(sc_PAUSEMENU)));
		pantryMusic->pauseMusic();
		ThievesManager::get()->pauseSound();
	}
}
void Pantry::resumeMusic() {
	pantryMusic->resumeMusic();
}
void Pantry::resumeSound() {
	ThievesManager::get()->resumeSound();
}
void Pantry::reset() {
	getGameObject(_ecs::hdr_PLAYER)->setActives(false);
	GameObject* otherPlayer = getGameObject(_ecs::hdr_OTHERPLAYER);
	otherPlayer->getComponent<OtherPlayerComp>()->sceneOut();
	otherPlayer->setActives(false);
	player->getComponent<PlayerMovementController>()->initP();
}

void Pantry::refresh() {
	Scene::refresh();
	rest->Scene::refresh();
}

void Pantry::receive(const Message& m) {
	rest->_receive(m);
	Scene::receive(m);
}

void Pantry::initCoopMode(bool server) {
	active = false;
	ThievesManager::get()->setActive(server);
	if (!server) {
		getGameObject(_ecs::hdr_PLAYER)->getComponent<CharacterAnimator>()->setTexture(&((*sdl).images().at("Player_2")), 18, 18);
		getGameObject(_ecs::hdr_OTHERPLAYER)->getComponent<CharacterAnimator>()->setTexture("Player_1", 18, 18);
	}
}

void Pantry::quitCoopMode() {
	active = true;
	ThievesManager::get()->setActive(true);
	getGameObject(_ecs::hdr_PLAYER)->getComponent<CharacterAnimator>()->setTexture("Player_1", 18, 18);
	getGameObject(_ecs::hdr_OTHERPLAYER)->getComponent<CharacterAnimator>()->setTexture("Player_2", 18, 18);
}