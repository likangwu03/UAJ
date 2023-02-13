#pragma once

#include "../structure/Structure_def.h"
#include <deque>

class Scene;
class GameObject;
class Vector;
class SDLUtils;

using namespace std;

class CostumerManager {
private:
	Scene* scene = nullptr;	// puntero a la escena que pertenece
	SDLUtils* sdl = nullptr;
	deque<GameObject*> entrada;	// cola con la entrada
	int offset = 0;	// offset para que los clientes que vengan a continuación se coloquen detrás

	void createCustomer(Vector origin, Vector end);

	void deleteFirstCustomer();

	void recolocate();

public:
	CostumerManager(Scene* scene);

	void addCustomerFrequently();
};