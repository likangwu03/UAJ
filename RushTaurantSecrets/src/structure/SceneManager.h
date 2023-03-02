#pragma once
#include "../utils/Singleton.h"
#include <list>
#include "Scene.h"
#include "../scenes/MainMenu.h"
#include "../scenes/Pantry.h"
#include "../scenes/Restaurant.h"
#include "../scenes/UIRestaurant.h"
#include "../scenes/SuperMarket.h"
#include "../scenes/UIMarket.h"
#include "../scenes/DailyMenuScene.h"
#include "../scenes/PauseMenu.h"


using namespace std;
class SceneManager:public Singleton<SceneManager> {
	friend Singleton<SceneManager>;
public:
	const float PANTRYSIZE = 0.8333333333;
	const float GENERALSIZE = 0.6666666667;
	//enum SceneName{MAINMENU,RESTAURANT,PANTRY,DAILYMENU,SUPERMARKET,PAUSEMENU};
private:
	//crea menu
	SceneManager();
	//lista de escenas que vamos a usar
	list<Scene*> Scenes;
	//escenas que estar activa (jugador)
	Scene* currentScene;
	int nSceceToPop;
public:
	SceneManager(SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;
	~SceneManager() { clear(); }
	void update();
	void handleEvents();
	void render();
	void refresh();
	void changeScene(Scene* _scene, int nPop=0);
	void setResize(bool type=true);

private:
	void setScene();
	void clear();
	void popScene(int n=1);
	void pushScene(Scene* scene);
};