#pragma once

#include "Transform.h"
#include "Image.h"
#include "../sdlutils/InputHandler.h"
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h";

class ShooRender : public Component
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
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SHOO_RENDER;
	ShooRender(GameObject* parent);
	virtual void render();

};

