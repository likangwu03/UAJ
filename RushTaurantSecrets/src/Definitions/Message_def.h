#pragma once
#include "../Utilities/Vector.h"
#include "Food_def.h"

// Mensajes para enviar a través de internet

struct Message {
	enum _msg_id : uint8_t {
		msg_PLAYER,
		msg_BASKET,
		msg_TO_DAILY_MENU,
		msg_TO_SUPERMARKET,

		// Do not erase pls
		msg_INVALID
	};
	_msg_id id;
	

	struct data_player {
		Vector pos, vel;
		uint8_t scene; // 0 - Restaurant, 1 - Pantry, 2 - Supermarket
	} player;

	struct data_basket {
		_ecs::_ingredients_id ing;
		int n;
	} basket;

	struct data_DAILY_MENUS {
		vector<uint8_t> menu1;
		vector<uint8_t> menu2;
	} daily_menus;

	struct data_DAILY_MENU {
		uint8_t menu; 
	} daily_menu;

};