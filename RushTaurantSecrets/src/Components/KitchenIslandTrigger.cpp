#include "KitchenIslandTrigger.h"
#include "../Structure/Scene.h"
#include "../Utilities/checkML.h"

KitchenIslandTrigger::KitchenIslandTrigger(GameObject* parent, Vector pos_, float width_, float height_, int i_, int orient_) :
	TriggerComp(parent, pos_, width_, height_), i(i_), orient(orient_),
	ki(parent->getScene()->getGameObject(_ecs::hdr_KITCHENISLAND)->getComponent<KitchenIslandComp>()),
	p(parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()){}

void KitchenIslandTrigger::isOverlapping() {
	float aux = p->getPos().getX() + p->getW() / 2;
	if (p->getOrientation() != orient && aux > transform_->getPos().getX() && aux < transform_->getPos().getX() + width)
	{
		ki->selectedIng(i);

		if (ih->joysticksInitialised()) {
			if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return;
		}
		else if (!ih->isKeyDown(SDLK_SPACE)) return;
		ki->pickIngredient(i);
	}
	else if (p->getOrientation() == orient)ki->unselectIng(i);
}
void KitchenIslandTrigger::onTriggerExit() {
	ki->unselectIng(i);
}