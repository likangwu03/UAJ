#pragma once
#include "../structure/Component.h"
#include "../structure/Food_def.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "Image.h"
#include <set>

class DailyMenuComp : public Component
{
private:
	Transform* tf;
	void drawDishes(vector<_ecs::DishInfo> menu);
	Scene* parentScene;
	vector<_ecs::DishInfo> menu;
	vector<_ecs::DishInfo> randomMenu();
	uint8_t menuSize;
	uint8_t spriteSize;

	bool murder;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_DAILYMENU;
	DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, uint8_t mSize = 4, bool m = false);
};

