#pragma once
#include "../Structure/Component.h"
#include <SDL_rect.h>
#include "../Utilities/Vector.h"
class Transform;
class GameObject;
class CollisionComp:public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COLLISIONS;
protected:
	Transform* transform_;
	Vector pos;
	float width;
	float height;

public:
	CollisionComp(GameObject* parent,Vector pos_,float width_,float height_);
	
	virtual void Collision(GameObject* other);
	SDL_FRect getRect();
};

