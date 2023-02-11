#include "SceneManager.h"
SceneManager::SceneManager() {
	act = MAINMENU;
	change = act;
	setScene();
}
void SceneManager::update() {
	currentScene->update();
}
void SceneManager::render() {
	currentScene->render();
}
void SceneManager::handleEvents() {
	currentScene->render();
}
void SceneManager::refresh() {
	currentScene->refresh();
}

void SceneManager::clear() {
	currentScene = nullptr;
	for (auto scene : Scenes) {
		delete scene;
	}
	Scenes.clear();
}

void SceneManager::setScene() {
	switch (change)
	{
	case SceneManager::MAINMENU:
		clear();
		currentScene = new MainMenu();
		Scenes.push_back(currentScene);
		break;
	case SceneManager::RESTAURANT:

		break;
	case SceneManager::PANTRY:
		break;
	case SceneManager::SUPERMARKET:
		break;
	default:
		break;
	}
}