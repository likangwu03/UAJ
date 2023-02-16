#pragma once
#include "../structure/Component.h"
#include "../structure/DishCombinator.h"
#include "../sdlutils/SDLUtils.h"
#include "../utilities/Vector.h"
class CookingMachineComp:public Component
{
public:
	//determinar si el horno est¨¢ libre, cocinando o que ha cocinado un plato
	enum State { available, cooking, finished };
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COOKMACHINE;
private:
	struct CookingTex {
		Texture* bubble=nullptr;
		Texture* dishTex= nullptr;
		Texture* cookingTex= nullptr;
	};
	CookingTex textures;
	State state;
	DishCombinator* dishComb; //solo existe uno en todo el juego
	_ecs::_dish_id dish; // plato que lleva cocinando,none si no hay
	Uint32 cookingTime; //tiempo de cocci¨®n del plato
	
	Vector renderPos;
	SDLUtils* sdl;
	Uint32 cont; //contador para cocinar

	//ha terminado de cocinar el plato
	void finishCooking();

public:
	CookingMachineComp(GameObject* parent,Vector pos);

	//consultar el plato que tiene
	_ecs::_dish_id getDish() { return dish; }

	State getState() { return state; };

	//informar si se puede formar un plato y qu¨¦ plato es
	pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id> ing);
	//pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id>ing); (VERSION ANTIGUA)

	//cocinar un plato
	void cook(_ecs::_dish_id d);

	//recoger el plato
	_ecs::_dish_id pickDish();

	virtual void update(); //para cocinar
	virtual void render(); 
};

