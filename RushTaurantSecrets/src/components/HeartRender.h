#pragma once

#include "../structure/Component.h"
#include "../sdlutils/Texture.h"
#include "../components/ClientState.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"

class HeartRender : public Component {
private:
	Texture* texture;
	ClientState* clientState;
	Transform* transform;
	int widthHeart;
	int heightHeart;
	int posStartX;
	int posStartY;
	int maxHearts;

	bool isEven(int num) const {
		return num % 2 == 0;
	}

	int numHearts(float happiness) const {
		return happiness / (2 * 10);
	}

	// aproximar los corazones
	// de modo que cuando la felicidad sea 0 aparezcan 0 corazones
	// y no cuando es [0, 1)
	int approximateHearts(float happiness) const {
		float numFloat = happiness / (2 * 10);
		if (happiness <= 0) {
			return 0;
		}
		else if (numFloat < maxHearts) {
			return numFloat + 1;
		}
		else {
			return numHearts(happiness);
		}
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_HEART_RENDER;

	HeartRender(GameObject* parent, Texture* texture, int widthHeart, int heightHeart, int offset) :
		Component(parent, id), texture(texture), widthHeart(widthHeart), heightHeart(heightHeart), posStartX(0), posStartY(0) {
		clientState = parent->getComponent<ClientState>();
		transform = parent->getComponent<Transform>();

		posStartY = -offset;
		posStartX = transform->getW() / 2;
		maxHearts = numHearts(clientState->getHappiness());
		if (isEven(maxHearts)) {
			// se resta n/2 corazones
			posStartX = posStartX - (maxHearts / 2) * widthHeart;
		}
		else {
			// se resta medio corazón
			posStartX = posStartX - widthHeart / 2;
			// se resta (n-1)/2 corazones
			posStartX = posStartX - ((maxHearts - 1) / 2) * widthHeart;
		}
	}

	void update() {
		// cuando el cliente se marcha se autodesactiva
		if (clientState->getState() == ClientState::OUT) {
			setActive(false);
		}
	}

	void render() {
		SDL_Rect dest;
		dest.w = widthHeart;
		dest.h = heightHeart;
		dest.y = posStartY + transform->getPos().getY();
		int hearts = approximateHearts(clientState->getHappiness());
		for (int i = 0; i < hearts; ++i) {
			dest.x = posStartX + i * widthHeart + transform->getPos().getX();
			texture->render(dest);
		}
	}
};