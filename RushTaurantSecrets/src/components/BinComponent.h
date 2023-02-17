#pragma once
#include "../structure/Component.h"
#include "../utilities/Vector.h"

class BinComponent : public Component
{
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BIN;
	BinComponent(GameObject* parent, Vector pos);
};