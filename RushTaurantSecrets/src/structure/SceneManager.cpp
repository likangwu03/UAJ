#include "SceneManager.h"

void SceneManager::update() {
	for (auto s : currentScenes) {
		s->update();
	}
}
void SceneManager::render() {
	for (auto s : currentScenes) {
		s->render();
	}
}
void SceneManager::handleEvents() {
	for (auto s : currentScenes) {
		s->handleEvents();
	}
}
void SceneManager::refresh() {
	for (auto s : currentScenes) {
		s->refresh();
	}
}
void SceneManager::ChangeScene() {

}