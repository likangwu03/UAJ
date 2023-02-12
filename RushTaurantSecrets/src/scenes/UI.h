#pragma once
#include "../structure/Scene.h"
#include "../objects/Icon.h"
#include "../sdlutils/Texture.h"

class Icon;

using namespace std;
	
typedef struct {
	string filename; // nombre del archivo donde se encuentra la textura
	//int hframes, vframes; // número de filas y columnas de la textura
}TextureDescription;

const int NUM_UI_TEXT = 20;

// clase UI de la que heredan el resto de clases UI (UI del restaurante, del supermercado...)
// es una escena que se superpone a la escena que esté presente en el momento
class UI : public Scene
{
private:
	const TextureDescription TEXT_DESCRIPT[NUM_UI_TEXT] = {
		{"../../assets/UI/money_icon.png"}, {"../../assets/UI/pause_button.png"}, {"../../assets/UI/daily_menu.png"}
	};
	// iconos en común que aparecen en todas las UIs
	int money; // dinero del jugador
	Texture* texturesUI[NUM_UI_TEXT]; // CAMBIAR TAMAÑO
	SDL_Renderer* renderer;

public:
	UI();
	void textures();
};

