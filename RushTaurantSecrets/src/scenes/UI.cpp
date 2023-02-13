#include "UI.h"

UI::UI() : Scene() {
	// se añaden los iconos a la lista de gameObjects
	// icono de dinero
	objects.push_back(new Icon(this, 10, 50, texturesUI[0]));
	// icono del menú de pausa
	// CAMBIAR (poner ancho de la ventana - 50)
	objects.push_back(new Icon(this, 100, 10, texturesUI[1]));
	// icono del menú del día
	// CAMBIAR (poner ancho de la ventana - 50 y alto de la ventana - 50)
	objects.push_back(new Icon(this, 10, 10, texturesUI[2]));

	// cambiar por un getter para obtener el dinero
	money = 0;

	moneyText = (char*)money;

	r = 253; g = 216; b = 112; a = 255;

	// renderizado de dinero actual
	// moneyFont->renderText(moneyText, SDL_Color(r, g, b, a)); // da error ?¿
}

void UI::textures() {
	for (int i = 0; i < NUM_UI_TEXT; ++i) {
		const TextureDescription& desc = TEXT_DESCRIPT[i];
		texturesUI[i] = new Texture(renderer, desc.filename);
	}
}

	// se pintan cuando se llama al render de todos los GameObjects