#pragma once
#include "../structure/Component.h"
#include "../objects/DishCombinator.h"
#include "../components/UIAnimator.h"
#include "../components/Transform.h"
#include "../components/Ingredients.h"
#include "../sdlutils/SDLUtils.h"
#include "../utilities/Vector.h"


using namespace std;
class KitchenIslandComp :public Component
{
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_KITCHENISLAND;
private:
	const float
		F_W =8,
		F_H = 19,
		B_H=F_H+12,
		B_W=F_W+10,OFFSETX=-6,OFFSETY=-6;

	struct Ing {
		_ecs::_ingredients_id id;
		int n;
		Texture* t;
		Texture* f;
		Texture* b;
	};
	Font* f; //para indicar n de ing
	vector<Ing>ing;
	SDLUtils* sdl;
	Ingredients* ingCloud;
	float w, h;// para cada ing
	float x, y;

public:
	KitchenIslandComp(GameObject* parent, vector<pair<_ecs::_ingredients_id,int>> _ing);

	virtual void render();
	void pickIngredient(int i);
};

