#include "DishCombinator.h"

#include "../Utilities/checkML.h"

DishCombinator::DishCombinator() {
	for (auto d : _ecs::Dishes) {
		//vuelta atras
		vector<bool>used(d.ingredients.size(), false);
		vector<_ecs::_ingredients_id>soluc(d.ingredients.size());
		auxCombinator(d.ingredients.size(), d.ingredients.size(), 0, soluc, used, d.id, d.ingredients);
	}
}

void DishCombinator::auxCombinator(int n, int m, int k, vector<_ecs::_ingredients_id>& soluc, vector<bool>& used,
	_ecs::_dish_id id, vector<_ecs::_ingredients_id>& ing) {
	for (int i = 0; i < m; ++i) {
		soluc[k] = (_ecs::_ingredients_id)ing[i];
		if (!used[i]) {
			used[i] = true;
			if (k == n - 1) dishes.insert({ soluc,id });
			else auxCombinator(n, m, k + 1, soluc, used, id, ing);
			used[i] = false;
		}
	}
}

pair<_ecs::_dish_id, bool> DishCombinator::existDish(const vector<_ecs::_ingredients_id> ing) {
	auto it = dishes.find(ing);
	if (it == dishes.end()) return { _ecs::NONE_DISH,false };
	else return { it->second,true };
}
