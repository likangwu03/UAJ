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

void Scene::addObject(GameObject* object, _ecs::_grp_id grp, _ecs::_hdr_id handler) {
	objGroups[grp].push_back(object);
	if(handler != _ecs::hdr_INVALID) handlers[handler] = object;
}

void Scene::refresh() {
	// sacar el objeto de los handlers
	for (int i = 0; i < _ecs::hdrNum; ++i) {
		if (handlers[i] != nullptr && !handlers[i]->isAlive()) {
			handlers[i] = nullptr;
		}
	}

	// sacar el objeto de los grupos y eliminarlo
	for (int n = 0; n < _ecs::grpNum; n++) {
		objGroups[n].erase(
			std::remove_if(objGroups[n].begin(), objGroups[n].end(), [](GameObject* obj) {
				if (obj->isAlive()) {
					return false;
				}
				else {
					obj = nullptr;
					delete obj;
					return true;
				}
				}), //
			objGroups[n].end());
	}
}

void Scene::update() {

	// cleon: for (auto objGroup : objGroups) { (también en los otros)
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