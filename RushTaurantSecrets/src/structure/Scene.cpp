#include "Scene.h"
#include "GameObject.h"

Scene::Scene() {
	ih = InputHandler::instance();
}

Scene::~Scene() {
	for (int n = 0; n < _ecs::grpNum; n++) {
		for (auto obj : objGroups[n]) delete obj;
	}
}

void Scene::addObject(GameObject* object, _ecs::id_type grp) {
	objGroups[grp].push_back(object);
}

// falta por añadir que se elimine del grupo (array de vectores)
void Scene::refresh() {
	for (int n = 0; n < _ecs::grpNum; n++) {
		objGroups[n].erase(
			std::remove_if(objGroups[n].begin(), objGroups[n].end(), [](GameObject* obj) {
				if (obj->isAlive()) {
					return false;
				}
				else {
					delete obj;
					return true;
				}
				}), //
			objGroups[n].end());
	}
}

void Scene::update() {
	for (int n = 0; n < _ecs::grpNum; n++) {
		for (auto obj : objGroups[n]) obj->update();
	}
}

void Scene::render() {
	for (int n = 0; n < _ecs::grpNum; n++) {
		for (auto obj : objGroups[n]) obj->render();
	}
}

void Scene::handleEvents() {
	for (int n = 0; n < _ecs::grpNum; n++) {
		for (auto obj : objGroups[n]) obj->handleEvents();
	}
}