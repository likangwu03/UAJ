#pragma once
#include "../structure/Component.h"
#include "../structure/GameObject.h"
#include "../structure/Scene.h"
#include "../utilities/Vector.h"
#include "../sdlutils/InputHandler.h"
#include "InventoryComp.h"

class BinComponent : public Component
{
	private:
	InputHandler* ih; //para consultar el input (teclado 123 o mando)
	GameObject* myParent;
	InventoryComp* myInventory;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BIN;
	BinComponent(GameObject* parent, Vector pos);
	virtual void handleEvents();
};