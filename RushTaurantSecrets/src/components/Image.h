#pragma once

#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "../structure/GameObject.h";

class Image : public Component {
private:
	// componente transform para consultar las características físicas del gameobject
	Transform* transform = nullptr;
	Texture* texture = nullptr;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_IMAGE;

	Image(GameObject* parent, Texture* texture) : Component(parent, id), texture(texture) {
		// importante que se añada el Transform antes de Image porque sino no se va a encontrar la ref
		// se guarda la referencia al Transform de la entidad
		transform = parent->getComponent<Transform>();
		// se produce un error si no se encuentra
		assert(texture != nullptr);
	}

	void setTexture(Texture* t) { texture = t; }

	virtual void render() {
		SDL_Rect dest;
		dest.x = transform->getPos().getX();
		dest.y = transform->getPos().getY();
		dest.w = transform->getW();
		dest.h = transform->getH();
		// renderiza la textura
		texture->render(dest, transform->getRot());
	}
};