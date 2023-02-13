#pragma once
#include "../structure/Component.h"
#include <vector>

class Client;
class Transform;

class DeskComp : public Component {
private:
	Transform* trans;
	std::vector<Client*> assigned;
public:
	constexpr static _ecs::id_type id = _ecs::cmp_DESK;

	DeskComp(GameObject* parent) : Component(parent, id) { }
	bool assignClients();
};