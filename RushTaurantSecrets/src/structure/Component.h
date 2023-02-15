#pragma once
#include "Structure_def.h"

class GameObject;

class Component {
protected:
	GameObject* parent;
	bool alive;
public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_INVALID;

	Component(GameObject* parent, _ecs::_cmp_id id);
	virtual ~Component() { }

	inline bool isAlive() { return alive; }

	virtual void update() { }
	virtual void render() { }
	virtual void handleEvents() { }
};