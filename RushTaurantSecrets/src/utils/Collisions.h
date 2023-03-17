#pragma once

#include "Vector2D.h"
#include "../utilities/Vector.h"

/*
 *
 */
class Collisions {
public:
	// virtual ~Collisions();

	// checks if two boxes o1 and o2 collides
	static bool collides( //
			const Vector &o1Pos, float o1Width, float o1Height, //
			const Vector &o2Pos, float o2Width, float o2Height);

	// checks if two boxed o1 and o2 collides, taking into account the rotation of both
	static bool collidesWithRotation( //
			const Vector &o1Pos, float o1Width, float o1Height, float o1Rot, //
			const Vector &o2Pos, float o2Width, float o2Height, float o2Rot);

private:
	Collisions() = delete;

	// checks if the point P is in the triangle defined by A,B,C
	static bool PointInTriangle(const Vector &A, const Vector &B,
			const Vector &C, const Vector &P);

	// checks if the point P is in the rectangle defined by the rectangle
	//
	//     A --- B
	//     |     |
	//     |     |
	//     D --- C
	//
	static bool PointInRectangle(const Vector &A, const Vector &B,
			const Vector &C, const Vector &D, const Vector &P);

};
