#pragma once
#include <unordered_map>
#include "Structure_def.h"

class Component;
class Scene;

enum GOOrientation {
	north, east, west, south
};

class GameObject {
protected:
	std::unordered_map<_ecs::_cmp_id, Component*> components;
	Scene* scene;
	bool alive;

	GOOrientation orientation;

public:
	GameObject(Scene* scene, _ecs::_grp_id grp = _ecs::grp_GENERAL, _ecs::_hdr_id handler = _ecs::hdr_INVALID);
	virtual ~GameObject();

	//void changeScene(Scene* scene);
	void refresh();
	bool isAlive() { return alive; }

	void setAlive(bool alive) {
		this->alive = alive;
	}

	GOOrientation getOrientation() {
		return orientation;
	}

	void setOrientation(GOOrientation o) {
		this->orientation = o;
	}

	virtual Scene* getScene() { return scene; }

	virtual void update();
	virtual void render();
	void handleEvents();

	void addComponent(Component* comp, _ecs::_cmp_id id) {
		auto it = components.find(id);
		if (it != components.end()) {
			delete it->second;
		}
		components[id] = comp;
	}

	template<typename Comp>
	inline Comp* getComponent() {
		auto it = components.find(Comp::id);
		if (it == components.end()) {
			return nullptr;
		}
		return static_cast<Comp*>(it->second);
	}

	template<typename Comp>
	inline void setActive(bool b) {
		auto it = components.find(Comp::id);
		if (it == components.end())return;
		it->second->setActive(b);
	}


};