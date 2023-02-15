#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"

// UI del supermercado
class UIMarket : public Scene
{
private:
	SDLUtils* sdl = SDLUtils::instance();

public:
	// constructora
	UIMarket();
};

