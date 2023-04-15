#include "FreezerComp.h"
#include "../Structure/GameObject.h"
#include "../Utilities/checkML.h"

FreezerComp::FreezerComp(GameObject* _parent) : Component(_parent, id),
image(parent->getComponent<Image>()), gameInfo(GameManager::get())
{
	textures.open1 = &sdlutils().images().at("FREEZER_OPEN");
	textures.close2 = &sdlutils().images().at("FREEZER2_CLOSE");
	textures.open2 = &sdlutils().images().at("FREEZER2_OPEN");
	if (gameInfo->getHasKill()) {
		isClosedWhenKilled();
	}
	else image->setActive(false);

};

void FreezerComp::nextDay() {
	if (gameInfo->getHasKill()) {
		isClosedWhenKilled();
	}
	else image->setActive(false);
}

void FreezerComp::isOpen() {
	image->setActive(true);
	image->setTexture(textures.open1);
}
void FreezerComp::isClosedWhenKilled() {
	image->setActive(true);
	image->setTexture(textures.close2);
}
void FreezerComp::isOpenWhenKilled() {
	image->setActive(true);
	image->setTexture(textures.open2);
}