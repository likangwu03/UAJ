#include "TriggerComp.h"
#include "Transform.h"
#include "../structure/GameObject.h"
//#include "../structure/CollisionsManager.h"
TriggerComp::TriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :Component(parent, id){
	transform_ = parent->getComponent<Transform>();
	other_ = nullptr;
	overlap_ = false;
	pos = pos_;
	width = width_;
	height = height_;
}

void TriggerComp::Overlap(GameObject* other) {
	if (other == nullptr && overlap_ == true) {
		OnTriggerExit();
		overlap_ = false;
	}
	other_ = other;
	if (other != nullptr&& overlap_ == false) {
		OnTriggerEnter();
		overlap_ = true;
	}
}
SDL_FRect TriggerComp::getRect() {
	return { pos.getX() + transform_->getPos().getX(), pos.getY() + transform_->getPos().getY(), width, height };
};