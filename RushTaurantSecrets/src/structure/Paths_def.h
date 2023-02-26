#pragma once
#include <cstdint>
#include <vector>
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
	const id_type NUM_TABLES = 7;

	enum _path_client_id : id_type {
		ARRIVE_TABLE_1,
		PAY_TABLE_1,
		OUT_TABLE_1,
		ARRIVE_TABLE_2,
		PAY_TABLE_2,
		OUT_TABLE_2,
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

	static unordered_map<string, _path_client_id> stringToEnum = {
		{"ARRIVE_TABLE_1",_path_client_id::ARRIVE_TABLE_1},
		{"PAY_TABLE_1", _path_client_id::PAY_TABLE_1},
		{"OUT_TABLE_1", _path_client_id::OUT_TABLE_1},
		{"ARRIVE_TABLE_2",_path_client_id::ARRIVE_TABLE_2},
		{"PAY_TABLE_2",_path_client_id::PAY_TABLE_2},
		{"OUT_TABLE_2",_path_client_id::OUT_TABLE_2},
		{"ARRIVE_TABLE_3",_path_client_id::ARRIVE_TABLE_3},
		{"PAY_TABLE_3", _path_client_id::PAY_TABLE_3},
		{"OUT_TABLE_3", _path_client_id::OUT_TABLE_3},
		{"ARRIVE_TABLE_4", _path_client_id::ARRIVE_TABLE_4},
		{"PAY_TABLE_4",_path_client_id::PAY_TABLE_4},
		{"OUT_TABLE_4",_path_client_id::OUT_TABLE_4},
		{"ARRIVE_TABLE_5",_path_client_id::ARRIVE_TABLE_5},
		{"PAY_TABLE_5", _path_client_id::PAY_TABLE_5},
		{"OUT_TABLE_5", _path_client_id::OUT_TABLE_5},
		{"ARRIVE_TABLE_6",_path_client_id::ARRIVE_TABLE_6},
		{"PAY_TABLE_6", _path_client_id::PAY_TABLE_6},
		{"OUT_TABLE_6", _path_client_id::OUT_TABLE_6},
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

	static Route paths[NUM_TABLES * 3 + 1] = {
		// mesa 1 silla abajo
		{{Vector(27, 17), Vector(22, 17)}, north },	// mesa
		{{Vector(19, 17), Vector(19, 10), CASH_REGISTER}},	// pagar
		{{Vector(28, 17), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 2 silla derecha
		{{Vector(27, 12), Vector(17, 12), Vector(17, 15)}, west },	// mesa
		{{Vector(17, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(17, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
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