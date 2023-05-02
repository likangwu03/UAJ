#pragma once
#include <cstdint>
#include <unordered_map>
#include "../Utilities/Vector.h"
#include "../Components/Transform.h"
#include <string>


using namespace std;
namespace _ecs {
	using id_type = uint8_t;

	struct Route {
		vector<Vector> points;
		GOOrientation orientation = none;
	};

	// LADRONES
	const int MAX_THIEFS = 3;
	const int NUM_THIEFS_PATHS = 2;

	enum _path_thief_id : id_type {
		SECRET_1,
		SECRET_2,
		SECRET_3,
		FREEZER_1,
		FREEZER_2,
		FREEZER_3
	};

	static _path_thief_id enumThiefsPaths[NUM_THIEFS_PATHS][MAX_THIEFS]{
		_path_thief_id::SECRET_1,
		_path_thief_id::SECRET_2,
		_path_thief_id::SECRET_3,
		_path_thief_id::FREEZER_1,
		_path_thief_id::FREEZER_2,
		_path_thief_id::FREEZER_3
	};

	const Vector DOOR = Vector(-1, 13);
	const Vector SECRET = Vector(26, 6);
	const Vector FREEZER = Vector(15, 5);

	// los caminos van de abajo a arriba
	// es decir, el 1 es el que esta más abajo
	static Route thiefsPahts[NUM_THIEFS_PATHS * MAX_THIEFS] = {
		// fórmula secreta
		{{Vector(7, 13), Vector(7, 11), Vector(16, 11), Vector(16, 14), Vector(23, 14), Vector(23, 12), Vector(26, 12), SECRET}, north},
		{{Vector(7, 12), Vector(7, 11), Vector(15, 11), Vector(15, 6), Vector(24, 6), Vector(24, 7), Vector(26, 7), SECRET}, north},
		{{Vector(8, 11), Vector(8, 8), Vector(12, 8), Vector(12, 7), Vector(15, 7), Vector(15, 10), Vector(23, 10), Vector(23, 8), Vector(26, 8), SECRET}, north},

		// frigorífico
		{{Vector(7, 13), Vector(7, 11), Vector(15, 11), FREEZER}, north},
		{{Vector(7, 12), Vector(7, 11), Vector(15, 11), FREEZER}, north},
		{{Vector(8, 11), Vector(8, 8), Vector(12, 8), Vector(12, 7), Vector(15, 7), FREEZER}, north}
	};

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
		ARRIVE_TABLE_3_LEFT,
		PAY_TABLE_3_LEFT,
		OUT_TABLE_3_LEFT,
		ARRIVE_TABLE_3_RIGHT,
		PAY_TABLE_3_RIGHT,
		OUT_TABLE_3_RIGHT,
		ARRIVE_TABLE_3_DOWN,
		PAY_TABLE_3_DOWN,
		OUT_TABLE_3_DOWN,
		ARRIVE_TABLE_3_UP,
		PAY_TABLE_3_UP,
		OUT_TABLE_3_UP,
		// mesa 4
		ARRIVE_TABLE_4_LEFT,
		PAY_TABLE_4_LEFT,
		OUT_TABLE_4_LEFT,
		ARRIVE_TABLE_4_RIGHT,
		PAY_TABLE_4_RIGHT,
		OUT_TABLE_4_RIGHT,
		ARRIVE_TABLE_4_DOWN,
		PAY_TABLE_4_DOWN,
		OUT_TABLE_4_DOWN,
		ARRIVE_TABLE_4_UP,
		PAY_TABLE_4_UP,
		OUT_TABLE_4_UP,
		// mesa 5
		ARRIVE_TABLE_5_LEFT,
		PAY_TABLE_5_LEFT,
		OUT_TABLE_5_LEFT,
		ARRIVE_TABLE_5_RIGHT,
		PAY_TABLE_5_RIGHT,
		OUT_TABLE_5_RIGHT,
		ARRIVE_TABLE_5_DOWN,
		PAY_TABLE_5_DOWN,
		OUT_TABLE_5_DOWN,
		ARRIVE_TABLE_5_UP,
		PAY_TABLE_5_UP,
		OUT_TABLE_5_UP,
		// mesa 6
		ARRIVE_TABLE_6_LEFT_1,
		PAY_TABLE_6_LEFT_1,
		OUT_TABLE_6_LEFT_1,
		ARRIVE_TABLE_6_LEFT_2,
		PAY_TABLE_6_LEFT_2,
		OUT_TABLE_6_LEFT_2,
		ARRIVE_TABLE_6_RIGHT_1,
		PAY_TABLE_6_RIGHT_1,
		OUT_TABLE_6_RIGHT_1,
		ARRIVE_TABLE_6_RIGHT_2,
		PAY_TABLE_6_RIGHT_2,
		OUT_TABLE_6_RIGHT_2,
		// mesa 7
		ARRIVE_TABLE_7_LEFT_1,
		PAY_TABLE_7_LEFT_1,
		OUT_TABLE_7_LEFT_1,
		ARRIVE_TABLE_7_LEFT_2,
		PAY_TABLE_7_LEFT_2,
		OUT_TABLE_7_LEFT_2,
		ARRIVE_TABLE_7_RIGHT_1,
		PAY_TABLE_7_RIGHT_1,
		OUT_TABLE_7_RIGHT_1,
		ARRIVE_TABLE_7_RIGHT_2,
		PAY_TABLE_7_RIGHT_2,
		OUT_TABLE_7_RIGHT_2,

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
		// mesa 1 abajo
		_path_client_id::ARRIVE_TABLE_1_DOWN,
		_path_client_id::PAY_TABLE_1_DOWN,
		_path_client_id::OUT_TABLE_1_DOWN,
		// mesa 1 arriba
		_path_client_id::ARRIVE_TABLE_1_UP,
		_path_client_id::PAY_TABLE_1_UP,
		_path_client_id::OUT_TABLE_1_UP,

