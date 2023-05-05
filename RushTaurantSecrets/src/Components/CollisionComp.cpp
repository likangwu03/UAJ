#include "CollisionComp.h"
#include "Transform.h"
#include <SDL_rect.h>
//#include "../structure/CollisionsManager.h"
#include "../Structure/GameObject.h"

#include "../Utilities/checkML.h"

CollisionComp::CollisionComp(GameObject* parent, Vector pos_, float width_, float height_) :Component(parent,id) {
	transform_ = parent->getComponent<Transform>();
	pos = pos_;
	width = width_;
	height = height_;
	//other_ = nullptr;
	//hasCollision_ = false;
}

void CollisionComp::Collision(GameObject* other) {
	transform_->setVel({ 0,0 });
}

SDL_FRect CollisionComp::getRect() {
	return { pos.getX() + transform_->getPos().getX(), pos.getY() + transform_->getPos().getY(), width, height };
}