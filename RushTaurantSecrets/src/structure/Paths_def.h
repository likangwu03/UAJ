#pragma once
#include <cstdint>
#include <unordered_map>
#include "../utilities/Vector.h"
#include "../components/Transform.h"
#include <string>


namespace _ecs {
	using namespace std;
	using id_type = uint8_t;

	// LADRONES
	const Vector DOOR = Vector(32, 18);
	const Vector SECRET = Vector(20, 18);
	const Vector FREEZER = Vector(24, 18);


	// CLIENTES
	const int NUM_TABLES = 7;
	const int NUM_CLIENTS_PATHS = 3;
	const int NUM_SEATS = 4;

	enum _path_client_id : id_type {
		// mesa 1
		ARRIVE_TABLE_1_LEFT,
		PAY_TABLE_1_LEFT,
		OUT_TABLE_1_LEFT,
		ARRIVE_TABLE_1_RIGHT,
		PAY_TABLE_1_RIGHT,
		OUT_TABLE_1_RIGHT,
		ARRIVE_TABLE_1_DOWN,
		PAY_TABLE_1_DOWN,
		OUT_TABLE_1_DOWN,
		ARRIVE_TABLE_1_UP,
		PAY_TABLE_1_UP,
		OUT_TABLE_1_UP,
		// mesa 2
		ARRIVE_TABLE_2_LEFT,
		PAY_TABLE_2_LEFT,
		OUT_TABLE_2_LEFT,
		ARRIVE_TABLE_2_RIGHT,
		PAY_TABLE_2_RIGHT,
		OUT_TABLE_2_RIGHT,
		ARRIVE_TABLE_2_DOWN,
		PAY_TABLE_2_DOWN,
		OUT_TABLE_2_DOWN,
		ARRIVE_TABLE_2_UP,
		PAY_TABLE_2_UP,
		OUT_TABLE_2_UP,
		// mesa 3
		ARRIVE_TABLE_3,
		PAY_TABLE_3,
		OUT_TABLE_3,
		ARRIVE_TABLE_4,
		PAY_TABLE_4,
		OUT_TABLE_4,
		ARRIVE_TABLE_5,
		PAY_TABLE_5,
		OUT_TABLE_5,
		ARRIVE_TABLE_6,
		PAY_TABLE_6,
		OUT_TABLE_6,
		ARRIVE_TABLE_7,
		PAY_TABLE_7,
		OUT_TABLE_7,
		PAY_AND_LEAVE
	};

	static _path_client_id enumClientPaths[NUM_TABLES][NUM_SEATS][NUM_CLIENTS_PATHS]{
		// mesa 1 izquierda
		_path_client_id::ARRIVE_TABLE_1_LEFT,
		_path_client_id::PAY_TABLE_1_LEFT,
		_path_client_id::OUT_TABLE_1_LEFT,
		// mesa 1 derecha
		_path_client_id::ARRIVE_TABLE_1_RIGHT,
		_path_client_id::PAY_TABLE_1_RIGHT,
		_path_client_id::OUT_TABLE_1_RIGHT,
		// mesa 1 arriba
		_path_client_id::ARRIVE_TABLE_1_UP,
		_path_client_id::PAY_TABLE_1_UP,
		_path_client_id::OUT_TABLE_1_UP,
		// mesa 1 abajo
		_path_client_id::ARRIVE_TABLE_1_DOWN,
		_path_client_id::PAY_TABLE_1_DOWN,
		_path_client_id::OUT_TABLE_1_DOWN,

		// mesa 2 izquierda
		_path_client_id::ARRIVE_TABLE_2_LEFT,
		_path_client_id::PAY_TABLE_2_LEFT,
		_path_client_id::OUT_TABLE_2_LEFT,
		// mesa 2 derecha
		_path_client_id::ARRIVE_TABLE_2_RIGHT,
		_path_client_id::PAY_TABLE_2_RIGHT,
		_path_client_id::OUT_TABLE_2_RIGHT,
		// mesa 2 arriba
		_path_client_id::ARRIVE_TABLE_2_UP,
		_path_client_id::PAY_TABLE_2_UP,
		_path_client_id::OUT_TABLE_2_UP,
		// mesa 2 abajo
		_path_client_id::ARRIVE_TABLE_2_DOWN,
		_path_client_id::PAY_TABLE_2_DOWN,
		_path_client_id::OUT_TABLE_2_DOWN
	};

