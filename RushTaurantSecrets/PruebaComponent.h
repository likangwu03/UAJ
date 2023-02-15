#pragma once
#include "src/structure/Component.h"
#include "src/sdlutils/Texture.h"
#include "src/components/Transform.h"
#include "src/structure/GameObject.h"

class PruebaComponent:public Component
{
private:
	Transform* transform = nullptr;
	Texture* t;
public:
	PruebaComponent(Texture* _t,GameObject* parent, _ecs::_cmp_id id):Component(parent, id),t(_t) {
		transform = parent->getComponent<Transform>();
	}
	virtual void render() {
		t->render(transform->getPos().getX(), transform->getPos().getY());
	}

	virtual void update() { }
	virtual void handleEvents() { }
};

