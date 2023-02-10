#include "GameObject.h"
#include "Scene.h"
#include "Component.h"

GameObject::GameObject(Scene* scene, _ecs::id_type grp) : scene(scene), alive(true) {
	scene->addObject(this, grp);
	components.reserve(_ecs::cmpNum);
}

GameObject::~GameObject() {
	for(auto& i : components) {
		delete i.second;
	}
}

/*void GameObject::changeScene(Scene* scene) {
	//this->scene->removeObject(this);
	//scene->addObject(this);
	this->scene = scene;
}//*/

void GameObject::refresh() {
	auto it = components.begin();
	while(it != components.end()) {
		if(!it->second->isAlive()) {
			delete it->second;
			it = components.erase(it);
		} else ++it;
	}
}

void GameObject::update() {
	for(auto& i : components) i.second->update();
}

void GameObject::render() {
	for(auto& i : components) i.second->render();
}

void GameObject::handleEvents() {
	for(auto& i : components) i.second->handleEvents();
}