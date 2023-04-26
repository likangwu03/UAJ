#pragma once
#include "../Utilities/Vector.h"
#include "Food_def.h"

// Mensajes para enviar a través de internet

struct Message {
	enum _msg_id : uint8_t {
		msg_PLAYER,
		msg_BASKET,

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
};