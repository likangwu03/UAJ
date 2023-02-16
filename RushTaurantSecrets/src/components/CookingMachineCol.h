#pragma once
#include "../structure/Component.h"
#include "../gameObjects/Player.h"
#include "../components/CookingMachineComp.h"
/*gestiona la cocina cuando se colisiona con player*/
class CookingMachineCol :public Component
{
public:
	/*suponiendo que tiene un identificador de grupo: grp_COLLISION*/
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COOKMACHINE;
private:
	CookingMachineComp* cook;
public:
	CookingMachineCol(GameObject* parent) :Component(parent, id),cook(parent->getComponent<CookingMachineComp>()) {};
	//llamado por CollisionManager
	void collision(Player* p); // le pasa un puntero a player, pero no se lo guarda?

};

