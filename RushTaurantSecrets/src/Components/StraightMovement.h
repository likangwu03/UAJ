#pragma once

#include "../Structure/Component.h"
#include "../Definitions/Structure_def.h"
#include "../Utilities/Vector.h"
#include "Transform.h"
#include "../Structure/GameObject.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/RelativeToGlobal.h"

using namespace std;

struct Path {
	// vector con los puntos a recorrer en ese camino
	vector<Vector> points;
	// contador que indica por que punto del camino se est?recorriendo
	// se hace de esta manera porque no se puede pop a una estructura de datos de pares
	int cont;
};

// Se pierde memoria del camino que ha recorrido cuando:
// - Se ha recorrido un camino entero y se ha añade otro
// - Se da media vuelta
class StraightMovement : public Component {
private:
	Transform* transform;
	Path path;
	Vector end;
	float speed;	// velocidad en ir de un punto a otro
	float offsetZone;	// tiene que ser un número pequeño

	// activar/desactivar la ida y vuelta
	bool roundTrip;
	// si roundTripTime es -1, pero numLaps no, se trata de un recorrido por vueltas
	// si numLaps es -1, pero roundTripTime no, se trata de un recorrido por timepo
	// si ambos son -1, se trata de una ida y vuelta infinita
	float roundTripTime;
	// número de vueltas a dar
	int numLaps;
	// cuántas vueltas ha dado de momento
	int actNumLaps;

	// activar/desactivar loop
	bool loop;
	// -1 si el loop es infinito
	float loopTime;

	float elapsedTime;
	bool isWalking;
	movementState walkingState;

	// recorrer recta
	Vector pointStraight(float t);

	// dirección del movimiento
	void calculateDir();

	// indica cuando se ha llegado al final de un punto para recorrer el siguiente del vector
	bool hasArrivedPoint() const;

	// se establece una nueva recta
	void newStraight(const Vector& end);

	// se establece un nuevo camino a partir de una serie de puntos
	void newPath(const vector<Vector>& newPath);

	// temporizador del recorrido
	void tripTimer(bool& trip, float& timer);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_STRAIGHT_MOVEMENT;

	StraightMovement(GameObject* parent, float speed);

	void addPath(const vector<Vector>& points);

	void stop();

	void goBack();

	inline bool hasFinishedPath() const {
		return path.cont >= path.points.size();
	}

	inline void changeSpeed(float speed) {
		this->speed = speed;
	}

	inline Vector getLastPoint() const {
		return path.points.back();
	}

	// activar ida y vuelta por número de vueltas
	inline void enableRoundTripByLaps(int numLaps) {
		roundTrip = true;
		this->numLaps = numLaps * 2;
	}
	// activar ida y vuelta por tiempo
	inline void enableRoundTripByTime(float time) {
		roundTrip = true;
		roundTripTime = time * 1000;
	}
	inline void enableInfiniteRoundTrip() {
		roundTrip = true;
	}
	inline bool roundTripEnded() const {
		return roundTrip;
	}

	// activar loop por tiempo
	inline void enableLoop(float time) {
		loop = true;
		loopTime = time;
	}
	inline void enableInfiniteLoop() {
		loop = true;
	}
	inline bool loopEnded() {
		return loop;
	}

	inline void setWalkingState(movementState newWalkingState) {
		walkingState = newWalkingState;
		transform->setMovState(walkingState);
	}

	virtual void update();
};