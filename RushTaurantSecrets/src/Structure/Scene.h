#pragma once
#include <vector>
#include <array>
#include <list>
#include <string>
#include "../Definitions/Structure_def.h"

class GameObject;
class GameManager;
class InputHandler;
class Vector;

using namespace _ecs;

class Scene {
private:
	friend class GameObject;
	void addObject(GameObject* object, _ecs::_grp_id grp, _ecs::_hdr_id handler);
	//render
	std::list<GameObject*> renderListTop;
	std::list<GameObject*> renderListMiddle;
	std::list<GameObject*> renderListDown;

protected:

	enum DPAD_XBOX { UP, DOWN, RIGHT, LEFT };

	InputHandler* ih;
	std::array<std::vector<GameObject*>, _ecs::grpNum> objGroups;


	// se utiliza para conectar objetos de una misma escena
	std::array<GameObject*, _ecs::hdrNum> handlers;
	Scene();
	void SortList(std::list<GameObject*>& v);
	void createMap(std::string file, RenderPos Rpos, Vector pos);

public:
	virtual ~Scene();

	const uint32_t& frameTime;

	virtual void refresh();
	inline std::vector<GameObject*>* getGroup(_ecs::_grp_id grp) { return &objGroups[grp]; }
	inline GameObject* getGameObject(_ecs::_hdr_id handler) { return handlers[handler]; }

	virtual void initComponent();
	virtual void update();
	virtual void render();
	virtual void handleEvents();
	virtual void nextDay();
	virtual void finishScene(){};

	void initRender();
	virtual void renderLayer();
	void pushRenderList(RenderPos pos, GameObject* obj);

	virtual void callAfterCreating() {};
	virtual void reset() {};
	virtual float getResizeFactor() { return 1; };
};