#include "UIRestaurant.h"

UIRestaurant::UIRestaurant() : Scene() {
	// icono de reputación
	GameObject* reputation = new GameObject(this, _ecs::hdr_REPUTATION, _ecs::grp_ICONS);
	new Transform(reputation, Vector(20, 20), Vector(0, 0), 56, 36, 0);
	new Image(reputation, &((*sdl).images().at("REPUTATION_ICON")));

	// icono de dinero
	GameObject* money = new GameObject(this, _ecs::hdr_MONEY, _ecs::grp_ICONS);
	new Transform(money, Vector(20, 80), Vector(0, 0), 50, 50, 0);
	new Image(money, &((*sdl).images().at("MONEY_ICON")));

	// icono de objetivo diario
	GameObject* target = new GameObject(this, _ecs::hdr_TARGET, _ecs::grp_ICONS);
	new Transform(target, Vector(20, 150), Vector(0, 0), 50, 50, 0);
	new Image(target, &((*sdl).images().at("TARGET_ICON")));
}

void UIRestaurant::showMoneyText() {

}