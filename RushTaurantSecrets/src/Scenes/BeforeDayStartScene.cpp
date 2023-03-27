#include "BeforeDayStartScene.h"
#include "../Structure/GameManager.h"
#include "../Scenes/DailyMenuScene.h"
#include "../Managers//DayManager.h"


#include "../Utilities/checkML.h"

BeforeDayStartScene::BeforeDayStartScene() {

	gm= GameManager::instance();
	ih= InputHandler::instance();

	day = gm->getDayManager();

	//string con texto correspondiente
	wordDay = "DAY: " + std::to_string(day->getDay());
	press = "PRESS ANY BUTTON TO CONTINUE...";
	mnyTarget = "TODAY'S GOAL IS TO ACHIEVE: " + std::to_string(day->getDailyObjective()) + " DOLLARS";

	//background
	obj = new GameObject(this);
	new Transform(obj, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	background = new Texture(sdlutils().renderer(), "assets/options_bg.png");
	new Image(obj, background);

	//fuentes usadas
	dayText = new Font("assets/Fonts/04B_30__.ttf", 72);
	pressButtonText = new Font("assets/Fonts/EpilepsySansBold.ttf", 30);
	text = new Font("assets/Fonts/EpilepsySansBold.ttf", 50);

	//Textura asociada a las fuentes y strings (ordenados en funcion de lugar de aparicion en escena)
	dayTxt = new Texture(sdlutils().renderer(), wordDay, *dayText, build_sdlcolor(0x000000FF));
	moneyTarget = new Texture(sdlutils().renderer(), mnyTarget, *text, build_sdlcolor(0x000000FF));
	buttonTxt = new Texture(sdlutils().renderer(), press, *pressButtonText, build_sdlcolor(0x000000FF));
	

	//diana
	targetObj = new GameObject(this);
	new Transform(targetObj, { 75, 300 }, {0,0}, 100, 100);
	target = new Texture(sdlutils().renderer(), "assets/Sprites/UI/HUD/target_icon.png");
	new Image(targetObj, target);

	bannerObj = new GameObject(this);
	new Transform(bannerObj, { (float)sdlutils().width() /4 +50, 25 }, {0,0}, 500, 300);
	bannerTexture = new Texture(sdlutils().renderer(), "assets/Sprites/UI/UI_Flat_Banner_01_Upward.png");
	new Image(bannerObj, bannerTexture);
}



void BeforeDayStartScene::update() {
	wordDay = "DAY: " + std::to_string(day->getDay());
	mnyTarget = "TODAY'S CHALLENGE IS TO ACHIEVE: " + std::to_string(day->getDailyObjective()) + " DOLLARS";
	dayTxt = new Texture(sdlutils().renderer(), wordDay, *dayText, build_sdlcolor(0x000000FF));
	moneyTarget = new Texture(sdlutils().renderer(), mnyTarget, *text, build_sdlcolor(0x000000FF));
	buttonTxt = new Texture(sdlutils().renderer(), press, *pressButtonText, build_sdlcolor(0x000000FF));

}

void BeforeDayStartScene::toDailyMenu() {
	gm->changeScene(GameManager::get()->getDailyMenu());
}

BeforeDayStartScene::~BeforeDayStartScene() {
	delete target;
	delete buttonTxt;
	delete moneyTarget;
	delete dayTxt;
	delete text;
	delete pressButtonText;
	delete dayText;
	delete background;

}

void BeforeDayStartScene::handleEvents() {
	if((ih->joysticksInitialised() && ih->getButtonState(0, SDL_JOYBUTTONDOWN)) || ih->keyDownEvent()) {
		toDailyMenu();
	}
}

void BeforeDayStartScene::render() {
	Scene::render();
	//hacer render de todos los images llamando a sus render
	//background->render({ 0,0, sdlutils().width(), sdlutils().height()});
	dayTxt->render({ sdlutils().width()/3 + 50, 100, 300, 150});
	//target->render({ 100, 100, 50, 100 });
	moneyTarget->render({ 200, 300, sdlutils().width() - 300, 100});
	buttonTxt->render({ 100, 500, 1000, 200 });
	
}