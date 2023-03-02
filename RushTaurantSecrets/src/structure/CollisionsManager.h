#pragma once
#include <vector>
#include <SDL_rect.h>
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

public:
	CollisionsManager(Scene* scene);
	void update();
private:
	void collision();
	void overlap();
};