#pragma once
#include "../structure/Component.h"
#include "ClockComponent.h"

class FinishDay : public Component {
private:
	ClockComponent* clock;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_FINISH_DAY;

	FinishDay(GameObject* parent);
	void update();
	void initComponent();
};