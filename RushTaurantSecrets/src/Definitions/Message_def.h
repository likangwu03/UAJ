#pragma once
#include "../Utilities/Vector.h"

// Mensajes para enviar a través de internet

struct Message {
	enum _msg_id : unsigned char {
		msg_PLAYER,

		// Do not erase pls
		msg_INVALID
	};

	_msg_id id;

	struct {
		Vector pos, vel;
	} data_player;
};