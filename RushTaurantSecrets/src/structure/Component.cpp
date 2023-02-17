#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* parent, _ecs::_cmp_id id,bool active) : parent(parent), alive(true),active(active) {
	parent->addComponent(this, id);
}

void Component::setActive(bool b) {
	if (b != active) active = b;
}
