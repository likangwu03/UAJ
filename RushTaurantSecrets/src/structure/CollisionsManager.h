#pragma once
#include <vector>
#include <SDL_rect.h>
#include "../structure/GameObject.h"
#include "../components/CollisionComp.h"
#include "../components/TriggerComp.h"
#include "../components/Transform.h"
#include "../components/DeskComp.h"
using namespace std;
class Scene;
class GameObject;
class CollisionsManager {
private:
	Scene* scene_;
	vector<GameObject*>* grp_Player;
	vector<GameObject*>* grup_Collisions;
	vector<GameObject*>* grp_Clients;
	vector<GameObject*>* grp_Interactable;
	vector<GameObject*>* grp_Desk;
	vector<GameObject*>* grp_Thiefs;
public:
	CollisionsManager(Scene* scene);
	void update();
private:
	void collision();
	void overlap();
};