#pragma once

#include "../Structure/Component.h"
#include "../Utilities/Texture.h"
#include "ClientState.h"
#include "../Structure/GameObject.h"
#include "Transform.h"

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

	inline bool isPar(int num) const {
		return num % 2 == 0;
	}

	inline int numHearts(float happiness) const {
		return happiness / (2 * 10);
	}

	// aproximar los corazones
	// de modo que cuando la felicidad sea 0 aparezcan 0 corazones
	// y no cuando es [0, 1)
	int approximateHearts(float happiness) const;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_HEART_RENDER;

	HeartRender(GameObject* parent, Texture* texture, int widthHeart, int heightHeart, int offsetY, int offsetX);

	virtual void update();

	virtual void render();
};