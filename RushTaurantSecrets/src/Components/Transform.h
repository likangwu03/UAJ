#pragma once
#include "../Structure/Component.h"
#include "../Utilities/Vector.h"
#include "../Definitions/Structure_def.h"

enum GOOrientation {
	north, east, west, south, none
};

enum movementState {
	idle, walking, sleeping, pushing, cart, sitting, dead, noMov
};

class Transform : public Component {
protected:
	Vector pos, vel;
	float w, h, r;
	GOOrientation orientation;
	movementState movState;
	bool statc;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TRANSFORM;

	Transform(GameObject* parent, Vector const& pos = Vector::zero, Vector const& vel = Vector::zero, float width = 0, float height = 0, float rotation = 0, bool sta = false)
		: Component(parent, id), pos(pos), vel(vel), w(width), h(height), r(rotation), orientation(south), movState(idle), statc(sta) { }
	virtual ~Transform() { }
	// getters
	inline Vector getPos() const { return pos; };
	inline Vector getVel() const { return vel; };
	inline float getW() const { return w; }
	inline float getH() const { return h; }
	inline float getRot() const { return r; }
	inline movementState getMovState() const { return this->movState; }
	inline bool isStatic() const { return statc; }
	// setters
	inline void setVel(Vector const& vel) { this->vel = vel; }
	inline void setRot(float rot) { r = rot; }
	inline void setPos(Vector const& pos) { this->pos = pos; }
	inline void setMovState(movementState ms) { this->movState = ms; }
	inline void setW(float width) { w = width; }
	inline void setH(float height) { h = height; }

	GOOrientation getOrientation() { return orientation; }
	void setOrientation(GOOrientation o) { this->orientation = o; }

	virtual void update() { pos = pos + vel; };
};