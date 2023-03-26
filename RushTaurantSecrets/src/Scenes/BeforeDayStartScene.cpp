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
	mnyTarget = "TODAY'S CHALLENGE IS TO ACHIEVE: " + std::to_string(day->getDailyObjective()) + " DOLLARS";

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
	new Transform(targetObj, { 100, 100 }, {0,0}, 58, 58);
	target = new Texture(sdlutils().renderer(), "assets/Sprites/UI/HUD/target_icon.png");
	new Image(targetObj, target);
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
	if((ih->joysticksInitialised() && ih->getButtonState(0, SDL_JOYBUTTONDOWN)) || ih->isKeyDown(SDL_KEYDOWN) || ih->isKeyDown(SDL_MOUSEBUTTONDOWN)) {
		toDailyMenu();
	}
}

void BeforeDayStartScene::render() {
	Scene::render();
	//hacer render de todos los images llamando a sus render
	background->render({ 0,0 }, { sdlutils().width(), sdlutils().height()});
	dayTxt->render({ 150, 100 }, { 58, 58 });
	target->render({ 100, 100 }, { 58, 58 });
	moneyTarget->render({ 150, 100 }, { 58, 58 });
	
}