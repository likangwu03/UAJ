#pragma once
#include "../Utilities/Vector.h"
#include "Food_def.h"

// Mensajes para enviar a través de internet

struct Message {
	enum _msg_id : unsigned char {
		msg_PLAYER,
		msg_BASKET,

		// Do not erase pls
		msg_INVALID
	};

	_msg_id id;
	

	struct data_player {
		Vector pos, vel;
	} player;

	struct data_basket {
		_ecs::_ingredients_id ing;
		int n;
	} basket;
};