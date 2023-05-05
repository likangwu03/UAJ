#pragma once
#include "../Structure/Component.h"
#include "../Components/StraightMovement.h"

class Route : public Component {
protected:
	StraightMovement* straightMovement;
	Transform* transform;

	void addPath(vector<Vector> points) {
		straightMovement->addPath(RelativeToGlobal::pointsRestaurant(points));
	}

	void reset(Vector point) {
		straightMovement->reset(RelativeToGlobal::pointRestaurant(point));
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_ROUTE;

	Route(GameObject* parent, Vector initPos) : Component(parent, id) {
		straightMovement = parent->getComponent<StraightMovement>();
		reset(initPos);

		transform = parent->getComponent<Transform>();
	}
};
