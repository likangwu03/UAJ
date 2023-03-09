#pragma once

#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../utilities/Vector.h"
#include "../components/Transform.h"
#include "../structure/GameObject.h"
#include "../sdlutils/SDLUtils.h"
#include "../objects/RelativeToGlobal.h"

using namespace std;

struct Path {
	// vector con los puntos a recorrer en ese camino
	vector<Vector> points;
	// contador que indica por que punto del camino se est?recorriendo
	// se hace de esta manera porque no se puede pop a una estructura de datos de pares
	int cont;
};

class StraightMovement : public Component {
private:
	Transform* transform;
	Path path;
	Vector end;
	float speed;	// velocidad en ir de un punto a otro
	float offsetZone;	// tiene que ser un número pequeño

	// recorrer recta
	Vector pointStraight(float t);

	// dirección del movimiento
	void calculateDir();

	// indica cuando se ha llegado al final de un punto para recorrer el siguiente del vector
	bool hasArrivedPoint() const;

	// se establece una nueva recta
	void newStraight(const Vector& end);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_STRAIGHT_MOVEMENT;

	StraightMovement(GameObject* parent, float speed);

	void addPath(const vector<Vector>& points);

	void stop();

	void goBack(const Vector& last);

	inline bool hasFinishedPath() const {
		return path.cont >= path.points.size();
	}

	inline void changeSpeed(float speed) {
		this->speed = speed;
	}

	inline Vector getLastPoint() const {
		return path.points.back();
	}

	virtual void update();
};