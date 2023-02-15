#pragma once
#include <vector>
#include <array>
#include "Structure_def.h"
#include "../sdlutils/InputHandler.h"
class GameObject;
using namespace _ecs;
class Scene {
protected:
	InputHandler* ih;
	std::array<std::vector<GameObject*>, _ecs::grpNum> objGroups;
	Scene();

public:
	virtual ~Scene();

	void addObject(GameObject* object, _ecs::_grp_id grp);
	void refresh();
	inline const std::vector<GameObject*>& getGroup(_ecs::_grp_id grp) { return objGroups[grp]; }

	virtual void update();
	virtual void render();
	virtual void handleEvents();
};