	static unordered_map<string, _path_client_id> stringToEnum = {
		// mesa 1 izquierda
		{"ARRIVE_TABLE_1_LEFT", _path_client_id::ARRIVE_TABLE_1_LEFT},
		{"PAY_TABLE_1_LEFT", _path_client_id::PAY_TABLE_1_LEFT},
		{"OUT_TABLE_1_LEFT", _path_client_id::OUT_TABLE_1_LEFT},
		// mesa 1 derecha
		{"ARRIVE_TABLE_1_RIGHT", _path_client_id::ARRIVE_TABLE_1_RIGHT},
		{"PAY_TABLE_1_RIGHT", _path_client_id::PAY_TABLE_1_RIGHT},
		{"OUT_TABLE_1_RIGHT", _path_client_id::OUT_TABLE_1_RIGHT},
		// mesa 1 abajo
		{"ARRIVE_TABLE_1_DOWN", _path_client_id::ARRIVE_TABLE_1_DOWN},
		{"PAY_TABLE_1_DOWN", _path_client_id::PAY_TABLE_1_DOWN},
		{"OUT_TABLE_1_DOWN", _path_client_id::OUT_TABLE_1_DOWN},
		// mesa 1 arriba
		{"ARRIVE_TABLE_1_UP", _path_client_id::ARRIVE_TABLE_1_UP},
		{"PAY_TABLE_1_UP", _path_client_id::PAY_TABLE_1_UP},
		{"OUT_TABLE_1_UP", _path_client_id::OUT_TABLE_1_UP},
		// mesa 2 izquierda
		{"ARRIVE_TABLE_2_LEFT",_path_client_id::ARRIVE_TABLE_2_LEFT},
		{"PAY_TABLE_2_LEFT",_path_client_id::PAY_TABLE_2_LEFT},
		{"OUT_TABLE_2_LEFT",_path_client_id::OUT_TABLE_2_LEFT},
		// mesa 2 derecha
		{"ARRIVE_TABLE_2_RIGHT",_path_client_id::ARRIVE_TABLE_2_RIGHT},
		{"PAY_TABLE_2_RIGHT",_path_client_id::PAY_TABLE_2_RIGHT},
		{"OUT_TABLE_2_RIGHT",_path_client_id::OUT_TABLE_2_RIGHT},
		// mesa 2 abajo
		{"ARRIVE_TABLE_2_DOWN",_path_client_id::ARRIVE_TABLE_2_DOWN},
		{"PAY_TABLE_2_DOWN",_path_client_id::PAY_TABLE_2_DOWN},
		{"OUT_TABLE_2_DOWN",_path_client_id::OUT_TABLE_2_DOWN},
		// mesa 2 arriba
		{"ARRIVE_TABLE_2_UP",_path_client_id::ARRIVE_TABLE_2_UP},
		{"PAY_TABLE_2_UP",_path_client_id::PAY_TABLE_2_UP},
		{"OUT_TABLE_2_UP",_path_client_id::OUT_TABLE_2_UP},
		// mesa 3
		{"ARRIVE_TABLE_3",_path_client_id::ARRIVE_TABLE_3},
		{"PAY_TABLE_3", _path_client_id::PAY_TABLE_3},
		{"OUT_TABLE_3", _path_client_id::OUT_TABLE_3},
		// mesa 4
		{"ARRIVE_TABLE_4", _path_client_id::ARRIVE_TABLE_4},
		{"PAY_TABLE_4",_path_client_id::PAY_TABLE_4},
		{"OUT_TABLE_4",_path_client_id::OUT_TABLE_4},
		// mesa 5
		{"ARRIVE_TABLE_5",_path_client_id::ARRIVE_TABLE_5},
		{"PAY_TABLE_5", _path_client_id::PAY_TABLE_5},
		{"OUT_TABLE_5", _path_client_id::OUT_TABLE_5},
		// mesa 6
		{"ARRIVE_TABLE_6",_path_client_id::ARRIVE_TABLE_6},
		{"PAY_TABLE_6", _path_client_id::PAY_TABLE_6},
		{"OUT_TABLE_6", _path_client_id::OUT_TABLE_6},
		// mesa 7
		{"ARRIVE_TABLE_7",_path_client_id::ARRIVE_TABLE_7},
		{"PAY_TABLE_7", _path_client_id::PAY_TABLE_7},
		{"OUT_TABLE_7", _path_client_id::OUT_TABLE_7},
	};

