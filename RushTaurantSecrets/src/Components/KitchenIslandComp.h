#pragma once

#include "../Structure/Component.h"
#include "../Managers/DishCombinator.h"
#include "UIAnimator.h"
#include "Transform.h"

#include "Image.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/Vector.h"
#include <unordered_map>

using namespace std;
class Ingredients;
class KitchenIslandComp :public Component
{
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_KITCHENISLAND;
private:
	const string FONT_PATH = "assets/Fonts/EpilepsySansBold.ttf";
	const float FONTSIZE = 15,
				B_H = 20, B_W = 20,
				OFFSETX = -6, OFFSETY = -6;

	struct Ing {
		int n;		// número de ingredientes
		Texture* t;	// imagen del ingrediente
		Texture* f;	// imagen con el número de ingredientes que tienes (delantera)
		Texture* b;	//
	};
	Font* font; //para indicar n de ing
	unordered_map<_ecs::_ingredients_id,Ing>ing;
	vector<_ecs::_ingredients_id>auxID;
	SDLUtils* sdl;
	Ingredients* ingCloud;
	Texture* highlight;
	Texture* KI_icon;
	Vector hPos;
	int selected;
	float w, h;// para cada ing
	float x, y;

public:
	KitchenIslandComp(GameObject* parent);
	virtual ~KitchenIslandComp();

	virtual void render();
	void pickIngredient(int i);
	void returnIngredient(_ecs::_ingredients_id id);
	void selectedIng(int i);
	void unselectIng(int i);

	void setIngredients(vector<pair<_ecs::_ingredients_id, int>> _ing);
};

