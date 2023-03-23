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
	bool random;
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

