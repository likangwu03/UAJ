#pragma once

#include "Transform.h"
#include "Image.h"
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../structure/GameObject.h";

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

