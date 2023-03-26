#pragma once
#include "../Structure/Component.h"
#include "../Definitions/Structure_def.h"
#include "Transform.h"
#include "../Utilities/Texture.h"
#include "../Utilities/SDLUtils.h"
#include "../Structure/GameObject.h";

using namespace std;

class Image : public Component {
private:
	Transform* transform;
	Texture* texture;
	SDLUtils* sdl;
	Vector offset;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_IMAGE;

	Image(GameObject* parent, Texture* texture, Vector _offset = Vector::zero) 
		: Component(parent, id), texture(texture), sdl(SDLUtils::instance()), offset(_offset) {
		transform = parent->getComponent<Transform>();

		assert(texture != nullptr);
	}

	Image(GameObject* parent, string s, Vector _offset = Vector::zero) 
		: Component(parent, id), sdl(SDLUtils::instance()), offset(_offset) {
		transform = parent->getComponent<Transform>();
		texture = &((*sdl).images().at(s));

		assert(texture != nullptr);
	}

	void setTexture(Texture* t) { texture = t; }
	void setTexture(string s) { texture = &((*sdl).images().at(s)); }
	void setOffset(Vector _offset) { offset = _offset;}

	virtual void render() {
		SDL_Rect dest;
		dest.x = transform->getPos().getX() + offset.getX();
		dest.y = transform->getPos().getY() + offset.getY();
		dest.w = transform->getW();
		dest.h = transform->getH();
		// renderiza la textura
		texture->render(dest, transform->getRot());
	}
};