#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* parent, _ecs::_cmp_id id) : parent(parent), alive(true) {
	parent->addComponent(this, id);
}