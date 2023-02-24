#include "SceneManager.h"
SceneManager::SceneManager() {
	act = MAINMENU;
	change = act;
	/*setScene();*/
	//clear();
	currentScene = new MainMenu(this);
	Scenes.push_back(currentScene);
	//currentScene = Scenes.back();
}

void SceneManager::update() {
	if (change != act) {
		setScene();
		currentScene = Scenes.back();
		act = change;
		//cout << act << endl;
	}
	currentScene->update();
}

void SceneManager::render() {
	currentScene->render();
}

void SceneManager::handleEvents() {
	currentScene->handleEvents();
}

void SceneManager::refresh() {
	currentScene->refresh();
}

void SceneManager::ChangeScene(SceneName scene) {
	change = scene;
}

void SceneManager::clear() {
	currentScene = nullptr;
	for (auto scene : Scenes) {
		delete scene;
	}
	Scenes.clear();
}
void SceneManager::setScene() {
	Scene* aux;
	switch(change) {
	case SceneManager::MAINMENU:
		/*aux = *Scenes.begin();
		Scenes.clear();
		Scenes.push_back(aux);*/
		clear();
		Scenes.push_back(new MainMenu(this));
		break;
	case SceneManager::RESTAURANT: {
		if (act == MAINMENU) {
			sdlutils().setResizeFactor(0.6666666667);
			//creacion de restaurant y pantry
			UIRestaurant* uiRest = new UIRestaurant();
			Restaurant* rest = new Restaurant(uiRest);
			Pantry* pantry = new Pantry();
			rest->linkPantry(pantry);
			pantry->linkRestaurant(rest);
			Scenes.push_back(rest);
		}
		else if (act == PANTRY) {
			sdlutils().setResizeFactor(1);
			Scene* aux = Scenes.back();
			Scenes.pop_back();
			Scenes.push_back(static_cast<Pantry*>(aux)->getRestaurant());
		}
		else if (act == SUPERMARKET) {
			/*sdlutils().setResizeFactor(0.6666666667);
			currentScene = new SuperMarket();
			Scenes.push_back(currentScene);*/

		}
		}break;
	case SceneManager::PANTRY: {
		if (act == RESTAURANT) {
			Scene* aux = Scenes.back();
			Scenes.pop_back();
			Scenes.push_back(static_cast<Restaurant*>(aux)->getPantry());
		}
		}break;
	case SceneManager::DAILYMENU: {
		if (act == MAINMENU) {
			DailyMenu* dailyMenu = new DailyMenu(this);
			currentScene = dailyMenu;
			Scenes.push_back(currentScene);
		}
		break;
	}
	case SceneManager::SUPERMARKET:
		sdlutils().setResizeFactor(0.6666666667);
		if (act == MAINMENU) {
			UIMarket* uiMarket = new UIMarket();
			SuperMarket* superMarket = new SuperMarket(uiMarket);
			currentScene = superMarket;
			Scenes.push_back(currentScene);
		}
		break;
	default:
		break;
	}
}