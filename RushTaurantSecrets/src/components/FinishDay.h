#pragma once
#include "../structure/Component.h"
#include "../scenes/UIRestaurant.h"

class FinishDay : public Component {
private:
	UIRestaurant* ui;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_FINISH_DAY;

	FinishDay(GameObject* parent);
	void update();
};