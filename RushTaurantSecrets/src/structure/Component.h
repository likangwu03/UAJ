#pragma once
#include "Structure_def.h"

class GameObject;

class Component {
protected:
	GameObject* parent;
public:
	static constexpr _ecs::id_type id = _ecs::cmp_INVALID;

	Component(GameObject* parent);
	virtual ~Component() { }
};