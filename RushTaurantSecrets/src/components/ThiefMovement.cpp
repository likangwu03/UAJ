#include "./ThiefMovement.h"
#include "../utils/checkML.h"
#include "../structure/Scene.h"

void ThiefMovement::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}

ThiefMovement::ThiefMovement(GameObject* parent, Objective objective, int pos, float escapeSpeed) :
	Component(parent, id), objective(objective), currentState(OBJECTIVE), deadTime(1 * 1000), elapsedTime(0), escapeSpeed(escapeSpeed) {
	straightMovement = parent->getComponent<StraightMovement>();
	transform = parent->getComponent<Transform>();
	sdl = SDLUtils::instance();
	freezer = parent->getScene()->getGameObject(_ecs::hdr_FREEZER)->getComponent<FreezerComp>();

	_ecs::_path_thief_id id = _ecs::enumThiefsPaths[objective][pos];
	addPath(_ecs::thiefsPahts[id].points);
}

void ThiefMovement::die() {
	currentState = DEAD;
	straightMovement->stop();
	// se cambia a muerto (se pone rojo el sprite y se tumba el sprite)
	transform->setMovState(dead);
	straightMovement->setActive(false);
	Vector pos = transform->getPos();
	transform->setPos(Vector(pos.getX(), pos.getY() + transform->getW() / 2));
}

void ThiefMovement::escape() {
	currentState = ESCAPE;
	straightMovement->goBack();
	straightMovement->changeSpeed(escapeSpeed);
}

void ThiefMovement::update() {
	float tick = 0;
	switch (currentState) {
	case OBJECTIVE:
		if (straightMovement->hasFinishedPath()) {
			switch (objective) {
			case Secret:
				currentState = SECRET;
			case Freezer:
				currentState = FREEZER;
				break;
			}
		}
		break;

	case SECRET:
		// se cambia a la escena en la que los ladrones han descubierto el secreto
		parent->setAlive(false);
		break;

	case FREEZER:
		// se cambia a la escena en la que los ladrones han abierto el congelador
		parent->setAlive(false);
		freezer->isOpen();
		break;

	case DEAD:
		elapsedTime += deltaTime;
		if (elapsedTime > deadTime) {
			parent->setAlive(false);
			elapsedTime = 0;	// no har�a falta
		}
		break;

	case ESCAPE:
		if (straightMovement->hasFinishedPath()) {
			parent->setAlive(false);
		}
		break;
	}
}
