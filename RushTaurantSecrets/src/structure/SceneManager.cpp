#include "SceneManager.h"
SceneManager::SceneManager() {
	act = MAINMENU;
	change = act;
	/*setScene();*/
	//clear();
	currentScene = new Restaurant();
	Scenes.push_back(currentScene);
	//currentScene = Scenes.back();
}

void SceneManager::update() {
	if (change != act) {
		setScene();
		currentScene = Scenes.back();
		act = change;
		cout << act << endl;
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
		Scenes.push_back(new MainMenu());
		break;
	case SceneManager::RESTAURANT: {
		if (act == MAINMENU) {
			//creacion de restaurant y pantry
			UIRestaurant* uiRest = new UIRestaurant();
			Restaurant* rest = new Restaurant(uiRest);
			Pantry* pantry = new Pantry();
			rest->linkPantry(pantry);
			pantry->linkRestaurant(rest);
			Scenes.push_back(rest);
		}
		else if (act == PANTRY) {
			Scene* aux = Scenes.back();
			Scenes.pop_back();
			Scenes.push_back(static_cast<Pantry*>(aux)->getRestaurant());
		}
		else if (act == SUPERMARKET) {

		}
		}break;
	case SceneManager::PANTRY: {
		if (act == RESTAURANT) {
			Scene* aux = Scenes.back();
			Scenes.pop_back();
			Scenes.push_back(static_cast<Restaurant*>(aux)->getPantry());
		}
		}break;
	case SceneManager::SUPERMARKET:
		break;
	default:
		break;
	}
}