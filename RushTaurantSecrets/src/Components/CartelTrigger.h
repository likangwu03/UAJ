#pragma once
#include "../Structure/TriggerComp.h"
#include "../Structure/GameObject.h"
#include "../Definitions/Food_def.h"
class Image;
class CartelManager;
/*encargada de detectar la entrada del jugador*/
class CartelTrigger :public TriggerComp
{
public:
	CartelTrigger(GameObject* parent, _ecs::_ingredients_id id, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerEnter();
	virtual void onTriggerExit();
	void highlight(); //llamado por CartelManager
	void unHighlight(); //llamado por CartelManager
	
	_ecs::_ingredients_id getIngredient() { return ingId; }

private:
	_ecs::_ingredients_id ingId; //para saber qu¨¦ ingrediente est¨¢ seleccionando
	CartelManager* cartelManager;
	bool highlighted;
};

