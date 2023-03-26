#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/CartelTrigger.h"
#include "../Components/Image.h"
#include "../Definitions/Food_def.h"
using namespace std;
/*Cartel del supermercado*/
class Cartel1 :public GameObject
{
private:
	const int HIGH_OFFSETX = -1;
	const int HIGH_OFFSETY = 1;
	const int HIGH_OFFSETW = 3;
	const int HIGH_OFFSETH = -1;
public:
	Cartel1(Scene* scene, _ecs::_ingredients_id ingId, Vector pos, float w, float h, Vector triP, float triW, float triH) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, Vector(pos.getX() + HIGH_OFFSETX, pos.getY() + HIGH_OFFSETY), Vector(0, 0), w + HIGH_OFFSETW , h + HIGH_OFFSETH, 0, true); //renderizar el cartel
		new Image(this, "CARTEL_HIGHLIGHT"); //renderizar el highlight
		new CartelTrigger(this, ingId, triP - pos, w, h); //pos relativa
	};
};
class Cartel2 :public GameObject
{
private:
	const int HIGH_OFFSETX = -1;
	const int HIGH_OFFSETY = 1;
	const int HIGH_OFFSETW = 3;
	const int HIGH_OFFSETH = -1;
	const int OFFSET = 1000;
public:
	Cartel2(Scene* scene, _ecs::_ingredients_id ingId, Vector pos, float w, float h, Vector triP, float triW, float triH) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, Vector(pos.getX() + HIGH_OFFSETX, pos.getY() + HIGH_OFFSETY + OFFSET), Vector(0, 0), w + HIGH_OFFSETW, h + HIGH_OFFSETH, 0, true); //renderizar el cartel
		new Image(this, "CARTEL_HIGHLIGHT", Vector(0, -OFFSET)); //renderizar el highlight
		new CartelTrigger(this, ingId, triP - pos - Vector(0, OFFSET), w, h); //pos relativa
	};
};
class Cartel3 :public GameObject
{
private:
	const int HIGH_OFFSETX = -1;
	const int HIGH_OFFSETY = 1;
	const int HIGH_OFFSETW = 3;
	const int HIGH_OFFSETH = -1;
public:
	Cartel3(Scene* scene, _ecs::_ingredients_id ingId, Vector pos, float w, float h, Vector triP, float triW, float triH) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, Vector(pos.getX() + HIGH_OFFSETX, pos.getY() + HIGH_OFFSETY), Vector(0, 0), w + HIGH_OFFSETW, h + HIGH_OFFSETH, 0, true); //renderizar el cartel
		new Image(this, "CARTEL_HIGHLIGHT"); //renderizar el highlight
		new CartelTrigger(this, ingId, triP - pos, w, h); //pos relativa
		scene->pushRenderList(Top, this);
	};
};