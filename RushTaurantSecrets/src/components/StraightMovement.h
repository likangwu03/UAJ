#pragma once

#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../utilities/Vector.h"
#include "../components/Transform.h"
#include "../structure/GameObject.h"

using namespace std;

enum Direction{Left, Right, Up, Down};

class StraightMovement : public Component {
private:
	Transform* transform;
	vector<Vector> points;
	int cont;
	Vector end;
	float speed;	// velocidad en ir de un punto a otro
	Vector act;
	float offsetZone;	// tiene que ser un número pequeño
	Direction direction;

	constexpr static _ecs::_cmp_id id = _ecs::cmp_STRAIGHT_MOVEMENT;

	// recorrer recta
	Vector pointLine(float t) {
		Vector dir = end - transform->getPos();
		dir = dir.getNormalized();
		return transform->getPos() + dir * t;
	}

	bool hasArrived() const {
		float posX = transform->getPos().getX();
		float posY = transform->getPos().getY();
		// se comprueba que el cliente ha llegado a una zona próxima al punto final
		if (posX + offsetZone >= end.getX() && posX - offsetZone <= end.getX()
			&& posY + offsetZone >= end.getY() && posY - offsetZone <= end.getY()) {
			// se soluciona el error
			transform->setPos(end);
			return true;
		}
		return false;
	}

	void calculateDir() {
		Vector pos = transform->getPos();
		Vector dir = end - pos;
		if (dir.getX() > 0) {
			direction = Right;
		}
		else if (dir.getX() < 0) {
			direction = Left;
		}
		else if (dir.getY() > 0) {
			direction = Down;
		}
		else if (dir.getY() < 0) {
			direction = Up;
		}
	}

public:
	StraightMovement(GameObject* parent, vector<Vector> points, float speed) :
		Component(parent, id), points(points), offsetZone(2), cont(0) {
		transform = parent->getComponent<Transform>();
		transform->setPos(points[cont]);
		++cont;
		newPath(points[cont], 2);
	}

	Direction getDir() const {
		return direction;
	}

	// se establece un nuevo camino
	void newPath(const Vector& end, float speed) {
		this->end = end;
		this->speed = speed;
		calculateDir();
	}

	virtual void update() {
		if (!hasArrived()) {
			transform->setPos(pointLine(speed));
		}
		else {
			++cont;
			if (cont >= points.size()) {
				cont = 0;
			}
			newPath(points[cont], speed);
		}
	}
};