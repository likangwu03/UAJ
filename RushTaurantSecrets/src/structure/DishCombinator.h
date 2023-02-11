#pragma once
#include "Food_def.h"
#include <unordered_map>
#include <vector>
using namespace std;
/*
* Sirve para consultar el plato que puede generar seg¨²n la combinaci¨®n de una serie ingredientes
* Se crea solo una vez en Game
*/
class DishCombinator
{
private:
	struct VectorHasher {
		int operator()(const vector<_ecs::_ingredients_id>& V) const {
			int hash = V.size();
			for (auto i : V) {
				hash ^= (int)i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			}
			return hash;
		}
	};

	//contiene todas las combinaciones pos de cada plato
	unordered_map < vector<_ecs::_ingredients_id>, _ecs::_dish_id,VectorHasher> dishes;
	//genera todas las combinaciones posibles
	void auxCombinator(int n,int m,int k,vector<_ecs::_ingredients_id>&soluc, vector<bool>&used,_ecs::_dish_id id, vector<_ecs::_ingredients_id>& ing);

public:
	
	DishCombinator();
	//consulta map
	pair<_ecs::_dish_id, bool> existDish(const vector<_ecs::_ingredients_id>* ing);
};

