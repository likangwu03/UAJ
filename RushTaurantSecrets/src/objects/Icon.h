#pragma once
#include "../structure/GameObject.h"
#include "../structure/Scene.h"
#include "../sdlutils/Texture.h"

// iconos que aparecen en la UI
class Icon : public GameObject
{
private:
	int posX, posY; // posición del icono
public:
	Icon(Scene* thisUI, int x, int y, Texture* texture) : GameObject(thisUI), posX(x), posY(y) {}
};