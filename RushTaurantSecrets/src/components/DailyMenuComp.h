#pragma once
#include "../structure/Component.h"
#include "../structure/Food_def.h"
#include "../structure/GameObject.h"
#include "../structure/GameManager.h"
#include "../components/Transform.h"
#include "../components/ButtonComp.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include <set>

class DailyMenuComp : public Component
{
private:
	Transform* tf;
	void drawDishes();
	Scene* parentScene;
	vector<_ecs::DishInfo>* menu;
	void randomMenu();
	uint8_t menuSize;
	uint8_t spriteSize;
	struct rend
	{
		Texture* tex;
		float x;
		float y;
	public:
		rend(Texture* t, float _x, float _y) : tex(t), x(_x), y(_y) { };
	};
	vector<rend> textures;
	vector<rend> prices;

	bool murder;

	Font* font;

	void init(GameObject* parent);
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_DAILYMENU;
	DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, uint8_t mSize = 4);
	DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, vector<_ecs::DishInfo>* _menu);
	virtual ~DailyMenuComp();

	virtual void render();
	vector<_ecs::DishInfo>* getMenu();
	void setMenu(vector<_ecs::DishInfo>* _menu);
};

