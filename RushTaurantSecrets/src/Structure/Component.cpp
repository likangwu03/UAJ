#include "Component.h"
#include "GameObject.h"
#include "Scene.h"

Component::Component(GameObject* parent, _ecs::_cmp_id id,bool active) : parent(parent), alive(true),active(active), deltaTime(parent->scene->frameTime) {
	parent->addComponent(this, id);
}

void Component::setActive(bool b) {
	active = b;
}
