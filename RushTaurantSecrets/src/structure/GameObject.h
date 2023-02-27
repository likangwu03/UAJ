#pragma once
#include <map>
#include "Structure_def.h"

class Component;
class Scene;

class GameObject {
private:
	friend class Component;
	void addComponent(Component* comp, _ecs::_cmp_id id);
protected:
	std::map<_ecs::_cmp_id, Component*> components;
	Scene* scene;
	bool alive;

public:
	GameObject(Scene* scene, _ecs::_grp_id grp = _ecs::grp_GENERAL, _ecs::_hdr_id handler = _ecs::hdr_INVALID);
	~GameObject();

	//void changeScene(Scene* scene);
	void refresh();
	bool isAlive() { return alive; }

	void setAlive(bool alive) { this->alive = alive; }

	virtual Scene* getScene() { return scene; }

	void update();
	void render();
	void handleEvents();

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