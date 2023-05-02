#pragma once
#include "../Utilities/Vector.h"
#include "Food_def.h"
#include <SDL.h>
#include <iostream>
#include <SDL_net.h>
#include <cassert>
// Mensajes para enviar a trav�s de internet

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
		msg_ASSIGN_CLIENT,
		msg_ADD_CLINETS,
		msg_CLIENT,
		msg_THIEF_SPAWN,
		msg_THIEF_INTERACT,
		msg_CLEAN_DESK,
		msg_PICK_INGREDIENT,
		msg_RETURN_INGREDIENT,
		msg_COOKING_DISH,
		msg_PICK_DISH,
		msg_CHARGE,
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

	struct data_ingredinet
	{
		int n;
	}ingredinet;

	struct data_DAILY_MENUS {
		vector<uint8_t> menu1;
		vector<uint8_t> menu2;
	} daily_menus;

	struct data_DAILY_MENU {
		uint8_t menu;
	} daily_menu;

	struct data_ASSIGN_CLIENT
	{
		uint8_t table;
	}assignClients;
	struct data_Grp_CLIENTS {
		uint8_t num;
		vector<uint8_t> clients;
	}grp_clients;
	struct data_CLIENT
	{
		uint8_t state;
		uint8_t dish;
		uint8_t desk;
		uint8_t nClinet;
	}client;

	struct data_thief_spawn {
		uint8_t number;
		std::vector<uint8_t> skins, positions; // Skin IDs & positions
	}thief_spawn;

	struct data_desk {
		uint8_t id;
	}desk;
	struct data_cooking_machine {
		uint8_t dish;
		uint8_t id;
	}cooking_machine;
	struct data_charge {
		uint8_t rep;
		uint8_t money;
		uint8_t tip;
	}charge;

	Message(_msg_id id = msg_INVALID) : id(id) { }
	~Message() { }
	
