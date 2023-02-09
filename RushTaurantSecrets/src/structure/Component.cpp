#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* parent) : parent(parent), alive(true) {
	parent->addComponent(this);
}