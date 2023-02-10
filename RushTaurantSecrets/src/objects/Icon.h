#pragma once
#include "../structure/GameObject.h"
#include "../scenes/UI.h"

// iconos que aparecen en la UI
class Icon : public GameObject
{
public:
	Icon(UI* thisUI) : GameObject(thisUI) {}
};