#pragma once
#include "../structure/Component.h"
#include "../structure/DishCombinator.h"
#include "../components/Animator.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../utilities/Vector.h"
class CookingMachineComp :public Component
{
public:
	//determinar si el horno est¨¢ libre, cocinando o que ha cocinado un plato
	enum State { available, cooking, finished };
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COOKMACHINE;
private:
	const int 
		BUBBLE_OFFSETX = -4,
		BUBBLE_OFFSETY = -60,
		BUBBLE_WIDTH = 41,
		BUBBLE_HEIGHT = 48,
		DISH_OFFSETX = -1, //respecto de bubble
		DISH_OFFSETY = -5,
		DISH_WIDTH = 32,
		DISH_HEIGHT = 32
		;
	struct CookingTex {
		Texture* bubble = nullptr;
		Texture* dishTex = nullptr;
		Texture* cookingTex = nullptr;
	};

	CookingTex textures;
	State state;
	DishCombinator* dishComb; //solo existe uno en todo el juego
	_ecs::_dish_id dish; // plato que lleva cocinando,none si no hay
	float cookingTime; //tiempo de cocci¨®n del plato

	Vector renderPos;
	SDLUtils* sdl;
	Uint32 cont; //contador para cocinar

	Transform* transform; //puede que posteriormente no sea necesario...
	Animator* anim;

	//ha terminado de cocinar el plato
	void finishCooking();

public:
	CookingMachineComp(GameObject* parent);

	//consultar el plato que tiene
	_ecs::_dish_id getDish() { return dish; }

	State getState() { return state; };

	//informar si se puede formar un plato y qu¨¦ plato es
	pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id> ing);

	//cocinar un plato
	void cook(_ecs::_dish_id d);

	//recoger el plato
	_ecs::_dish_id pickDish();

	virtual void update(); //para cocinar
	virtual void render();
};

