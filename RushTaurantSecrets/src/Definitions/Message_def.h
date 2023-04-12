#pragma once

// ESTOS INCLUDE ESTÁN PARA EL EJEMPLO
#include "Structure_def.h"
#include <cstdint>

// Mensajes para enviar a través de internet

struct Message {
	enum _msg_id : unsigned char {
		msg_PLACEHOLDER,

		// Do not erase pls
		msg_INVALID
	};

	_msg_id id;

	struct {
		uint8_t dataUint;
		char dataChar;
		int dataInt;
		_ecs::_cmp_id dataCmpId;
		float dataFloat;
	} data_placeholder;
};