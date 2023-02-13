#pragma once

#include "../structure/Structure_def.h"
#include <deque>

class Scene;
class GameObject;
class Vector;
class SDLUtils;

using namespace std;

class CustomerManager {
private:
	Scene* scene = nullptr;
	SDLUtils* sdl = nullptr;
	deque<GameObject*> entrada;
	int offset = 0;

	void createCustomer(Vector origin, Vector end);

	void deleteFirstCustomer();

	void recolocate();

public:
	CustomerManager(Scene* scene);

	void addCustomerFrequently();
};