#pragma once

#include "../Structure/Component.h"
#include "../Managers/DishCombinator.h"
#include "UIAnimator.h"
#include "Transform.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/Vector.h"


class CookingMachineComp :public Component {
public:
	//determinar si el horno está libre, cocinando o que ha cocinado un plato
	enum State { available, informing, cooking, finished };
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COOKMACHINE;

private:
	const float 
		BUBBLE_OFFSETX = -4,
		BUBBLE_OFFSETY = -47,
		BUBBLE_WIDTH = 35,
		BUBBLE_HEIGHT = 41,
		DISH_OFFSETX = -1, //respecto de bubble
		DISH_OFFSETY = -5,
		DISH_WIDTH = 24,
		DISH_HEIGHT = 24,
		CROSS_WIDTH = 32,
		CROSS_HEIGHT = 32 ;
		
		const float CROSS_TIME = 0.5;

	struct CookingTex {
		Texture* bubble = nullptr;
		Texture* dishTex = nullptr;
		Texture* cookingTex = nullptr;
		Texture* cross = nullptr;
	};

	CookingTex textures;
	State state;
	DishCombinator* dishComb; //solo existe uno en todo el juego
	_ecs::_dish_id dish; // plato que lleva cocinando,none si no hay
	float cookingTime; //tiempo de cocción del plato

	Vector renderPos;
	SDLUtils* sdl;
	Uint32 cont; //contador para cocinar

	Transform* transform; //puede que posteriormente no sea necesario...
	UIAnimator* anim;

	//ha terminado de cocinar el plato
	void finishCooking();

public:
	CookingMachineComp(GameObject* parent);

	//consultar el plato que tiene
	_ecs::_dish_id getDish() { return dish; }

	State getState() { return state; };

	//informar si se puede formar un plato y qué plato es
	pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id> ing);

	//cocinar un plato
	void cook(_ecs::_dish_id d);
	void informCannotCook();
	//recoger el plato
	_ecs::_dish_id pickDish();

	virtual void update(); //para cocinar
	virtual void render();

};

