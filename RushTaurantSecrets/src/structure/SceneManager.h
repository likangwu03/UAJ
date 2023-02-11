#pragma once
#include "../utils/Singleton.h"
#include <list>
#include "Scene.h"
#include "../scenes/MainMenu.h"
#include "../scenes/Pantry.h"
#include "../scenes/Restaurant.h"

using namespace std;
class SceneManager:public Singleton<SceneManager> {
	friend Singleton<SceneManager>;
public:
	enum SceneName{MAINMENU,RESTAURANT,PANTRY,SUPERMARKET};
private:
	//crea menu
	SceneManager();
	//lista de escenas que vamos a usar
	list<Scene*> Scenes;
	//escenas que estar activa (jugador)
	Scene* currentScene;
	SceneName act;
	SceneName change;

public:
	~SceneManager() { clear(); }
	void update();
	void handleEvents();
	void render();
	void refresh();
	void ChangeScene(SceneName scene);
private:
	void setScene();
	void clear();
};