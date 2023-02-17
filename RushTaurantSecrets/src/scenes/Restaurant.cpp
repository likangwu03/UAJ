#include "Restaurant.h"
#include "Pantry.h"
#include "../structure/SceneManager.h"
#include "../components/CookingMachineComp.h"

void Restaurant::linkPantry(Pantry* pantry) {
	this->pantry = pantry;
}

void Restaurant::render() {
	Scene::render();
	if (ui != nullptr)
	ui->render();
}

void Restaurant::update() {
	Scene::update();
	if(pantry!=nullptr)
	pantry->Scene::update();
	ui->update();
}

void Restaurant::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->ChangeScene(SceneManager::PANTRY);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->ChangeScene(SceneManager::MAINMENU);
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}

}
void Restaurant::init() {
	new Player(this);

	/* prueba, luego se borra
	vector<_ecs::_ingredients_id> ing = { _ecs::HARINA,QUESO,HUEVO };
	auto aux1=new CookingMachine(this);
	setHandler(_ecs::hdr_PLAYER, aux1);
	pair<_ecs::_dish_id, bool> aux = getHandler(_ecs::hdr_PLAYER)->getComponent<CookingMachineComp>()->canFormDish(ing);
	cout << (int)aux.first << endl;
	*/

	// objetos interactuables
	Bin* bin = new Bin(this, Vector(200, 200));
	// icono temporal, cambiar cuando se haya implementado la animación de la papelera
	new Image(bin, &((*sdl).images().at("MONEY_ICON")));
}