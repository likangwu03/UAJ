#pragma once
#include <cstdint>

namespace _ecs {
	using id_type = uint8_t;

	// Components
	// EL ORDEN DE EJECUCI�N DE LOS COMPONENTES ESTA DETERMINADO POR COMO SE A�ADEN
	enum _cmp_id : id_type {
		cmp_MAPCREATOR,
		cmp_MANAGER,
		cmp_MONEY,
		cmp_TRANSFORM,
		cmp_STRAIGHT_MOVEMENT,
		cmp_MOVEMENT,
		cmp_COLLISIONS,
		cmp_TRIGGER,
		cmp_DESK,
		cmp_BIN,
		cmp_THIEF_TRIGGER,
		cmp_COOKMACHINE,
		cmp_STATE,
		cmp_KITCHENISLAND,
		cmp_INGREDIENTS,
		cmp_DAILYMENU,
		cmp_BUTTON,
		cmp_INVENTORY,
		cmp_SM_INVENTORY,
		cmp_CLIENTSTATE_RENDER,
		cmp_HEART_RENDER,
		cmp_MURDER_RENDER,
		cmp_SHOO_RENDER,
		cmp_IMAGE,
		cmp_BUBBLE,
		cmp_BUTTON_COMP,
		cmp_CHARACANIM,
		cmp_UIANIM,
		cmp_WARNING,
		cmp_SHOP_MENU,
		cmp_FREEZER,
		cmp_RENDER_LIST,
		cmp_TEXT,
		cmp_BOX_TEXT,
		cmp_FINISH_DAY,
		cmp_STREAK,
		cmp_OTHERPLAYER,
		cmp_SHOWCONTROL,
		cmp_TEXT2,
		cmp_TEXTBOX,
		// Do not erase pls
		cmp_INVALID
	};
	constexpr id_type cmpNum = cmp_INVALID;
	
	// Groups
	enum _grp_id : id_type {
		grp_GENERAL,
		grp_PLAYER,
		grp_RENDERTOP,
		grp_CLIENTS,
		grp_INTERACTABLE,
		grp_ICONS,
		grp_HUD,
		grp_COLLISIONS,
		grp_THIEFS,
		grp_DESK,
		grp_OBJECTS,

		// Do not erase pls
		grp_INVALID
	};
	constexpr id_type grpNum = grp_INVALID;

	// Handlers
	enum _hdr_id : id_type {
		hdr_PLAYER,
		hdr_OTHERPLAYER,
		hdr_CLOCK,
		hdr_FREEZER,
		hdr_KITCHENISLAND,
		hdr_SHOP_MENU1,
		hdr_SM_INVENTORY,
		hdr_STREAK,
		// Do not erase pls
		hdr_INVALID
	};

	constexpr id_type hdrNum = hdr_INVALID;

	enum RenderPos { Top, Middle, Down };

	enum endingType { BadRep, Broke, Caught, Robbed, Normal, Happy };


	// Escenas
	enum _scene_id : id_type {
		sc_MAINMENU,
		sc_CONTINUEMENU,
		sc_COOPMENU,
		sc_OPTIONSMENU,
		sc_PAUSEMENU,

		sc_BEFOREDAYSTART,
		sc_DAILYMENU,
		sc_SUPERMARKET,
		sc_RESTAURANT,
		sc_PANTRY,
		sc_ENDOFDAY,
		sc_GAMEOVER,

		sc_INTRO1,
		sc_INTRO2,
		sc_INTRO3NOKILL,
		sc_ENDINGDAY1,
		sc_ENDINGDAY2KILL,
		sc_ENDINGDAY2NOKILL,
		sc_FIRSTDAYAFTERKILL,
		sc_SECONDDAYAFTERKILL,


		sc_BADENDING1,
		sc_BADENDING2,
		sc_BADENDING3,
		sc_BADENDING4,
		sc_NORMALENDING,
		sc_HAPPYENDING,

		// Do not erase pls
		sc_INVALID
	};
	constexpr id_type scNum = sc_INVALID;
}