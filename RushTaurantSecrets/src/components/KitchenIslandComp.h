#pragma once
#include "../structure/Component.h"
#include "../objects/DishCombinator.h"
#include "../components/UIAnimator.h"
#include "../components/Transform.h"
#include "../components/Ingredients.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../utilities/Vector.h"


using namespace std;
class KitchenIslandComp :public Component
{
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_KITCHENISLAND;
private:
	const float
		F_W =12,
		F_H = 25,
		B_H=20,
		B_W=20,OFFSETX=-6,OFFSETY=-6;

	struct Ing {
		_ecs::_ingredients_id id;	// id del ingrediente
		int n;	// número de ingredientes
		Texture* t;	// imagen del ingrediente
		Texture* f;	// imagen con el número de ingredientes que tienes (delantera)
		Texture* b;	//
	};
	Font* f; //para indicar n de ing
	vector<Ing>ing;
	SDLUtils* sdl;
	Ingredients* ingCloud;
	Texture* highlight;
	Vector hPos;
	int selected;
	float w, h;// para cada ing
	float x, y;

public:
	KitchenIslandComp(GameObject* parent, vector<pair<_ecs::_ingredients_id,int>> _ing);
	virtual ~KitchenIslandComp();

	virtual void render();
	void pickIngredient(int i);
	void selectedIng(int i);
	void unselectIng(int i);
};

