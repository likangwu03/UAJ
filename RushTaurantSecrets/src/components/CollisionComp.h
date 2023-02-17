#pragma once
#include "../structure/Component.h"
#include <SDL_rect.h>
#include "../utilities/Vector.h"
class Transform;
class GameObject;
//class CollisionsManager;
class CollisionComp:public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COLLISIONS;
protected:
	//CollisionsManager* collisionsManager_;
	Transform* transform_;
	//GameObject* other_;
	//bool hasCollision_;
	Vector pos;
	float width;
	float height;

public:
	CollisionComp(GameObject* parent,Vector pos_,float width_,float height_);
	//bool hasCollision() { return hasCollision_; }
	//llamado por CollisionsManager
	virtual void Collision(GameObject* other);
	//virtual void update() { }
	SDL_FRect getRect();
protected:


};

