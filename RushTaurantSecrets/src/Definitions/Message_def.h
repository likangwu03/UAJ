#pragma once

// Mensajes para enviar a través de internet

struct Message {
	enum _msg_id : unsigned char {
		msg_PLAYER,

		// Do not erase pls
		msg_INVALID
	};

	_msg_id id;

	struct {
		float x, y, vX, vY;
	} data_player;
};