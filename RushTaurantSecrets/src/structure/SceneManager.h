#pragma once
#include "../utils/Singleton.h"
#include <list>
#include "Scene.h"
using namespace std;
class SceneManager:public Singleton<SceneManager> {
public:
	enum SceneName{Menu,Restaurant,Panty,SuperMarket};
	//crea menu
	SceneManager() {};
private:
	
	list<Scene*> Scenes;

	//escenas que van a estar activa
	list<Scene*> currentScenes;

public:
	void update();
	void render();
	void handleEvents();
	void refresh();
	void ChangeScene();

};