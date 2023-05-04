#pragma once
#include "../Structure/Component.h"
#include "../Components/Transform.h"
#include "../Structure/GameObject.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/checkML.h"

class ClientWithCart : public Component {
private:
	struct Animation {
		Texture* texture;
		int row;
		int actCol;
		int initCol;
		int endCol;
		float elapsedTime;
		float frameRate;
	};

	const float FRAME_RATE = 7;

	SDLUtils* sdl;

	Transform* transform;
	StraightMovement* straightMovement;
	Animation client;

	Animation cart;
	Vector offset;
	float nearEast;
	float nearWest;
	float nearNorth;
	float nearSouth;
	float widthCart;
	float heightCart;
	GOOrientation oldOrientation;
	bool changeToIdle;

	inline void setAnim(Animation& anim, int row, int initCol, int endCol) {
		anim.row = row;
		anim.initCol = initCol;
		anim.endCol = endCol;
		anim.actCol = initCol;
		anim.elapsedTime = 0;
	}

	inline void renderAnim(Animation anim, Vector pos, int width, int height) {
		SDL_Rect dest;
		dest.x = pos.getX();
		dest.y = pos.getY();
		dest.w = width * sdl->getResizeFactor();
		dest.h = height * sdl->getResizeFactor();
		anim.texture->renderFrame(dest, anim.actCol, anim.row, 0);
	}

	void updateAnim(Animation& anim) {
		anim.elapsedTime += deltaTime / 10;
		if (anim.elapsedTime > anim.frameRate) {
			anim.elapsedTime = 0;

			++anim.actCol;
			if (anim.actCol > anim.endCol) {
				anim.actCol = anim.initCol;
			}
		}
	}

	void changeDirection() {
		GOOrientation newOrientation = transform->getOrientation();
		if (newOrientation != oldOrientation) {
			setDirection(newOrientation);
			oldOrientation = newOrientation;
		}
	}

	void setDirection(GOOrientation orientation) {
		switch (orientation) {
		case east:
			offset = Vector(transform->getW() + nearEast, transform->getH() / 5.5);
			setAnim(cart, 0, 0, 2);
			setAnim(client, 8, 0, 5);
			break;

		case west:
			offset = Vector(-widthCart + nearWest, transform->getH() / 5.5);
			setAnim(cart, 0, 6, 8);
			setAnim(client, 8, 12, 17);
			break;

		case north:
			offset = Vector(-transform->getW() / 3, -heightCart + nearNorth);
			setAnim(cart, 0, 3, 5);
			setAnim(client, 8, 6, 11);
			break;

		case south:
			offset = Vector(-transform->getW() / 1.6, transform->getH() + nearSouth);
			setAnim(cart, 0, 9, 11);
			setAnim(client, 8, 18, 23);
			break;
		}
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENT_CART;

	ClientWithCart(GameObject* parent) : Component(parent, id), offset(),
		nearEast(-23), nearWest(41), nearNorth(100), nearSouth(-60),
		oldOrientation(none), changeToIdle(false) {

		sdl = SDLUtils::instance();

		transform = parent->getComponent<Transform>();
		straightMovement = parent->getComponent<StraightMovement>();
		client = { nullptr, 0 ,0, 0, 0, 0, FRAME_RATE };
		int aux = sdl->rand().nextInt(1, 15);
		client.texture = &sdl->images().at("Client_" + to_string(aux));

		cart = { nullptr, 0 ,0, 0, 0, 0, FRAME_RATE };
		cart.elapsedTime = sdl->currRealTime();
		cart.texture = &sdl->images().at("SHOPPING_CART");
		widthCart = transform->getW() * 2;
		heightCart = transform->getH();

		oldOrientation = transform->getOrientation();
		setDirection(oldOrientation);
	}

	virtual void update() {
		if (transform->getMovState() == pushing) {
			// después de estar parado, si vuelve a caminar en la misma orientación
			// hay que forzar a que se cambie la dirección
			if (changeToIdle) {
				changeToIdle = false;
				setDirection(oldOrientation);
			}
			changeDirection();
		}
		else if (transform->getMovState() == idle) {
			// se cambia solo una vez la animación a idle del personaje y se para el carrito
			if (!changeToIdle) {
				changeToIdle = true;
				setAnim(cart, 0, cart.initCol, cart.initCol);
				setAnim(client, 1, 18, 23);
			}
		}

		updateAnim(cart);

		updateAnim(client);
	}

	virtual void render() {
		if (oldOrientation == east || oldOrientation == west || oldOrientation == north) {
			renderAnim(cart, transform->getPos() + offset, widthCart, heightCart);
			renderAnim(client, transform->getPos(), transform->getW(), transform->getH());
		}
		else if (oldOrientation == south) {
			renderAnim(client, transform->getPos(), transform->getW(), transform->getH());
			renderAnim(cart, transform->getPos() + offset, widthCart, heightCart);
		}
	}
};