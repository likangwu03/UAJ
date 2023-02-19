#pragma once
#include <cstdint>
#include <vector>
#include "../utilities/Vector.h"
#include "../components/Transform.h"

using namespace std;
namespace _ecs {
	using id_type = uint8_t;

	const id_type NUM_PATHS = 22;

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
	/*
	// entrada
	const Vector ENTRY = Vector(950, 470);
	// fuera
	const Vector OUT = Vector(1300, 470);
	// pos caja registradora
	const Vector CASH_REGISTER = Vector(900, 290);
	*/

	// array de vectores
	// cada vector es uno de los paths posibles
	// a la hora de pagar lo importante es que entra desde la izq con un Vector(x, 290)
	static Route paths[NUM_PATHS] = {
		// mesa 1 silla izquierda
		{{Vector(27, 11), Vector(20, 11), Vector(20, 15)}, east },	// mesa
		{{Vector(20, 10), CASH_REGISTER}},	// pagar
		{{Vector(20, 11), Vector(27, 11), ENTRY, OUT}},	// marcharse mesa
		// mesa 2 silla derecha
		{{Vector(27, 12), Vector(17, 12), Vector(17, 15)}, west },	// mesa
		{{Vector(17, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(17, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// mesa 3 silla derecha
		{{Vector(27, 12), Vector(10, 12), Vector(10, 15)}, west },	// mesa
		{{Vector(10, 12), Vector(21, 12), Vector(21, 10), CASH_REGISTER}},	// pagar
		{{Vector(10, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// mesa 4 silla derecha
		{{Vector(27, 11), Vector(19, 11), Vector(19, 9)}, west},	// mesa
		{{Vector(19, 10), CASH_REGISTER}},	// pagar
		{{Vector(19, 11), Vector(27, 11), ENTRY, OUT}},	// marcharse mesa
		// mesa 5 silla derecha
		{{Vector(27, 12), Vector(12, 12), Vector(12, 9)}, west },	// mesa
		{{Vector(12, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(12, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// mesa 6 silla derecha
		{{Vector(27, 11), Vector(20, 11), Vector(20, 6), Vector(15, 6), Vector(15, 4)}, west},	// mesa
		{{Vector(15, 6), Vector(20, 6), Vector(20, 10), CASH_REGISTER}},	// pagar
		{{Vector(15, 6), Vector(20, 6), Vector(20, 11), Vector(27, 11), ENTRY, OUT}},	// marcharse mesa
		// mesa 7 silla izquierda
		{{Vector(27, 12), Vector(6, 12), Vector(6, 4)}, east },	// mesa
		{{Vector(6, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(6, 12), Vector(27, 12), ENTRY, OUT}},	// marcharse mesa
		// marcharse haciendo cola en la caja
		{{Vector(26, 15), OUT}}
	};
	/* static Route paths[NUM_PATHS] = {
		// mesa 1 silla izquierda
		{{Vector(950, 360), Vector(675, 360), Vector(675, 465)}, east },	// mesa
		{{Vector(675, 290), CASH_REGISTER}},	// pagar
		{{Vector(675, 360), Vector(950, 360), Vector(950, 470), OUT}},	// marcharse mesa
		// mesa 2 silla derecha
		{{Vector(950, 360), Vector(565, 360), Vector(565, 465)}, west },	// mesa
		{{Vector(565, 360), Vector(700, 360), Vector(700, 290), CASH_REGISTER}},	// pagar
		{{Vector(565, 360), Vector(950, 360), Vector(950, 470), OUT}},	// marcharse mesa
		// mesa 4 silla derecha
		{{Vector(950, 360), Vector(635, 360), Vector(635, 250)}, west},	// mesa
		{{Vector(635, 290), CASH_REGISTER}},	// pagar
		{{Vector(635, 360), Vector(950, 360), Vector(950, 470), OUT}},	// marcharse mesa
		{{Vector(900, 470), OUT}}			// marcharse pagando
	};
	*/
};