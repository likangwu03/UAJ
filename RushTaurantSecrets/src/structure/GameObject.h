#pragma once
#include <vector>
#include "Structure_def.h"

class Component;
class Scene;

class GameObject {
protected:
	std::vector<std::pair<Component*, _ecs::id_type>> components;
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

	template<typename Comp>
	void addComponent(Comp* comp) {
		components.push_back(std::pair<Component*, _ecs::id_type>(comp, Comp::id));
	}
	
	template<typename Comp>
	Comp* getComponent() {
		for(auto& i : components) {
			if(i.second == Comp::id) return dynamic_cast<Comp*>(i.first);
		}
		return nullptr;
	}

	
};