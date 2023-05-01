#pragma once

#include "../Structure/Component.h"
#include "../Utilities/Texture.h"
#include "ClientState.h"
#include "../Structure/GameObject.h"
#include "Transform.h"
#include "../Utilities/checkML.h"

class HeartRender : public Component {
private:
	ClientState* clientState;
	Transform* transform;
	int widthHeart;
	int heightHeart;
	Texture* texture;
	int progressHeart;
	float offsetY;
	// cada cuantas unidades de vida cambia el frame de las vidas
	float change;
	float currentHappiness;
	float elapsedTime;
	float disappearTimer;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_HEART_RENDER;

	HeartRender(GameObject* parent, Texture* texture, int widthHeart, int heightHeart, int offsetY);

	virtual void update();

	virtual void render();
};