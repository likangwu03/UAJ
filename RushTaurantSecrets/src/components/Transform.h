#pragma once
#include "../structure/Component.h"
#include "../utilities/Vector.h"
#include "../structure/Structure_def.h"

class Transform : public Component {
private:
	Vector pos, vel;
	float w, h, r;
public:
	constexpr static _ecs::id_type id = _ecs::cmp_TRANSFORM;

	Transform(GameObject* parent, Vector const& pos = Vector::zero, float width = 0, float height = 0, float rotation = 0) : Component(parent, id), pos(pos), vel(), w(width), h(height), r(rotation) { }
	virtual ~Transform() { }
	inline Vector getPos() const { return pos; };
	inline Vector getVel() const { return vel; };
	inline float getW() const { return w; }
	inline float getH() const { return h; }
	inline float getRot() const { return r; }

	inline void setVel(Vector const& vel) { this->vel = vel; }
	inline void setRot(float rot) { r = rot; }

	void update() { pos = pos + vel; };
};