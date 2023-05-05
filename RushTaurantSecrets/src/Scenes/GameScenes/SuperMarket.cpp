#include "SuperMarket.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/OtherPlayer.h"
#include "../../GameObjects/ClientMarket.h"
#include "../../Utilities/checkML.h"
#include "../../Components/Route1.h"
#include "../../Components/Route2.h"
#include "../../Components/Route3.h"
#include "../../Components/Route4.h"
#include "../../GameObjects/ClientCart.h"
#include "../../Managers/DayManager.h"

 void SuperMarket::initComponent() {
	 Scene::initComponent();
	 uiMarket->initComponent();
}

void SuperMarket::render() {
	Scene::renderLayer();
	if (uiMarket != nullptr)
		uiMarket->render();
}

void SuperMarket::update() {
	Scene::update();
	cm->update();
	uiMarket->update();
}

void SuperMarket::handleEvents() {
	Scene::handleEvents();
	uiMarket->handleEvents();
	
	if (ih->isKeyDown(SDLK_ESCAPE) && active || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_START))) {
		GameManager::get()->pushScene((GameManager::get()->getScene(sc_PAUSEMENU)));
		restaurantMusic->pauseMusic();
	}
}

void SuperMarket::init() {
	cm = new CollisionsManager(this);
	player = new Player(this, 0);
	new OtherPlayer(this, 2);

	ClientCart* clientCart = new ClientCart(this, "Client_10", 2.5);
	new Route1(clientCart, 10000, { Vector(10, 5), Vector(10, 9), Vector(19, 9) });

	if (GameManager::get()->getDayManager()->getDay() == 3) {
		for (int i = 0; i < 3; ++i) {
			string sprite = "Client_" + to_string(8 + i);
			ClientMarket* dancingClient = new ClientMarket(this, sprite, _ecs::Top, 4.5);
			new Route2(dancingClient, Vector(19 + 0.8 * i, 20), 8);
		}
	}

	new ClientMarket(this, "Staff_1", _ecs::Down, 0, Vector(31, 3));

	ClientMarket* fishStaff = new ClientMarket(this, "Staff_2", _ecs::Down, 2);
	new Route3(fishStaff, Vector(5, 9), Vector(5, 13), 7000);

	ClientCart* clientCart2 = new ClientCart(this, "Client_5", 2.5);
	new Route4(clientCart2, 12000);
}

void SuperMarket::callAfterCreating() {
	cartelM = new CartelManager(this);
	createMap();
	initRender();
	initComponent();
}

void SuperMarket::createMap() {
	Scene::createMap("assets/tilemaps/supermarket.tmx", Down, Vector());
	Scene::createMap("assets/tilemaps/supermarket_top_walls.tmx", Top, Vector());
	Scene::createMap("assets/tilemaps/supermarket_top_bottom.tmx", Middle, Vector(0, 16*48 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/supermarket_top_middle.tmx", Middle, Vector(0, 11*48 * RESIZEFACTOR));
}

SuperMarket::~SuperMarket() {
	delete uiMarket;
	delete cm;
	delete cartelM;
}

void SuperMarket::reset() {
	Transform* playerTransform = player->getComponent<Transform>();
	playerTransform->setPos(INITIAL_POS);
	playerTransform->setOrientation(west);
	player->getComponent<PlayerMovementController>()->initP();
}

BasketMarket* SuperMarket::getBM() {
	return uiMarket->basketM();
}

ButtonGO* SuperMarket::buyButton() {
	return uiMarket->BuyButton();
}

void SuperMarket::setBuy(bool _buy) {
	uiMarket->setBuy(_buy);
}

bool SuperMarket::getBuy() {
	return uiMarket->getBuy();
}

void SuperMarket::resumeMusic() {
	supermarketMusic->resumeMusic();
}

void SuperMarket::receive(const Message& message) {
	Scene::receive(message);
	uiMarket->receive(message);
}


void SuperMarket::initCoopMode(bool server) {
	active = false;
	if (!server) {
		getGameObject(_ecs::hdr_PLAYER)->getComponent<CharacterAnimator>()->setTexture("Player_2",18,18);
		getGameObject(_ecs::hdr_OTHERPLAYER)->getComponent<CharacterAnimator>()->setTexture("Player_1", 18, 18);
	}
}

void SuperMarket::quitCoopMode() {
	active = true;
	getGameObject(_ecs::hdr_PLAYER)->getComponent<CharacterAnimator>()->setTexture("Player_1", 18, 18);
	getGameObject(_ecs::hdr_OTHERPLAYER)->getComponent<CharacterAnimator>()->setTexture("Player_2", 18, 18);
}