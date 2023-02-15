#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"

// UI del supermercado
class UIMarket : public Scene
{
private:
	SDLUtils* sdl;

public:
	// constructora
	UIMarket() : Scene() {
		sdl = SDLUtils::instance();
		// construcción de entidades de la clase y sus componentes
		// icono de dinero
		GameObject* moneyIcon = new GameObject(this, _ecs::hdr_MONEY_ICON, _ecs::grp_ICONS);

		// icono de cesta

		// icono de pausa

		// icono de menú

		// texto de dinero
	}
};

