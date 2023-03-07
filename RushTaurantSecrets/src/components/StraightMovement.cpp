#include "./StraightMovement.h"

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
	// animación de moverse
	transform->setMovState(walking);
}

StraightMovement::StraightMovement(GameObject* parent, float speed) :
	Component(parent, id), offsetZone(3), speed(speed) {
	path.cont = 0;
	transform = parent->getComponent<Transform>();
}

void StraightMovement::addPath(const vector<Vector>& points) {
	vector<Vector> aux = RelativeToGlobal::points(points);

	// si ha terminado de recorrer el camino, cambia otro
	if (hasFinishedPath()) {
		path.points.reserve(aux.size());
		path.points = aux;
		path.cont = 0;
		newStraight(path.points[path.cont]);
	}
	// si no lo ha terminado de recorrer, el camino nuevo se añade al actual
	// solo va a suceder cuando se recoloquen clientes
	else {
		path.points.reserve(path.points.size() + aux.size());
		path.points.insert(path.points.end(), aux.begin(), aux.end());
	}
}

void StraightMovement::stop() {
	end = transform->getPos();
	path.cont = path.points.size();
	path.points.clear();
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
	}
}