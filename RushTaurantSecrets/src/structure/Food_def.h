#pragma once
#include <cstdint>
namespace _ecs {
	using id_type = uint8_t;

	enum _recipes_id : id_type {
		HUEVO_FRITO,
		PAN,
		MERMELADA,
		PAN_AJO,
		FRENCH_FRIES,
		PANCAKE,
		TARTA_FRESA,
		TARTA_CHOC,
		TARTA_FRAM,
		GALLETAS,
		OMELETTE,
		TARTA_MAN,
		TARTA_QUESO,
		BURRITO,
		PURE,
		HELADO,
		NACHOS,
		HOTDOG,
		SANDWICH,
		SUSHI,
		CURRY_ARROZ,
		PIZZA,
		POLLO,
		FILETE,
		ALBONDIGAS,
		ESTAGUETI,
		BURGUER,
		RAMEN

	};
	enum _ingredients_id : id_type {
		HARINA,
		HUEVO,
		PATATA,
		CHOCOLATE,
		LECHUGA,
		MAIZ,
		FRESA,
		ZANAHORIA,
		AJO,
		LECHE,
		ARROZ,
		TOMATE,
		MANZANA,
		MANTEQUILLA,
		FRAMBUESA,
		MOSTAZA,
		FIDEOS,
		CURRY,
		QUESO,
		SALCHICHA,
		POLLO,
		GAMBAS,
		SALMON,
		CARNE
	};

	struct DishInfo {
		int cookingTime;
		int ingredients[];
	};



}