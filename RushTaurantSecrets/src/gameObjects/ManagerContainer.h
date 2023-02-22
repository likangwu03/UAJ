#pragma once
#include "../objects/ClientsManager.h"
#include "../objects/ThiefsManager.h"
#include "../structure/GameObject.h"

class ManagerContainer : public GameObject {
public:
	ManagerContainer(Scene* scene, vector<_ecs::_dish_id> menu, float clientsFrequency, float clientsSpeed, int numClients,
		float thiefsSpeed, float thiefsEscapeSpeed, bool canGetFreezer, float thiefsFrequency) 
		: GameObject(scene) {
		// manager de clientes
		ClientsManager::init(this, menu, clientsFrequency * 1000, clientsSpeed, numClients);
		ThiefsManager::init(this, thiefsSpeed, thiefsEscapeSpeed, true, thiefsFrequency * 1000);
	}
};
