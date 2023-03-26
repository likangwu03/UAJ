#include "Scene.h"

#include "GameObject.h"
#include "Game.h"
#include "../Structure/GameManager.h"
#include "../Utilities/InputHandler.h"
#include "../Structure/GameObject.h"

#include "../Components/Transform.h"
#include "../Components/MapCreator.h"

#include "../Utilities/checkML.h"

Scene::Scene():frameTime(Game::instance()->getframeTime()) {
	ih = InputHandler::instance();
	handlers = {};
}

Scene::~Scene() {
	end();
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
					delete obj;
					// hacer que el hueco de memoria 
					// apunte a nullptr siempre va después de eliminar el objeto
					obj = nullptr;
					return true;
				}
				}), //
			objGroups[n].end());

		for(auto& obj : objGroups[n]) obj->refresh();
	}
}

void Scene::initComponent() {

	for (auto& objGroup : objGroups) {
		for (auto obj : objGroup) obj->initComponent();
	}
}

void Scene::update() {
	for (auto& objGroup : objGroups) {
		for (auto obj : objGroup) obj->update();
	}
}
void Scene::renderLayer() {

	for (auto obj : renderListDown) {
		obj->render();
	}

	list<GameObject*> aux;
	aux.insert(aux.end(), renderListMiddle.begin(), renderListMiddle.end());
	aux.insert(aux.end(), objGroups[_grp_id::grp_CLIENTS].begin(), objGroups[_grp_id::grp_CLIENTS].end());
	aux.insert(aux.end(), objGroups[_grp_id::grp_THIEFS].begin(), objGroups[_grp_id::grp_THIEFS].end());
	SortList(aux);
	for (auto& gameObject : aux) {
		gameObject->render();
	}

	for (auto obj : renderListTop) {
		obj->render();
	}
}

void Scene::render() {
	for (auto& objGroup : objGroups) {
		for (auto obj : objGroup) obj->render();
	}
}

void Scene::handleEvents() {
	for (auto& objGroup : objGroups) {
		for (auto obj : objGroup) obj->handleEvents();
	}
}

void Scene::nextDay() {
	for(auto& objGroup : objGroups)
		for(auto obj : objGroup) obj->nextDay();
}

void Scene::initRender(){
	renderListMiddle.insert(renderListMiddle.end(), objGroups[_grp_id::grp_GENERAL].begin(), objGroups[_grp_id::grp_GENERAL].end());
	renderListMiddle.insert(renderListMiddle.end(), objGroups[_grp_id::grp_PLAYER].begin(), objGroups[_grp_id::grp_PLAYER].end());
	renderListMiddle.insert(renderListMiddle.end(), objGroups[_grp_id::grp_RENDERTOP].begin(), objGroups[_grp_id::grp_RENDERTOP].end());
	//renderList.insert(renderList.end(), objGroups[_grp_id::grp_CLIENTS].begin(), objGroups[_grp_id::grp_CLIENTS].end());
	renderListMiddle.insert(renderListMiddle.end(), objGroups[_grp_id::grp_INTERACTABLE].begin(), objGroups[_grp_id::grp_INTERACTABLE].end());
	std::list<GameObject*>::iterator it = renderListMiddle.begin();
	std::list<GameObject*>::iterator aux;
	while (it!=renderListMiddle.end())
	{
		aux = it;
		it++;
		if ((*aux)->getComponent<Transform>() == nullptr) {
			renderListMiddle.erase(aux);
		}
	}
	
	SortList(renderListMiddle);
}

void Scene::SortList(std::list<GameObject*>& v) {
	v.sort([](GameObject* a, GameObject* b)
		{
			return a->getComponent<Transform>()->getPos().getY()+a->getComponent<Transform>()->getH() < b->getComponent<Transform>()->getPos().getY() + b->getComponent<Transform>()->getH();
		});
}

void Scene::pushRenderList(RenderPos pos, GameObject* obj) {
	switch (pos)
	{
	case _ecs::Top:
		renderListTop.push_back(obj);
		break;
	case _ecs::Middle:
		renderListMiddle.push_back(obj);
		break;
	case _ecs::Down:
		renderListDown.push_back(obj);
		break;
	default:
		break;
	}
}

void Scene::createMap(std::string file, RenderPos Rpos, Vector pos) {
	GameObject* aux = new GameObject(this, grp_RENDERTOP);
	new MapCreator(aux, file);
	new Transform(aux, pos);
	pushRenderList(Rpos, aux);
}
