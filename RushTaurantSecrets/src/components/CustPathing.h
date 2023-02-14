#pragma once

#include "../components/Transform.h"
#include "../utilities/Vector.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/SDLUtils.h"
#include <deque>

using namespace std;

// cuadrante al que se dirige
enum Quadrant {First, Second, Third, Fourth, Yn, Yp, Xp, Xn};

class CustPathing : public Transform {
private:
	Vector origin;	
	Vector end;
	Vector dir;	// dirección de la recta que recorrer
	float speed = 0;	// velocidad en ir de un punto a otro
	float t = 0;	// calcular puntos de la recta
	Quadrant q = First;	// cuadrante al que se dirige

	// hallar punto de una recta
	Vector pointStraight(float t) {
		dir = dir.getNormalized();
		return origin + dir * t;
	}

	// se determina el cuadrante hacia donde se dirige
	// están invertidos resepcto a cómo siempre
	void detQuad(Vector dir) {
		if (dir.getX() > 0 && dir.getY() < 0) {
			q = First;
		}
		else if (dir.getX() < 0 && dir.getY() < 0) {
			q = Second;
		}
		else if (dir.getX() < 0 && dir.getY() > 0) {
			q = Third;
		}
		else if (dir.getX() > 0 && dir.getY() > 0) {
			q = Fourth;
		}
		// ejes y
		else if (dir.getX() == 0) {
			if (dir.getY() < 0) {
				q = Yn;
			}
			else {
				q = Yp;
			}
		}
		// eje x
		else if (dir.getY() == 0) {
			if (dir.getX() < 0) {
				q = Xn;
			}
			else {
				q = Xp;
			}
		}
	}

	void calDir() {
		dir = end - origin;
		detQuad(dir);
	}

public:
	CustPathing(GameObject* parent, Vector origin, Vector end, float speed, float width = 0, float height = 0) :
		Transform(parent, origin, Vector(0, 0), width, height, 0), origin(origin), end(end), speed(speed) {
		// se calcula el vector director de la recta
		calDir();
	}

	// se establece un nuevo camino
	void newPath(Vector end) {
		origin = pos;
		this->end = end;
		calDir();
	}

	// dependiendo del cuadrante hacia donde se dirija se comprueba si ha llegado o no
	bool hasArrived() {
		switch (q) {
		case First:
			if (pos.getX() >= end.getX() && pos.getY() <= end.getY()) {
				return true;
			}
		case Second:
			if (pos.getX() <= end.getX() && pos.getY() <= end.getY()) {
				return true;
			}
		case Third:
			if (pos.getX() <= end.getX() && pos.getY() >= end.getY()) {
				return true;
			}
			break;
		case Fourth:
			if (pos.getX() >= end.getX() && pos.getY() >= end.getY()) {
				return true;
			}
			break;
		case Yn:
			if (pos.getY() <= end.getY()) {
				return true;
			}
			break;
		case Yp:
			if (pos.getY() >= end.getY()) {
				return true;
			}
			break;
		case Xn:
			if (pos.getX() <= end.getX()) {
				return true;
			}
			break;
		case Xp:
			if (pos.getX() >= end.getY()) {
				return true;
			}
			break;
		}
		return false;
	}

	virtual void update() {
		if (!hasArrived()) {
			t += speed;
			pos = pointStraight(t);
		}
	}
};