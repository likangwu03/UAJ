#pragma once
#include "../Utilities/Vector.h"
#include "Food_def.h"
#include <SDL.h>
#include <iostream>
#include <SDL_net.h>
#include <cassert>
// Mensajes para enviar a través de internet

struct Message {
	typedef char byte;
	typedef uint8_t id_type;
	struct doubleByte { byte first, second; };

	enum _msg_id : uint8_t {
		msg_PLAYER,
		msg_BASKET,
		msg_TO_DAILY_MENU,
		msg_TO_SUPERMARKET,
		msg_TO_RESTAURANT,

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



#pragma region code_decode


	/// <summary>
   /// Para int: desde el -128 hasta el 127 /
   /// Para uint: desde el 0 hasta el 255 /
   /// Para char: todos los carácteres /
   /// Para float: indefinido
   /// </summary>
	template<typename T>
	Uint8* code8(T input, Uint8* msg) {
		*reinterpret_cast<Uint8*>(msg) = input;
		return msg + sizeof(Uint8);
	}
	template<typename T>
	Uint8* decode8(Uint8& v, Uint8* msg) {
		v =msg[0];
		return msg + sizeof(Uint8);
	}

	Uint8* code8(int input, Uint8* msg) { return code8<int8_t>(input, msg); }

	/// <summary>
	/// Para int: desde el -32768 hasta el 32767 /
	/// Para uint: desde el 0 hasta el 65535 /
	/// Para float: desde el -3276.8 hasta el 3276.7
	/// </summary>
	template<typename T>
	Uint8* code16(T input, Uint8* msg) {
		doubleByte output{};
		output.first = output.second = 0;
		for (uint8_t i = 0; i < 8; i++, input >>= 1) {
			output.second = (output.second << 1) + (input & 1);
		}
		for (uint8_t i = 0; i < 8; i++, input >>= 1) {
			output.first = (output.first << 1) + (input & 1);
		}
		msg = code8(output.first, msg);
		msg = code8(output.second, msg);
		return msg;
	}
	template<typename T>
	Uint8* decode16(T& v, Uint8* msg) {
		Uint8 input[2];
		msg = decode8<int8_t>(input[0], msg);
		msg = decode8<int8_t>(input[1], msg);

		v = *reinterpret_cast<Uint16*>(input);
		/*for (uint8_t i = 0; i < 8; i++, input.first >>= 1) {
			v = (v << 1) + (input.first & 1);
		}
		for (uint8_t i = 0; i < 8; i++, input.second >>= 1) {
			v = (v << 1) + (input.second & 1);
		}*/
		return msg;
	};
	Uint8* code16(int input, Uint8* msg) { return code16<int16_t>(input, msg); };
	Uint8* decode16(int& v, Uint8* msg) {
		uint16_t aux;
		msg = decode16(aux, msg);
		v = aux;
		return msg;
	};
	Uint8* code16(float input, Uint8* msg) { return code16<int16_t>(roundf(input * 10), msg); };
	Uint8* decode16(float& v, Uint8* msg) {
		uint16_t aux;
		msg = decode16(aux, msg);
		v = aux / 10.0f;
		return msg;
	};
#pragma endregion



public:
	Uint8* code(Uint8* msg) {
		msg = code8(id, msg);
		switch (id) {
		case Message::msg_PLAYER:
			msg=code16(player.pos.getX(),msg);
			msg=code16(player.pos.getY(),msg);
			msg=code16(player.vel.getX(),msg);
			msg=code16(player.vel.getY(),msg);
			msg=code8(player.scene,msg);
			break;
		case Message::msg_BASKET:
			msg=code8(basket.ing,msg);
			msg=code8(basket.n,msg);
			break;
		case Message::msg_TO_DAILY_MENU:
			for (uint8_t d : daily_menus.menu1) {
				msg=code8(d,msg);
			}
			for (uint8_t d : daily_menus.menu2) {
				msg=code8(d,msg);
			}
			break;
		case Message::msg_TO_SUPERMARKET:
			msg = code8(daily_menu.menu, msg);
			break;
		}
	
		return msg;
	}

	// Recoge la información del buffer y ejecuta las acciones pertinentes
	Uint8* decode(Uint8* msg) {
		Uint8 id_;
		msg = decode8< uint8_t>(id_, msg);
		id = (_msg_id)id_;
		switch (id) {
		case Message::msg_PLAYER:
			float aux;
			msg = decode16<float>(aux, msg);
			player.pos.setX(aux);
			msg = decode16<float>(aux, msg);
			player.pos.setY(aux);
			msg = decode16<float>(aux, msg);
			player.vel.setX(aux);
			msg = decode16<float>(aux, msg);
			player.vel.setY(aux);
			msg = decode8< uint8_t>(player.scene, msg);
			break;
		case Message::msg_BASKET:
			uint8_t aux2;
			msg = decode8<uint8_t>(aux2, msg);
			basket.ing =(_ecs::_ingredients_id) aux2;
			msg = decode8<uint8_t>(aux2, msg);
			basket.n = aux2;
			
		case Message::msg_TO_DAILY_MENU:
			for (int i = 0; i < 4; ++i) {
				uint8_t aux;
				msg = decode8<uint8_t>(aux, msg);
				daily_menus.menu1.push_back((_ecs::_ingredients_id)aux);
			}
			for (int i = 0; i < 4; ++i) {
				uint8_t aux;
				msg = decode8<uint8_t>(aux, msg);
				daily_menus.menu2.push_back((_ecs::_ingredients_id)aux);
			}
			break;
		case Message::msg_TO_SUPERMARKET:
			msg= decode8<uint8_t>(daily_menu.menu, msg);
			break;
		}
		return msg;
	}



};