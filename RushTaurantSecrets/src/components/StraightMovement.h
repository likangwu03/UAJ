#pragma once

#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../utilities/Vector.h"
#include "../components/Transform.h"
#include "../structure/GameObject.h"
#include "../sdlutils/SDLUtils.h"

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
	SDLUtils* sdl;

	// recorrer recta
	Vector pointStraight(float t) {
		Vector dir = end - transform->getPos();
		dir = dir.getNormalized();
		return transform->getPos() + dir * t;
	}

	// dirección del movimiento
	void calculateDir() {
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

	// indica cuando se ha llegado al final de un punto para recorrer el siguiente del vector
	bool hasArrivedPoint() const {
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
	void newStraight(const Vector& end) {
		this->end = end;
		calculateDir();
		// animación de moverse
		transform->setMovState(walking);
	}

	vector<Vector> relativeToGlobal(const vector<Vector>& points) {
		vector<Vector> aux;
		int fWidth = sdl->width() / 40;
		int fHeight = sdl->height() / 23;
		for (int i = 0; i < points.size(); ++i) {
			int x = points[i].getX();
			int y = points[i].getY();
			aux.push_back(Vector(x * fWidth, y * fHeight));
		}
		return aux;
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_STRAIGHT_MOVEMENT;

	StraightMovement(GameObject* parent, float speed) :
		Component(parent, id), offsetZone(3), speed(speed) {
		sdl = SDLUtils::instance();
		path.cont = 0;
		transform = parent->getComponent<Transform>();
	}

	void addPath(const vector<Vector>& points) {
		vector<Vector> aux = relativeToGlobal(points);

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

	void stop() {
		end = transform->getPos();
		path.cont = path.points.size();
	}

	bool hasFinishedPath() const {
		return path.cont >= path.points.size();
	}

	void changeSpeed(float speed) {
		this->speed = speed;
	}

	Vector getLastPoint() const {
		return path.points.back();
	}

	virtual void update() {
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
};