#pragma once
#include "../Structure/Component.h"
#include "../Definitions/Food_def.h"
#include "../Structure/GameObject.h"
#include "../Structure/GameManager.h"
#include "Transform.h"
#include "ButtonComp.h"
#include "../Utilities/SDLUtils.h"
#include "Image.h"
#include <set>

class DailyMenuComp : public Component {
private:
	const float STARTING_X = -30, STARTING_Y = 70, ING_OFFSET_X = 10,
				MENU_SIZE = 4, DISH_SIZE = 64, INGREDIENT_SIZE = 48,
				FONT_SIZE = 20, CENTER_OUTLINE = 4, TEXT_RESIZE = 1.2;
	const string FONT_PATH = "assets/Fonts/light_pixel-7.ttf";

	Transform* tf;
	void drawDishes();
	Scene* parentScene;
	vector<_ecs::DishInfo>* menu;
	void randomMenu();
	
	struct rend {
		Texture* tex;
		float x;
		float y;
	public:
		rend(Texture* t, float _x, float _y) : tex(t), x(_x), y(_y) { };
	};
	vector<rend> dishTextures;
	vector<rend> textTextures;
	vector<rend> textOutlines;
	vector<rend> ingTextures;
	vector<rend> menuText;

	bool murder;

	Font* font;
	Font* fontOutline;

	void init(GameObject* parent);
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_DAILYMENU;
	DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id);
	DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, vector<_ecs::DishInfo>* _menu);
	virtual ~DailyMenuComp();

	virtual void render();
	vector<_ecs::DishInfo>* getMenu();
	void setMenu(vector<_ecs::DishInfo>* _menu);
};