	struct Route {
		vector<Vector> points;
		GOOrientation orientation = none;
	};

	// afuera entrada
	const Vector OUT_ENTRY = Vector(40, 16);
	// entrada
	const Vector ENTRY = Vector(27, 16);
	// pos caja registradora
	const Vector CASH_REGISTER = Vector(26, 10);
	// salida
	const Vector PAY = Vector(28, 13);
	// afuera salida
	const Vector OUT_PAY = Vector(40, 13);

	static Route clientsPaths[NUM_TABLES * NUM_SEATS * NUM_CLIENTS_PATHS + 1] = {
		// EL PRIMER VECTOR DE MESA TIENE QUE EMPEZAR POR x = 27
		// SINO HAY QUE PONER ENTRY
		// mesa 1 silla izquierda
		{{Vector(27, 18), Vector(20, 18), Vector(20, 15)}, east},	// mesa
		{{Vector(20, 10), CASH_REGISTER}},	// pagar
		{{Vector(20, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 1 silla derecha
		{{ENTRY, Vector(24, 16), Vector(24, 15)}, west },	// mesa
		{{Vector(24, 10), CASH_REGISTER}},	// pagar
		{{Vector(24, 13), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 1 silla abajo
		{{Vector(27, 17), Vector(22, 17)}, north },	// mesa
		{{Vector(19, 17), Vector(19, 10), CASH_REGISTER}},	// pagar
		{{Vector(28, 17), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 1 silla arriba
		{{Vector(27, 13), Vector(22, 13)}, south },	// mesa
		{{Vector(22, 10), CASH_REGISTER}},	// pagar
		{{PAY, OUT_PAY}},	// marcharse mesa

		// mesa 2 silla izquierda
		{{Vector(27, 12), Vector(13, 12), Vector(13, 15)}, east },	// mesa
		{{Vector(13, 12), Vector(17, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(13, 12), Vector(17, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 2 silla derecha
		{{Vector(27, 12), Vector(17, 12), Vector(17, 15)}, west },	// mesa
		{{Vector(17, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(17, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 2 silla abajo
		{{Vector(27, 18), Vector(15, 18), Vector(15, 17)}, north },	// mesa
		{{Vector(19, 17), Vector(19, 10), CASH_REGISTER}},	// pagar
		{{Vector(19, 17), Vector(19, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 2 silla arriba
		{{Vector(27, 12), Vector(15, 12), Vector(15, 13)}, south },	// mesa
		{{Vector(15, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(15, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa

		// mesa 3 silla derecha
		{{Vector(27, 12), Vector(10, 12), Vector(10, 15)}, west },	// mesa
		{{Vector(10, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(10, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 4 silla derecha
		{{Vector(27, 11), Vector(19, 11), Vector(19, 9)}, west},	// mesa
		{{Vector(19, 10), CASH_REGISTER}},	// pagar
		{{Vector(19, 11), Vector(28, 11), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 5 silla derecha
		{{Vector(27, 12), Vector(12, 12), Vector(12, 9)}, west },	// mesa
		{{Vector(12, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(12, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 6 silla derecha
		{{Vector(27, 11), Vector(20, 11), Vector(20, 6), Vector(16, 6), Vector(16, 5)}, west},	// mesa
		{{Vector(16, 6), Vector(20, 6), Vector(20, 10), CASH_REGISTER}},	// pagar
		{{Vector(16, 6), Vector(20, 6), Vector(20, 11), Vector(28, 11), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 7 silla izquierda
		{{Vector(27, 12), Vector(5, 12), Vector(5, 5)}, east },	// mesa
		{{Vector(5, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(5, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// marcharse después de haber pagado la comida
		{{Vector(26, 13), OUT_PAY}}
	};
};