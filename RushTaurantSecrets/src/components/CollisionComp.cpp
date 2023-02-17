#include "CollisionComp.h"
#include "Transform.h"
#include <SDL_rect.h>
//#include "../structure/CollisionsManager.h"
#include "../structure/GameObject.h"

CollisionComp::CollisionComp(GameObject* parent, Vector pos_, float width_, float height_) :Component(parent,id) {
	transform_ = parent->getComponent<Transform>();
	pos = pos_;
	width = width_;
	height = height_;
	//other_ = nullptr;
	//hasCollision_ = false;
}
void CollisionComp::Collision(GameObject* other) {
	Transform* aux=other->getComponent<Transform>();
	SDL_FRect targe ={aux->getPos().getX(),aux->getPos().getY(),aux->getW(),aux->getH()};
	SDL_FRect obj = { transform_->getPos().getX(),transform_->getPos().getY(),transform_->getW(),transform_->getH() };
	SDL_FRect result;
	SDL_IntersectFRect(&targe, &obj, &result);
	Vector dir = transform_->getVel();
	float s = sqrtf(result.w * result.w + result.h * result.h);
	transform_->setPos(transform_->getPos() - (dir.getNormalized() * s));
}
SDL_FRect CollisionComp::getRect() {
	return { pos.getX() + transform_->getPos().getX(), pos.getY() + transform_->getPos().getY(), width, height };
};