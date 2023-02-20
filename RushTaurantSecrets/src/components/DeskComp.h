#pragma once
#include "../structure/Component.h"
#include <vector>
class Transform;

class DeskComp : public Component {
private:
	Transform* trans;
	std::vector<GameObject*> assigned;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_DESK;

	DeskComp(GameObject* parent);

	bool assignClients(GameObject* first, GameObject* second = nullptr, GameObject* third = nullptr, GameObject* fourth = nullptr);

	bool receiveDish(GameObject* dish);
};