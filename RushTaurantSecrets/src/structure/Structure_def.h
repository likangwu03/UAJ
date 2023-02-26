#pragma once
#include <cstdint>

namespace _ecs {
	using id_type = uint8_t;

	// Components
	// EL ORDEN DE LOS ENUMERADOS DETERMINA EL ORDEN DE LOS COMPONENTES
	// IMPORTA EL ORDEN DE LOS COMPONENTES
	enum _cmp_id : id_type {
		// mapa
		cmp_MAPCREATOR,
		cmp_MAPRENDER,
		// managers
		cmp_CLIENTS_MANAGER,
		cmp_THIEFS_MANAGER,
		cmp_MONEY,
		// movimiento / update
		cmp_TRANSFORM,
		cmp_STRAIGHT_MOVEMENT,
		cmp_MOVEMENT,
		// colisiones / triggers
		cmp_COLLISIONS,
		cmp_TRIGGER,
		cmp_DESK,
		cmp_BIN,
		// otros
		cmp_COOKMACHINE,
		cmp_CLIENTSTATE,
		cmp_KITCHENISLAND,
		cmp_INGREDIENTS,
		cmp_DAILYMENU,
		// HUD
		cmp_BUTTON,
		cmp_INVENTORY,
		// renders
		cmp_CLIENTSTATE_RENDER,
		cmp_HEART_RENDER,
		cmp_IMAGE,
		cmp_BUBBLE,
		// botones
		cmp_BUTTON_COMP,
		// animaciones
		cmp_CHARACANIM,
		cmp_UIANIM,

		// Do not erase pls
		cmp_INVALID
	};
	constexpr id_type cmpNum = cmp_INVALID;
	
	// Groups
	enum _grp_id : id_type {
		grp_GENERAL,
		grp_PLAYER,
		grp_CLIENTS,
		grp_RENDERTOP,
		grp_INTERACTABLE,
		grp_HUD,
		grp_ICONS,
		grp_COLLISIONS,
		grp_THIEFS,


		// Do not erase pls
		grp_INVALID
	};
	constexpr id_type grpNum = grp_INVALID;

	// Handlers
	enum _hdr_id : id_type {
		hdr_PLAYER,
		hdr_DISHCOMB,
		hdr_CLIENT,
		hdr_INVENTORY,
		hdr_MONEY_ICON,
		hdr_REPUTATION,
		hdr_TARGET,
		hdr_MONEY,
		hdr_MONEY_TEXT,
		hdr_TIME_TEXT,
		hdr_CLOCK,
		hdr_STAR,
		hdr_EMPTY_STAR,
		hdr_MENU,
		hdr_PAUSE,
		hdr_BASKET,
		hdr_BIN,
		hdr_PRUEBA,
		hdr_KITCHENISLAND,
		
		// Do not erase pls
		hdr_INVALID
	};
	constexpr id_type hdrNum = hdr_INVALID;
}