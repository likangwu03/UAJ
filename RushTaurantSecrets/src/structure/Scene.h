#pragma once
#include <vector>
#include <array>
#include "Structure_def.h"

class GameObject;

class Scene {
protected:
	std::vector<GameObject*> objects;
	std::array<std::vector<GameObject*>, _ecs::grpNum> objGroups;
public:
	Scene();
	virtual ~Scene();

	void addObject(GameObject* object, _ecs::id_type grp);
	void refresh();
	inline const std::vector<GameObject*>& getGroup(_ecs::id_type grp) { return objGroups[grp]; }

	inline void update();
	inline void render();
	inline void handleEvents();
};