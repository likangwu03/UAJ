#include "GameObject.h"
#include "Scene.h"
#include "Component.h"

GameObject::GameObject(Scene* scene, _ecs::id_type grp) : scene(scene), alive(true) {
	scene->addObject(this, grp);
	components.reserve(_ecs::cmpNum);
}

GameObject::~GameObject() {
	for(auto& i : components) {
		delete i.first;
	}
}

/*void GameObject::changeScene(Scene* scene) {
	//this->scene->removeObject(this);
	//scene->addObject(this);
	this->scene = scene;
}//*/

void GameObject::refresh() {
	components.erase(
		std::remove_if(components.begin(), components.end(), [](std::pair<Component*, _ecs::id_type> comp) {
			if(comp.first->isAlive()) {
				return false;
			} else {
				delete comp.first;
				return true;
			}
			}),
		components.end());
}

void GameObject::update() {
	for(auto& i : components) i.first->update();
}

void GameObject::render() {
	for(auto& i : components) i.first->render();
}