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
		//if (typeid(scene) == typeid(Restaurant)) delete static_cast<Restaurant*>(scene)->getPantry();
		//if (typeid(scene) == typeid(Pantry)) delete static_cast<Pantry*>(scene)->getRestaurant();
		delete scene;
	}
	Scenes.clear();
}


// cleon: no pongáis esto con un switch, sino con polimorfismo dentro de cada escena. 'SceneManager' no puede saber qué escenas hay.
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
		sdlutils().setResizeFactor(GENERALSIZE);
		if (act == MAINMENU) {
			//creacion de restaurant y pantry
			UIRestaurant* uiRest = new UIRestaurant();
			Restaurant* rest = new Restaurant(uiRest);
			sdlutils().setResizeFactor(PANTRYSIZE);
			Pantry* pantry = new Pantry();
			rest->linkPantry(pantry);
			pantry->linkRestaurant(rest);
			Scenes.push_back(rest);
			sdlutils().setResizeFactor(GENERALSIZE);
		}
		else if (act == PANTRY) {
			Scenes.pop_back();
		}
		else if (act == SUPERMARKET) {
			/*sdlutils().setResizeFactor(GENERALSIZE);
			currentScene = new SuperMarket();
			Scenes.push_back(currentScene);*/

		}
		else if (act == PAUSEMENU) {
			Scene* aux = Scenes.back();
			Scenes.pop_back();
			delete aux;
		}
		}break;
	case SceneManager::PANTRY: {
		sdlutils().setResizeFactor(PANTRYSIZE);
		if (act == RESTAURANT) {			
			Scene* aux = Scenes.back();
			Scenes.pop_back();
			Scenes.push_back(static_cast<Restaurant*>(aux)->getPantry());
		}
		}break;
	case SceneManager::DAILYMENU: {
		if (act == MAINMENU) {
			DailyMenuScene* dailyMenuS = new DailyMenuScene(this);
			currentScene = dailyMenuS;
			Scenes.push_back(currentScene);
		}
		break;
	}
	case SceneManager::SUPERMARKET:
		sdlutils().setResizeFactor(GENERALSIZE); // cleon =D
		if (act == MAINMENU || act == DAILYMENU) {
			UIMarket* uiMarket = new UIMarket();
			SuperMarket* superMarket = new SuperMarket(uiMarket);
			currentScene = superMarket;
			Scenes.push_back(currentScene);
		}
		break;
	case SceneManager::PAUSEMENU:
		if (act == RESTAURANT || act == PANTRY) {
			PauseMenu* pauseMenu = new PauseMenu(this);
			currentScene = pauseMenu;
			Scenes.push_back(currentScene);
		}		
		break;
	default:
		break;
	}
}