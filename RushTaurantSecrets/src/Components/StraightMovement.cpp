#include "StraightMovement.h"
#include "../Utilities/checkML.h"

Vector StraightMovement::pointStraight(float t) {
	Vector dir = end - transform->getPos();
	dir = dir.getNormalized();
	return transform->getPos() + dir * t;
}

// dirección del movimiento
void StraightMovement::calculateDir() {
	Vector pos = transform->getPos();
	Vector dir = end - pos;

	if (dir.getX() > 0) {
		transform->setOrientation(east);
	}
	else if (dir.getX() < 0) {
		transform->setOrientation(west);
	}
	else if (dir.getY() > 0) {
		transform->setOrientation(south);
	}
	else if (dir.getY() < 0) {
		transform->setOrientation(north);
	}
}

bool StraightMovement::hasArrivedPoint() const {
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

// se establece una nueva recta
void StraightMovement::newStraight(const Vector& end) {
	this->end = end;
	calculateDir();
	// transform->setMovState(walking);
}

void StraightMovement::newPath(const vector<Vector>& newPath) {
	// se añaden los puntos a recorrer
	path.points.reserve(newPath.size());
	path.points = newPath;
	path.cont = 0;

	// se establece la recta a recorrer
	newStraight(path.points[path.cont]);

	// se cambia la animación y se indica que se est?moviendo
	transform->setMovState(walkingState);
	isWalking = true;
}

void StraightMovement::tripTimer(bool& trip, float& timer) {
	if (timer > 0 && trip) {
		elapsedTime += deltaTime;
		if (elapsedTime > timer) {
			elapsedTime = 0;
			trip = false;
			timer = -1;
			stop();
		}
	}
}

StraightMovement::StraightMovement(GameObject* parent, float speed) :
	Component(parent, id), offsetZone(3), speed(speed), roundTrip(false),
	roundTripTime(-1), numLaps(-1), actNumLaps(0), loop(false), loopTime(-1), 
	elapsedTime(0), walkingState(walking), isWalking(), path() {

	transform = parent->getComponent<Transform>();
	// se crea un camino con el punto inicial de modo que se consigue que:
	// - se queden quietos cuando se crean si no se añaden más caminos
	// - se guarde el punto inicial por si se quiere dar media vuelta
	newPath({ transform->getPos() });
}

void StraightMovement::addPath(const vector<Vector>& points) {
	// si ha terminado de recorrer el camino, cambia a otro
	if (hasFinishedPath()) {
		newPath(points);
	}
	// si no lo ha terminado de recorrer, el camino nuevo se añade al actual
	// va a sucede cuando se recoloquen clientes y la primera vez
	// que se crean porque el punto inicial se guarda en el vector
	else {
		path.points.reserve(path.points.size() + points.size());
		path.points.insert(path.points.end(), points.begin(), points.end());
	}
}

void StraightMovement::stop() {
	end = transform->getPos();
	path.cont = path.points.size();
}

void StraightMovement::goBack() {
	// dos opciones
	vector<Vector> aux;
	// se ha recorrido todo el camino, por lo tanto, se vuelve a dar media vuelta
	if (hasFinishedPath()) {
		aux.reserve(path.points.size());
		for (int i = path.points.size() - 1; i >= 0; --i) {
			aux.push_back(path.points[i]);
		}
	}
	// no se ha recorrido todo el camino
	else {
		aux.reserve(path.cont);
		// se guardan en un vector auxiliar los puntos que ya se han recorrido
		for (int i = path.cont - 1; i >= 0; --i) {
			aux.push_back(path.points[i]);
		}
	}
	newPath(aux);
}

void StraightMovement::update() {
	// recorriendo la recta
	if (!hasArrivedPoint()) {
		transform->setPos(pointStraight(speed));
	}
	// cuando ha terminado de recorrer una recta pasa a comprobar si puede recorrer otra
	else {
		++path.cont;
		// si no ha terminado de recorrer el camino, recorre la siguiente recta
		if (!hasFinishedPath()) {
			newStraight(path.points[path.cont]);
		}
		// si ha terminado de recorrer el camino y esta en ida y vuelta, da media vuelta
		else if (roundTrip) {
			// media vuelta por número de vueltas
			if (numLaps != -1) {
				actNumLaps += 1;

				if (actNumLaps >= numLaps) {
					numLaps = -1;
					roundTrip = false;
				}
			}

			if (roundTrip) {
				goBack();
			}
		}
		// si ha terminado de recorrer el camino y esta en loop, vuelve a recorrerlo
		else if (loop) {
			path.cont = 0;
			newStraight(path.points[path.cont]);
		}
		else {
			if (isWalking) {
				transform->setMovState(idle);
				isWalking = false;
			}
		}
	}

	tripTimer(roundTrip, roundTripTime);

	tripTimer(loop, loopTime);
}