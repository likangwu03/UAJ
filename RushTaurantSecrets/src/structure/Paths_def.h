#pragma once
#include <cstdint>
#include <vector>
#include "../utilities/Vector.h"
#include "../components/Transform.h"

using namespace std;


namespace _ecs {
	using id_type = uint8_t;

	const id_type NUM_PATHS = 10;

	enum _path_id : id_type {
		ARRIVE_TABLE_1,
		PAY_TABLE_1,
		OUT_TABLE_1,
		ARRIVE_TABLE_2,
		PAY_TABLE_2,
		OUT_TABLE_2,
		ARRIVE_TABLE_4,
		PAY_TABLE_4,
		OUT_TABLE_4,
		PAY_AND_LEAVE
	};

	static unordered_map<string, _path_id> stringToEnum = {
		{"ARRIVE_TABLE_1",_path_id::ARRIVE_TABLE_1},
		{"PAY_TABLE_1", _path_id::PAY_TABLE_1},
		{"OUT_TABLE_1", _path_id::OUT_TABLE_1},
		{"ARRIVE_TABLE_2",_path_id::ARRIVE_TABLE_2},
		{"PAY_TABLE_2",_path_id::PAY_TABLE_2},
		{"OUT_TABLE_2",_path_id::OUT_TABLE_2},
		{"ARRIVE_TABLE_4", _path_id::ARRIVE_TABLE_4},
		{"PAY_TABLE_4",_path_id::PAY_TABLE_4},
		{"OUT_TABLE_4",_path_id::OUT_TABLE_4}
	};

	struct Route {
		vector<Vector> points;
		GOOrientation orientation = none;
	};

	// entrada
	const Vector ENTRY = Vector(950, 470);
	// fuera
	const Vector OUT = Vector(1300, 470);
	// pos caja registradora
	const Vector CASH_REGISTER = Vector(900, 290);

	// array de vectores
	// cada vector es uno de los paths posibles
	// a la hora de pagar lo importante es que entra desde la izq con un Vector(x, 290)
	static Route paths[NUM_PATHS] = {
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
};