#include "Scene.h"
#include "GameObject.h"

Scene::Scene() {
	objects.reserve(50);
}

Scene::~Scene() {
	for(auto obj : objects) delete obj;
}

void Scene::addObject(GameObject* object, _ecs::id_type grp) {
	objects.push_back(object);
	objGroups[grp].push_back(object);
}

// falta por añadir que se elimine del grupo (array de vectores)
void Scene::refresh() {
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), [](GameObject* obj) {
			if (obj->isAlive()) {
				return false;
			}
			else {
				delete obj;
				return true;
			}
			}), //
		objects.end());
}

void Scene::update() {
	for(auto& i : objects) i->update();
}

void Scene::render() {
	for(auto& i : objects) i->render();
}

void Scene::handleEvents() {
	for(auto& i : objects) i->handleEvents();
}