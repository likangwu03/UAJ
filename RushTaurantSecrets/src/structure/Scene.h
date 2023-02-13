#pragma once
#include <vector>
#include <array>
#include "Structure_def.h"

class GameObject;

class Scene {
protected:
	std::array<std::vector<GameObject*>, _ecs::grpNum> objGroups;
	Scene();
public:
	virtual ~Scene();

	void addObject(GameObject* object, _ecs::id_type grp);
	void refresh();
	inline const std::vector<GameObject*>& getGroup(_ecs::id_type grp) { return objGroups[grp]; }

	virtual void update();
	virtual void render();
	virtual void handleEvents();
};