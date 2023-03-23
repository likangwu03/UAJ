#pragma once

#include "Transform.h"
#include "Image.h"
#include "../Structure/Component.h"
#include "../Definitions/Structure_def.h"
#include "../Utilities/Texture.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/InputHandler.h"
#include "../Structure/GameObject.h";

class MurderRender : public Component
{
	float offsetX;
	float offsetY;
	const int spriteWidth;
	const int spriteHeight;
	InputHandler* ih;
	int row;
	int col;
	Texture* texture;
	Transform* transform;
	Transform* parentTransform;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MURDER_RENDER;

	MurderRender(GameObject* parent);
	virtual void render();
};

