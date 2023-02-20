#pragma once
#include <cstdint>
#include <vector>
#include "../utilities/Vector.h"
#include "../components/Transform.h"

using namespace std;
namespace _ecs {
	using id_type = uint8_t;

	const id_type NUM_TABLES = 7;

	enum _path_id : id_type {
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

	static unordered_map<string, _path_id> stringToEnum = {
		{"ARRIVE_TABLE_1",_path_id::ARRIVE_TABLE_1},
		{"PAY_TABLE_1", _path_id::PAY_TABLE_1},
		{"OUT_TABLE_1", _path_id::OUT_TABLE_1},
		{"ARRIVE_TABLE_2",_path_id::ARRIVE_TABLE_2},
		{"PAY_TABLE_2",_path_id::PAY_TABLE_2},
		{"OUT_TABLE_2",_path_id::OUT_TABLE_2},
		{"ARRIVE_TABLE_3",_path_id::ARRIVE_TABLE_3},
		{"PAY_TABLE_3", _path_id::PAY_TABLE_3},
		{"OUT_TABLE_3", _path_id::OUT_TABLE_3},
		{"ARRIVE_TABLE_4", _path_id::ARRIVE_TABLE_4},
		{"PAY_TABLE_4",_path_id::PAY_TABLE_4},
		{"OUT_TABLE_4",_path_id::OUT_TABLE_4},
		{"ARRIVE_TABLE_5",_path_id::ARRIVE_TABLE_5},
		{"PAY_TABLE_5", _path_id::PAY_TABLE_5},
		{"OUT_TABLE_5", _path_id::OUT_TABLE_5},
		{"ARRIVE_TABLE_6",_path_id::ARRIVE_TABLE_6},
		{"PAY_TABLE_6", _path_id::PAY_TABLE_6},
		{"OUT_TABLE_6", _path_id::OUT_TABLE_6},
		{"ARRIVE_TABLE_7",_path_id::ARRIVE_TABLE_7},
		{"PAY_TABLE_7", _path_id::PAY_TABLE_7},
		{"OUT_TABLE_7", _path_id::OUT_TABLE_7},
	};

	struct Route {
		vector<Vector> points;
		GOOrientation orientation = none;
	};

	// entrada
	const Vector ENTRY = Vector(27, 15);
	// fuera
	const Vector OUT = Vector(40, 15);
	// pos caja registradora
	const Vector CASH_REGISTER = Vector(26, 10);

	// array de vectores
	// cada vector es uno de los paths posibles
	// a la hora de pagar lo importante es que entra desde la izq con un Vector(x, 290)
	static Route paths[NUM_TABLES * 3 + 1] = {
		// mesa 1 silla izquierda
		{{Vector(27, 11), Vector(20, 11), Vector(20, 14)}, east },	// mesa
		{{Vector(20, 10), CASH_REGISTER}},	// pagar
		{{Vector(20, 11), Vector(27, 11), ENTRY, OUT}},	// marcharse mesa
		// mesa 2 silla derecha
		{{Vector(27, 12), Vector(17, 12), Vector(17, 14)}, west },	// mesa
		{{Vector(17, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(17, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// mesa 3 silla derecha
		{{Vector(27, 12), Vector(10, 12), Vector(10, 14)}, west },	// mesa
		{{Vector(10, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(10, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// mesa 4 silla derecha
		{{Vector(27, 11), Vector(19, 11), Vector(19, 8)}, west},	// mesa
		{{Vector(19, 10), CASH_REGISTER}},	// pagar
		{{Vector(19, 11), Vector(27, 11), ENTRY, OUT}},	// marcharse mesa
		// mesa 5 silla derecha
		{{Vector(27, 12), Vector(12, 12), Vector(12, 8)}, west },	// mesa
		{{Vector(12, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(12, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// mesa 6 silla derecha
		{{Vector(27, 11), Vector(20, 11), Vector(20, 6), Vector(16, 6), Vector(16, 4)}, west},	// mesa
		{{Vector(16, 6), Vector(20, 6), Vector(20, 10), CASH_REGISTER}},	// pagar
		{{Vector(16, 6), Vector(20, 6), Vector(20, 11), Vector(27, 11), ENTRY, OUT}},	// marcharse mesa
		// mesa 7 silla izquierda
		{{Vector(27, 12), Vector(5, 12), Vector(5, 4)}, east },	// mesa
		{{Vector(5, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(5, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// marcharse haciendo cola en la caja
		{{Vector(26, 15), OUT}}
	};
};