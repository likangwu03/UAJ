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
	inline bool isAlive() { return alive; }

	inline void update();
	inline void render();
	inline void handleEvents();

	template<typename Comp>
	void addComponent(Comp* comp) {
		auto it = components.find(Comp::id);
		if(it != components.end()) {
			delete it->second;
		}
		components[Comp::id] = comp;
	}
	
	template<typename Comp>
	Comp* getComponent() {
		auto it = components.find(Comp::id);
		if(it == components.end()) {
			return nullptr;
		}
		return it->second;
	}
};