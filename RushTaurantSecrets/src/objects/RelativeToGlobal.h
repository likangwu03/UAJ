#pragma once

#include "../utilities/Vector.h"
#include "../sdlutils/SDLUtils.h"
#include <vector>

using namespace std;

namespace RelativeToGlobal {
	static const int nTilesW = 40;
	static const int nTilesH = 23;

	// convertir un punto relativo en global
	inline static Vector point(Vector point) {
		int fWidth = SDLUtils::instance()->width() / nTilesW;
		int fHeight = SDLUtils::instance()->height() / nTilesH;
		return Vector(point.getX() * fWidth, point.getY() * fHeight);
	}

	// convertir una serie de puntos relativos en globales
	static vector<Vector> points(const vector<Vector>& points) {
		vector<Vector> aux;
		for (int i = 0; i < points.size(); ++i) {
			aux.push_back(point(points[i]));
		}
		return aux;
	}
};