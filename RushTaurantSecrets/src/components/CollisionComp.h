#pragma once
#include "../structure/Component.h"
class Transform;
class GameObject;
class CollisionsManager;
class CollisionComp:public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COLLISIONS;

protected:
	CollisionsManager* collisionsManager_;
	Transform* transform_;
	GameObject* other_;
	bool hasCollision_;
public:
	CollisionComp();
	bool hasCollision() { return hasCollision_; }
	//llamado por CollisionsManager
	virtual void Collision(GameObject* other) { other_ = other; hasCollision_ = other!=nullptr;}
	virtual void update() { }
protected:


};

