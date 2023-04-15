#pragma once

#include "../Structure/Component.h"
#include "Image.h"
#include "../Utilities/Vector.h"
#include "../Utilities/SDLUtils.h"
#include "../Structure/GameManager.h"

class FreezerComp :public Component {
public:

	constexpr static _ecs::_cmp_id id = _ecs::cmp_FREEZER;

private:
	struct FreezerTex {
		Texture* open1 = nullptr;
		Texture* close2 = nullptr;
		Texture* open2 = nullptr;
	};

	Image* image; 
	FreezerTex textures;
	GameManager* gameInfo;

	void isClosedWhenKilled();
	void isOpenWhenKilled();
public:
	FreezerComp(GameObject* parent);
	void isOpen();
	void nextDay() override;
};

