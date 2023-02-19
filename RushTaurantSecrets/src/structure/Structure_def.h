#pragma once
#include <cstdint>

namespace _ecs {
	using id_type = uint8_t;

	// Components
	enum _cmp_id : id_type {
		cmp_TRANSFORM,
		cmp_IMAGE,
		cmp_MAPCREATOR,
		cmp_MAPRENDER,
		cmp_DESK,
		cmp_ANIMATOR,
		cmp_CLIENTSTATE,
		cmp_COOKMACHINE,
		cmp_DISHCOMB,
		cmp_INVENTORY,
		cmp_MOVEMENT,
		cmp_INGREDIENTS,
		cmp_COLLISIONS,
		cmp_TRIGGER,
		cmp_BIN,
		cmp_STRAIGHT_MOVEMENT,
		


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


		// Do not erase pls
		grp_INVALID
	};
	constexpr id_type grpNum = grp_INVALID;

	// Handlers
	enum _hdr_id : id_type {
		hdr_PLAYER,
		hdr_DISHCOMB,
		hdr_CUSTOMER,
		hdr_INVENTORY,
		hdr_MONEY_ICON,
		hdr_REPUTATION,
		hdr_TARGET,
		hdr_MONEY,
		hdr_MONEY_TEXT,
		hdr_MENU,
		hdr_PAUSE,
		hdr_BASKET,
		hdr_BIN,
		hdr_PRUEBA,
		
		// Do not erase pls
		hdr_INVALID
	};
	constexpr id_type hdrNum = hdr_INVALID;
}