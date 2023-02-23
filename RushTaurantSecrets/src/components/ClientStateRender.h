#pragma once
#include "Transform.h"
#include "UIAnimator.h"
#include "../structure/Food_def.h"
#include "../structure/Component.h"
#include "../sdlutils/SDLUtils.h"

using namespace std;
using namespace _ecs;
class ClientState;
/*renderiza el estado del cliente*/
class ClientStateRender :public Component
{
private:
	const int
#pragma region para la nube de plato que quiere
		BUBBLE_OFFSETX = -4,
		BUBBLE_OFFSETY = -7,
		BUBBLE_WIDTH = 41,
		BUBBLE_HEIGHT = 40,
		DISH_OFFSETX = -1, //respecto de bubble
		DISH_OFFSETY = -3,
		DISH_WIDTH = 32,
		DISH_HEIGHT = 32,
#pragma endregion
		TAKINGNOTE_WIDTH = 48,
		TAKINGNOTE_OFFSETY = -5;
		

#pragma region todas las texturas que necesiten
	struct OrderedDishTex {
		Texture* bubble = nullptr;
		Texture* dish = nullptr;
		Texture* thinking = nullptr;
		Texture* takingNote = nullptr;
	};

	OrderedDishTex textures;
#pragma endregion

	Transform* transform; //puede que posteriormente no sea necesario...
	UIAnimator* anim;
	ClientState* state;
	SDLUtils* sdl;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENTSTATE_RENDER;
	ClientStateRender(GameObject* parent);
	
	
	virtual void render();
	
	//llamado por ClientMovement
	void renderThinkingState(); //muestra que est¨¢ pensando
	//llamados por ClientState
	void renderTakingNoteState(); //informa de que quiere pedir algo
	void renderOrderingState(); //esperando su plato
	void renderEatingState(); //comiendo

	void clientStateIsReady();

};

