#pragma once
#include "../structure/Component.h"
#include "../structure/GameObject.h"
#include "../exceptions/CompNotFound.h"
#include <vector>

class Client;
class Transform;

class DeskComp : public Component {
private:
	Transform* trans;
	std::vector<Client*> assigned;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_DESK;

	DeskComp(GameObject* parent) : Component(parent, id) {
		trans = parent->getComponent<Transform>();
		if(trans == nullptr) {
			throw exceptions::CompNotFound("Transform", "DeskComp");
		}
	}

	bool assignClients() {

	}
};