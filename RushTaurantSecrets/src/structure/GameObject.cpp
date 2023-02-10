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
	// Borrar si !component->isAlive()
}

void GameObject::update() {
	for(auto& i : components) i.second->update();
}

void GameObject::render() {
	for(auto& i : components) i.second->render();
}