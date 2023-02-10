#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* parent, _ecs::id_type id) : parent(parent), alive(true) {
	parent->addComponent(this, id);
}