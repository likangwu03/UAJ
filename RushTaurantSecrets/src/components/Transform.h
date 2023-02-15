#pragma once
#include "../structure/Component.h"
#include "../utilities/Vector.h"
#include "../structure/Structure_def.h"

class Transform : public Component {
protected:
	Vector pos, vel;
	float w, h, r;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TRANSFORM;

	Transform(GameObject* parent, Vector const& pos = Vector(0, 0), Vector const& vel = Vector(0, 0), float width = 0, float height = 0, float rotation = 0)
		: Component(parent, id), pos(pos), vel(vel), w(width), h(height), r(rotation) { }
	virtual ~Transform() { }
	inline Vector getPos() const { return pos; };
	inline Vector getVel() const { return vel; };
	inline float getW() const { return w; }
	inline float getH() const { return h; }
	inline float getRot() const { return r; }

	inline void setVel(Vector const& vel) { this->vel = vel; }
	inline void setRot(float rot) { r = rot; }

	virtual void update() { pos = pos + vel; };
};