#pragma region code_decode
	/// <summary>
   /// Para int: desde el -128 hasta el 127 /
   /// Para uint: desde el 0 hasta el 255 /
   /// Para char: todos los car�cteres /
   /// Para float: indefinido
   /// </summary>
	template<typename T>
	Uint8* code8(T input, Uint8* msg) const {
		*reinterpret_cast<Uint8*>(msg) = input;
		return msg + sizeof(Uint8);
	}
	template<typename T>
	Uint8* decode8(T& v, Uint8* msg) const {
		v =msg[0];
		return msg + sizeof(Uint8);
	}

	Uint8* code8(int input, Uint8* msg) const { return code8<int8_t>(input, msg); }
	Uint8* decode8(int& v, Uint8* msg) const {
		int8_t output = v;
		msg = decode8<int8_t>(output, msg);
		v = output;
		return msg;
	}

	/// <summary>
	/// Para int: desde el -32768 hasta el 32767 /
	/// Para uint: desde el 0 hasta el 65535 /
	/// Para float: desde el -3276.8 hasta el 3276.7
	/// </summary>
	template<typename T>
	Uint8* code16(T input, Uint8* msg) const {
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
	Uint8* decode16(T& v, Uint8* msg) const {
		Uint16 output{}; std::pair<char, char> input;
		input.first = msg[0]; input.second = msg[1];
		for (uint8_t i = 0; i < 8; i++, input.first >>= 1) {
			output = (output << 1) + (input.first & 1);
		}
		for (uint8_t i = 0; i < 8; i++, input.second >>= 1) {
			output = (output << 1) + (input.second & 1);
		}
		v = output;
		return msg+sizeof(Uint16);
	};
	Uint8* code16(int input, Uint8* msg) const { return code16<int16_t>(input, msg); };
	Uint8* decode16(int& v, Uint8* msg) const {
		int16_t aux;
		msg = decode16(aux, msg);
		v = aux;
		return msg;
	};
	Uint8* code16(float input, Uint8* msg) const { return code16<int16_t>(roundf(input * 10), msg); };
	Uint8* decode16(float& v, Uint8* msg) const {
		int16_t aux;
		msg = decode16(aux, msg);
		v = aux / 10.0f;
		return msg;
	};



	template<typename T>
	Uint8* code8vector(std::vector<T> input, Uint8* msg) const {
		for(T item : input) msg = code8(item, msg);
		return msg;
	}
	template<typename T>
	Uint8* decode8vector(std::vector<T>& v, Uint8* msg, uint16_t length) const {
		T item;
		for(uint16_t i = 0; i < length; i++) {
			msg = decode8(item, msg);
			v.push_back(item);
		}
		return msg;
	}
	template<typename T>
	Uint8* code16vector(std::vector<T> input, Uint8* msg) const {
		for(T item : input) msg = code16(item, msg);
		return msg;
	}
	template<typename T>
	Uint8* decode16vector(std::vector<T>& v, Uint8* msg, uint16_t length) const {
		T item;
		for(uint16_t i = 0; i < length; i++) {
			msg = decode16(item, msg);
			v.push_back(item);
		}
		return msg;
	};
#pragma endregion

public:
	Uint8* code(Uint8* msg) const {
		msg = code8(id, msg);
		switch (id) {
		case msg_PLAYER:
			msg=code16(player.pos.getX(),msg);
			msg=code16(player.pos.getY(),msg);
			if (player.vel.getX() < 0) {
				int algo=1234;
			}
			msg=code16(player.vel.getX(),msg);
			msg=code16(player.vel.getY(),msg);
			msg=code8(player.scene,msg);
			break;
		case msg_BASKET:
			msg=code8(basket.ing,msg);
			msg=code8(basket.n,msg);
			break;
		case msg_TO_DAILY_MENU:
			for (uint8_t d : daily_menus.menu1) {
				msg=code8(d,msg);
			}
			for (uint8_t d : daily_menus.menu2) {
				msg=code8(d,msg);
			}
			break;
		case msg_TO_SUPERMARKET:
			msg = code8(daily_menu.menu, msg);
			break;
		case msg_ADD_CLINETS:
			uint8_t aux3;
			msg = code8(grp_clients.num, msg);
			for (uint8_t c : grp_clients.clients) {
				msg = code8(c, msg);
			}		
			break;
		case msg_ASSIGN_CLIENT:
			msg = code8(assignClients.table, msg);
			break;
		case msg_THIEF_SPAWN:
			msg = code8(thief_spawn.number, msg);
			msg = code8vector(thief_spawn.skins, msg);
			msg = code8vector(thief_spawn.positions, msg);
			break;

		case msg_CLIENT:
			msg = code8(client.state, msg);
			msg = code8(client.nClinet, msg);
			msg = code8(client.desk, msg);
			msg = code8(client.dish, msg);
			break;
		case msg_CLEAN_DESK:
			msg = code8(desk.id, msg);
			break;
		case msg_PICK_INGREDIENT:
		case msg_RETURN_INGREDIENT:
			msg = code8(ingredinet.n, msg);
			break;
		case msg_COOKING_DISH:
		case msg_PICK_DISH:
			msg = code8(cooking_machine.id, msg);
			msg = code8(cooking_machine.dish, msg);
			break;
		case msg_CHARGE:
			msg = code8(charge.money, msg);
			msg = code8(charge.rep, msg);
			msg = code8(charge.tip, msg);
			break;

		}
	
		return msg;
	}

	Uint8* decode(Uint8* msg) {
		Uint8 id_;
		msg = decode8< uint8_t>(id_, msg);
		id = (_msg_id)id_;
		switch (id) {
		case msg_PLAYER:
			float aux;
			msg = decode16(aux, msg);
			player.pos.setX(aux);
			msg = decode16(aux, msg);
			player.pos.setY(aux);
			msg = decode16(aux, msg);
			player.vel.setX(aux);
			msg = decode16(aux, msg);
			player.vel.setY(aux);
			msg = decode8< uint8_t>(player.scene, msg);
			break;
		case msg_BASKET:
			uint8_t aux2;
			msg = decode8<uint8_t>(aux2, msg);
			basket.ing =(_ecs::_ingredients_id) aux2;
			msg = decode8<uint8_t>(aux2, msg);
			basket.n = aux2;
			
		case msg_TO_DAILY_MENU:
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
		case msg_TO_SUPERMARKET:
			msg= decode8<uint8_t>(daily_menu.menu, msg);
			break;
		case Message::msg_ADD_CLINETS:
			uint8_t aux3;
			msg = decode8<uint8_t>(grp_clients.num, msg);
			for (int i = 0; i < grp_clients.num; i++) {
				msg = decode8<uint8_t>(aux3, msg);
				grp_clients.clients.push_back(aux3);
			}
			break;
		case Message::msg_ASSIGN_CLIENT:
			msg=decode8<uint8_t>(assignClients.table, msg);
			break;
		case msg_THIEF_SPAWN:
			msg = decode8(thief_spawn.number, msg);
			msg = decode8vector(thief_spawn.skins, msg, thief_spawn.number);
			msg = decode8vector(thief_spawn.positions, msg, thief_spawn.number);
			break;
		case msg_CLIENT:
			msg = decode8(client.state, msg);
			msg = decode8(client.nClinet, msg);
			msg = decode8(client.desk, msg);
			msg = decode8(client.dish, msg);
			break;
		case msg_CLEAN_DESK:
			msg = decode8(desk.id, msg);
			break;
		case msg_PICK_INGREDIENT:
		case msg_RETURN_INGREDIENT:
			msg = decode8(ingredinet.n, msg);
			break;
		case msg_COOKING_DISH:
		case msg_PICK_DISH:
			msg = decode8(cooking_machine.id, msg);
			msg = decode8(cooking_machine.dish, msg);
			break;
		case msg_CHARGE:
			msg = decode8(charge.money, msg);
			msg = decode8(charge.rep, msg);
			msg = decode8(charge.tip, msg);
			break;

		}
		return msg;
	}



};