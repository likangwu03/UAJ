#pragma once
#include "Structure_def.h"

class GameObject;

class Component {
protected:
	GameObject* parent;
	bool alive;
public:
	static constexpr _ecs::id_type id = _ecs::cmp_INVALID;

	Component(GameObject* parent, _ecs::id_type id);
	virtual ~Component() { }

	inline bool isAlive() { return alive; }

	virtual void update() { }
	virtual void render() { }
	virtual void handleEvents() { }
};