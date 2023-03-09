#include "SceneManager.h"

void SceneManager::init() {
	currentScene = new MainMenu();
	pushScene(currentScene);
	nSceceToPop = 0;
}

SceneManager::SceneManager() {
	setResize();
}

void SceneManager::update() {
	if (currentScene != Scenes.back()) {
		setScene();
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
void SceneManager::pushScene(Scene* scene) {
	Scenes.push_back(scene);
}

void SceneManager::popScene(int n) {
	for (int i = 0; i < n; ++i) {
		delete Scenes.back();
		Scenes.pop_back();
	}
}
void SceneManager::changeScene(Scene* _scene, int nPop) {
	nSceceToPop = nPop;
	currentScene = _scene;
}

void SceneManager::clear() {
	currentScene = nullptr;
	for (auto scene : Scenes) {
		delete scene;
	}
	Scenes.clear();
}

void SceneManager::setResize(bool type) {
	if (type) {
		sdlutils().setResizeFactor(GENERALSIZE);
	}
	else {
		sdlutils().setResizeFactor(PANTRYSIZE);
	}
}

// cleon: no pongáis esto con un switch, sino con polimorfismo dentro de cada escena. 'SceneManager' no puede saber qu?escenas hay.
void SceneManager::setScene() {
	if (nSceceToPop != -1) {
		popScene(nSceceToPop);
	}
	else {  //caso de que no queremos destruir la escena
		Scenes.pop_back();
	}
	if (currentScene != nullptr) Scenes.push_back(currentScene);
	else currentScene = Scenes.back();
}