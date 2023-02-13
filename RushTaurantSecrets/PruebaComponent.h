#pragma once
#include "src/structure/Component.h"
#include "src/sdlutils/Texture.h"
class PruebaComponent:public Component
{
private:
	Texture* t;
public:
	PruebaComponent(Texture* _t,GameObject* parent, _ecs::id_type id):Component(parent, id),t(_t) {

	}
	virtual void render() {
		t->render(100, 100);
	}

	virtual void update() { }
	virtual void handleEvents() { }
};

