#pragma once
#include <unordered_map>
#include "Structure_def.h"

class Component;
class Scene;

class GameObject {
protected:
	std::unordered_map<_ecs::id_type, Component*> components;
	Scene* scene;
	bool alive;
public:
	GameObject(Scene* scene, _ecs::id_type grp = _ecs::grp_GENERAL);
	virtual ~GameObject();

	//void changeScene(Scene* scene);
	void refresh();
	bool isAlive() { return alive; }

	void setAlive(bool alive) {
		this->alive = alive;
	}

	void update();
	void render();
	void handleEvents();

	void addComponent(Component* comp, _ecs::id_type id) {
		auto it = components.find(id);
		if (it != components.end()) {
			delete it->second;
		}
		components[id] = comp;
	}

	template<typename Comp>
	Comp* getComponent() {
		auto it = components.find(Comp::id);
		if (it == components.end()) {
			return nullptr;
		}
		return static_cast<Comp*>(it->second);
	}
};