		// mesa 2 izquierda
		_path_client_id::ARRIVE_TABLE_2_LEFT,
		_path_client_id::PAY_TABLE_2_LEFT,
		_path_client_id::OUT_TABLE_2_LEFT,
		// mesa 2 derecha
		_path_client_id::ARRIVE_TABLE_2_RIGHT,
		_path_client_id::PAY_TABLE_2_RIGHT,
		_path_client_id::OUT_TABLE_2_RIGHT,
		// mesa 2 abajo
		_path_client_id::ARRIVE_TABLE_2_DOWN,
		_path_client_id::PAY_TABLE_2_DOWN,
		_path_client_id::OUT_TABLE_2_DOWN,
		// mesa 2 arriba
		_path_client_id::ARRIVE_TABLE_2_UP,
		_path_client_id::PAY_TABLE_2_UP,
		_path_client_id::OUT_TABLE_2_UP,

		// mesa 3 izquierda
		_path_client_id::ARRIVE_TABLE_3_LEFT,
		_path_client_id::PAY_TABLE_3_LEFT,
		_path_client_id::OUT_TABLE_3_LEFT,
		// mesa 3 derecha
		_path_client_id::ARRIVE_TABLE_3_RIGHT,
		_path_client_id::PAY_TABLE_3_RIGHT,
		_path_client_id::OUT_TABLE_3_RIGHT,
		// mesa 3 abajo
		_path_client_id::ARRIVE_TABLE_3_DOWN,
		_path_client_id::PAY_TABLE_3_DOWN,
		_path_client_id::OUT_TABLE_3_DOWN,
		// mesa 3 arriba
		_path_client_id::ARRIVE_TABLE_3_UP,
		_path_client_id::PAY_TABLE_3_UP,
		_path_client_id::OUT_TABLE_3_UP,

		// mesa 4 izquierda
		_path_client_id::ARRIVE_TABLE_4_LEFT,
		_path_client_id::PAY_TABLE_4_LEFT,
		_path_client_id::OUT_TABLE_4_LEFT,
		// mesa 4 derecha
		_path_client_id::ARRIVE_TABLE_4_RIGHT,
		_path_client_id::PAY_TABLE_4_RIGHT,
		_path_client_id::OUT_TABLE_4_RIGHT,
		// mesa 4 abajo
		_path_client_id::ARRIVE_TABLE_4_DOWN,
		_path_client_id::PAY_TABLE_4_DOWN,
		_path_client_id::OUT_TABLE_4_DOWN,
		// mesa 4 arriba
		_path_client_id::ARRIVE_TABLE_4_UP,
		_path_client_id::PAY_TABLE_4_UP,
		_path_client_id::OUT_TABLE_4_UP,

		// mesa 5 izquierda
		_path_client_id::ARRIVE_TABLE_5_LEFT,
		_path_client_id::PAY_TABLE_5_LEFT,
		_path_client_id::OUT_TABLE_5_LEFT,
		// mesa 5 derecha
		_path_client_id::ARRIVE_TABLE_5_RIGHT,
		_path_client_id::PAY_TABLE_5_RIGHT,
		_path_client_id::OUT_TABLE_5_RIGHT,
		// mesa 5 abajo
		_path_client_id::ARRIVE_TABLE_5_DOWN,
		_path_client_id::PAY_TABLE_5_DOWN,
		_path_client_id::OUT_TABLE_5_DOWN,
		// mesa 5 arriba
		_path_client_id::ARRIVE_TABLE_5_UP,
		_path_client_id::PAY_TABLE_5_UP,
		_path_client_id::OUT_TABLE_5_UP,

