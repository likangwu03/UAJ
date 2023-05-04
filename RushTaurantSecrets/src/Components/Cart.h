#pragma once
#include "../Structure/Component.h"
#include "../Components/Transform.h"
#include "../Structure/GameObject.h"
#include "../Utilities/SDLUtils.h"

class Cart : public Component {
private:
	Transform* transform;
	SDLUtils* sdl;
	Texture* cart;
	Vector offset;
	float offsetEast;
	float offsetWest;
	float offsetNorth;
	float offsetSouth;
	int width;
	int height;
	int direction;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CART;

	Cart(GameObject* parent, int width, int height) : Component(parent, id), offset(), direction(0),
		offsetEast(-20), offsetWest(10), offsetNorth(55), offsetSouth(-50) {
		transform = parent->getComponent<Transform>();
		sdl = SDLUtils::instance();
		cart = &sdl->images().at("SHOPPING_CART");
		this->width = width * sdl->getResizeFactor();
		this->height = height * sdl->getResizeFactor();
	}

	virtual void update() {
		switch (transform->getOrientation()) {
		case east:
			offset = Vector(transform->getW() + offsetEast, transform->getH() / 6);
			direction = 0;
			break;
		case west:
			offset = Vector(-width + offsetWest, transform->getH() / 6);
			direction = 6;
			break;
		case north:
			//offset = Vector(0, 0);
			offset = Vector(-transform->getW() / 3.5, -height + offsetNorth);
			direction = 3;
			break;
		case south:
			//offset = Vector(0, 0);
			offset = Vector(-transform->getW() / 1.8, transform->getH() + offsetSouth);
			direction = 9;
			break;
		}
	}

	virtual void render() {
		SDL_Rect dest;
		dest.x = transform->getPos().getX() + offset.getX();
		dest.y = transform->getPos().getY() + offset.getY();
		dest.w = width;
		dest.h = height;
		cart->renderFrame(dest, direction, 0, 0);
	}
};