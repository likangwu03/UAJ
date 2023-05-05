#include "BeforeDayStartScene.h"
#include "../../Structure/GameManager.h"
#include "DailyMenuScene.h"
#include "../../Managers//DayManager.h"
#include "../../Utilities/checkML.h"
#include "../../Utilities/CoopHandler.h"
#include "../../Structure/Game.h"
#include "../../Managers/Money.h"


BeforeDayStartScene::BeforeDayStartScene() {

	beginSound = &sdlutils().soundEffects().at("DAILY_OBJECTIVE");

	gm = GameManager::instance();
	ih = InputHandler::instance();

	//string con texto correspondiente
	wordDay = "DAY " + std::to_string(accDay);
	press = "PRESS ANY BUTTON TO CONTINUE";
	mnyTarget = "TODAY'S GOAL IS TO ACHIEVE: " + std::to_string(accGoal) + " DOLLARS";

	//background
	obj = new GameObject(this);
	new Transform(obj, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	background = &(sdlutils().images().at("MORNING_BG"));
	new Image(obj, background);

	//fuentes usadas
	dayText = new Font("assets/Fonts/04B_30__.ttf", 72);
	pressButtonText = new Font("assets/Fonts/light_pixel-7.ttf", 40);
	text = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	pressButtonText1 = new Font("assets/Fonts/light_pixel-7.ttf", 40);
	text1 = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	TTF_SetFontOutline(pressButtonText1->getTTFFont(), 2);
	TTF_SetFontOutline(text1->getTTFFont(), 2);


	//diana
	targetObj = new GameObject(this);
	new Transform(targetObj, { 75, 400 }, { 0,0 }, 100, 100);
	target = &(sdlutils().images().at("TARGET_ICON"));
	new Image(targetObj, target);

	//banner
	bannerObj = new GameObject(this);
	new Transform(bannerObj, { (float)sdlutils().width() / 4 + 50, 10 }, { 0,0 }, 500, 300);
	bannerTexture = &(sdlutils().images().at("BANNER"));
	new Image(bannerObj, bannerTexture);

}

void BeforeDayStartScene::init() {

	//Textura asociada a las fuentes y strings (ordenados en funcion de lugar de aparicion en escena)
	dayTxt = new Texture(sdlutils().renderer(), wordDay, *dayText, build_sdlcolor(0x000000FF));
	moneyTarget = new Texture(sdlutils().renderer(), mnyTarget, *text, build_sdlcolor(0x000000FF));
	buttonTxt = new Texture(sdlutils().renderer(), press, *pressButtonText, build_sdlcolor(0x000000FF));

	day = gm->getDayManager();
	initMoney = gm->getMoney()->getMoney(); //Dinero inicial del día
}


void BeforeDayStartScene::reset() {
	//beginSound->play();
	accDay = day->getDay();
	accGoal = day->getDailyObjective();
	wordDay = "DAY " + std::to_string(accDay);
	mnyTarget = "TODAY'S GOAL IS TO ACHIEVE: " + std::to_string(accGoal) + " DOLLARS";
	delete dayTxt;
	delete moneyTarget;
	//delete buttonTxt;  //???
	dayTxt = new Texture(sdlutils().renderer(), wordDay, *dayText, build_sdlcolor(0x000000FF));
	moneyTarget = new Texture(sdlutils().renderer(), mnyTarget, *text, build_sdlcolor(0x000000FF));
	initMoney = gm->getMoney()->getMoney(); //Dinero inicial del día

}

void BeforeDayStartScene::toDailyMenu() {
	gm->changeScene(gm->getScene(_ecs::sc_DAILYMENU));
}

BeforeDayStartScene::~BeforeDayStartScene() {
	delete dayTxt;
	delete moneyTarget;
	delete buttonTxt;
	delete text;
	delete text1;
	delete pressButtonText;
	delete pressButtonText1;
	delete dayText;
}

void BeforeDayStartScene::handleEvents() {
	if (!active)return;
	if ((ih->joysticksInitialised() && ih->joyButtonDown()) || ih->keyDownEvent()) {
		toDailyMenu();
		Message m{};
		m.id = Message::msg_TO_DAILY_MENU;
		gm->getDailyMenu()->getMenus(m.daily_menus.menu1, m.daily_menus.menu2);
		Game::get()->getCoopHandler()->send(m);
	}
}

void BeforeDayStartScene::render() {
	Scene::render();

	dayTxt->render({ sdlutils().width() / 3 + 50, 85, 300, 150 });
	moneyTarget->render({ 200, 400, sdlutils().width() - 300, 100 });
	buttonTxt->render({ sdlutils().width() / 4 - 50, 600, buttonTxt->width(), buttonTxt->height() });

}

void BeforeDayStartScene::initCoopMode(bool server) {
	active = server;
}

void BeforeDayStartScene::quitCoopMode() {
	active = true;
}

void BeforeDayStartScene::receive(const Message& message) {
	if (message.id == Message::msg_TO_DAILY_MENU) {
		gm->getDailyMenu()->setMenus(message.daily_menus.menu1, message.daily_menus.menu2);
		toDailyMenu();
	}
}

int BeforeDayStartScene::getInitMoney() { return initMoney; }