		// mesa 6 izquierda abajo
		_path_client_id::ARRIVE_TABLE_6_LEFT_1,
		_path_client_id::PAY_TABLE_6_LEFT_1,
		_path_client_id::OUT_TABLE_6_LEFT_1,
		// mesa 6 izquierda arriba
		_path_client_id::ARRIVE_TABLE_6_LEFT_2,
		_path_client_id::PAY_TABLE_6_LEFT_2,
		_path_client_id::OUT_TABLE_6_LEFT_2,
		// mesa 6 derecha abajo
		_path_client_id::ARRIVE_TABLE_6_RIGHT_1,
		_path_client_id::PAY_TABLE_6_RIGHT_1,
		_path_client_id::OUT_TABLE_6_RIGHT_1,
		// mesa 6 derecha arriba
		_path_client_id::ARRIVE_TABLE_6_RIGHT_2,
		_path_client_id::PAY_TABLE_6_RIGHT_2,
		_path_client_id::OUT_TABLE_6_RIGHT_2,

		// mesa 7 izquierda abajo
		_path_client_id::ARRIVE_TABLE_7_LEFT_1,
		_path_client_id::PAY_TABLE_7_LEFT_1,
		_path_client_id::OUT_TABLE_7_LEFT_1,
		// mesa 7 izquierda arriba
		_path_client_id::ARRIVE_TABLE_7_LEFT_2,
		_path_client_id::PAY_TABLE_7_LEFT_2,
		_path_client_id::OUT_TABLE_7_LEFT_2,
		// mesa 7 derecha abajo
		_path_client_id::ARRIVE_TABLE_7_RIGHT_1,
		_path_client_id::PAY_TABLE_7_RIGHT_1,
		_path_client_id::OUT_TABLE_7_RIGHT_1,
		// mesa 7 derecha arriba
		_path_client_id::ARRIVE_TABLE_7_RIGHT_2,
		_path_client_id::PAY_TABLE_7_RIGHT_2,
		_path_client_id::OUT_TABLE_7_RIGHT_2,
	};

	// afuera entrada
	const Vector OUT_ENTRY = Vector(40, 16);
	// entrada
	const Vector ENTRY = Vector(27, 16);
	// pos 1 casilla más en y que la caja registradora
	const Vector CASH_REGISTER = Vector(26, 11);
	// salida
	const Vector PAY = Vector(28, 13);
	// afuera salida
	const Vector OUT_PAY = Vector(40, 13);

	static Route clientsPaths[NUM_TABLES * NUM_SEATS * NUM_CLIENTS_PATHS + 1] = {
		// De abajo a arriba (izquierda, derecha, abajo, arriba)
		// mesa 1 silla izquierda
		{{Vector(27, 18), Vector(20, 18), Vector(20, 15)}, east},	// mesa
		{{Vector(20, 11), CASH_REGISTER}},	// pagar
		{{Vector(20, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 1 silla derecha
		{{Vector(24, 15)}, west },	// mesa
		{{Vector(24, 11), CASH_REGISTER}},	// pagar
		{{Vector(24, 13), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 1 silla abajo
		{{Vector(27, 17), Vector(22, 17)}, north },	// mesa
		{{Vector(19, 17), Vector(19, 11), CASH_REGISTER}},	// pagar
		{{Vector(19, 17), Vector(19,13), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 1 silla arriba
		{{Vector(22, 13)}, south },	// mesa
		{{Vector(22, 11), CASH_REGISTER}},	// pagar
		{{PAY, OUT_PAY}},	// marcharse mesa

		// mesa 2 silla izquierda
		{{Vector(27, 12), Vector(13, 12), Vector(13, 15)}, east },	// mesa
		{{Vector(13, 12), Vector(17, 12), Vector(21, 12), Vector(21, 11), CASH_REGISTER}},	// pagar
		{{Vector(13, 12), Vector(17, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 2 silla derecha
		{{Vector(27, 12), Vector(17, 12), Vector(17, 15)}, west },	// mesa
		{{Vector(17, 12), Vector(21, 12), Vector(21, 11), CASH_REGISTER}},	// pagar
		{{Vector(17, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 2 silla abajo
		{{Vector(27, 12), Vector(18, 12), Vector(18, 17), Vector(15, 17)}, north },	// mesa
		{{Vector(19, 17), Vector(19, 11), CASH_REGISTER}},	// pagar
		{{Vector(19, 17), Vector(19, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 2 silla arriba
		{{Vector(27, 12), Vector(15, 12), Vector(15, 13)}, south },	// mesa
		{{Vector(15, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(15, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa

		// mesa 3 silla izquierda
		{{Vector(27, 12), Vector(6, 12), Vector(6, 15)}, east },	// mesa
		{{Vector(6, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(6, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 3 silla derecha
		{{Vector(27, 12), Vector(10, 12), Vector(10, 15)}, west },	// mesa
		{{Vector(10, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(10, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 3 silla abajo
		{{Vector(27, 12), Vector(11, 12), Vector(11, 17), Vector(8, 17)}, north },	// mesa
		{{Vector(12, 17), Vector(12, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(12, 17), Vector(12, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 3 silla arriba
		{{Vector(27, 12), Vector(8, 12), Vector(8, 13)}, south },	// mesa
		{{Vector(8, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(8, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa

		// mesa 4 silla izquierda
		{{Vector(27, 12), Vector(15, 12), Vector(15, 9)}, east },	// mesa
		{{Vector(15, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(15, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 4 silla derecha
		{{Vector(27, 11), Vector(19, 11), Vector(19, 9)}, west },	// mesa
		{{Vector(19, 11), CASH_REGISTER}},	// pagar
		{{Vector(19, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 4 silla abajo
		{{Vector(27, 11), Vector(17, 11)}, north },	// mesa
		{{CASH_REGISTER}},	// pagar
		{{Vector(28, 11), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 4 silla arriba
		{{Vector(27, 12), Vector(20, 12), Vector(20, 7), Vector(17, 7)}, south},	// mesa
		{{Vector(21, 7), Vector(21, 11), CASH_REGISTER}},	// pagar
		{{Vector(21, 7), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa

		// mesa 5 silla izquierda
		{{Vector(27, 12), Vector(8, 12), Vector(8, 9)}, east },	// mesa
		{{Vector(8, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(8, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 5 silla derecha
		{{Vector(27, 12), Vector(12, 12), Vector(12, 9)}, west },	// mesa
		{{Vector(12, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(12, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 5 silla abajo
		{{Vector(27, 12), Vector(10, 12), Vector(10, 11)}, north },	// mesa
		{{Vector(10, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(10, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 5 silla arriba
		{{Vector(27, 12), Vector(13, 12), Vector(13, 7), Vector(10, 7)}, south},	// mesa
		{{Vector(14, 7), Vector(14, 12), Vector(26, 12), CASH_REGISTER}},	// pagar
		{{Vector(14, 7), Vector(14, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa

		// mesa 6 silla izquierda abajo
		{{Vector(27, 12), Vector(20, 12), Vector(20, 6), Vector(12, 6), Vector(12, 5)}, east},	// mesa
		{{Vector(12, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER}},	// pagar
		{{Vector(12, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 6 silla izquierda arriba
		{{Vector(27, 12), Vector(20, 12), Vector(20, 6), Vector(11, 6), Vector(11, 4), Vector(12, 4)}, east},	// mesa
		{{Vector(11, 4), Vector(11, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER}},	// pagar
		{{Vector(11, 4), Vector(11, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 6 silla derecha abajo
		{{Vector(27, 12), Vector(20, 12), Vector(20, 5), Vector(16, 5)}, west },	// mesa
		{{Vector(16, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER}},	// pagar
		{{Vector(16, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa
		// mesa 6 silla derecha arriba
		{{Vector(27, 12), Vector(20, 12), Vector(20, 6), Vector(18, 6), Vector(18, 4), Vector(16, 4)}, west },	// mesa
		{{Vector(18, 4), Vector(18, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER}},	// pagar
		{{Vector(18, 4), Vector(18, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY}},	// marcharse mesa

		// mesa 7 silla izquierda abajo
		{ {Vector(27, 12), Vector(5, 12), Vector(5, 5)}, east },	// mesa
		{ {Vector(5, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER} },	// pagar
		{ {Vector(5, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY} },	// marcharse mesa
		// mesa 7 silla izquierda arriba
		{ {Vector(27, 12), Vector(5, 12), Vector(5, 7), Vector(4, 7), Vector(4, 4), Vector(5, 4)}, east },	// mesa
		{ {Vector(4, 4), Vector(4, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER} },	// pagar
		{ {Vector(4, 4), Vector(4, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY} },	// marcharse mesa
		// mesa 7 silla derecha abajo
		{ {Vector(27, 12), Vector(6, 12), Vector(6, 6), Vector(9, 6), Vector(9, 5)}, west},	// mesa
		{ {Vector(9, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER} },	// pagar
		{ {Vector(9, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY} },	// marcharse mesa
		// mesa 7 silla derecha arriba
		{ {Vector(27, 12), Vector(6, 12), Vector(6, 6), Vector(10, 6), Vector(10, 4), Vector(9, 4)}, west },	// mesa
		{ {Vector(10, 4), Vector(10, 6), Vector(21, 6), Vector(21, 11), CASH_REGISTER} },	// pagar
		{ {Vector(10, 4), Vector(10, 6), Vector(21, 6), Vector(21, 12), Vector(28, 12), PAY, OUT_PAY} },	// marcharse mesa

		// marcharse después de haber pagado la comida
		{{Vector(26, 13), OUT_PAY}}
	};
};