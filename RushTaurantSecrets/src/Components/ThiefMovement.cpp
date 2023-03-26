#include "./ThiefMovement.h"
#include "../Utilities/checkML.h"
#include "../Structure/Scene.h"

void ThiefMovement::addPath(const vector<Vector>& points) {
	straightMovement->addPath(RelativeToGlobal::pointsPantry(points));
}

ThiefMovement::ThiefMovement(GameObject* parent, int pos, float escapeSpeed) :
	Component(parent, id), escapeSpeed(escapeSpeed) {
	straightMovement = parent->getComponent<StraightMovement>();
	transform = parent->getComponent<Transform>();
	thiefState = parent->getComponent<ThiefState>();
	sdl = SDLUtils::instance();

	// se mueve el ladrón
	_ecs::_path_thief_id id = _ecs::enumThiefsPaths[thiefState->getState()][pos];
	addPath(_ecs::thiefsPahts[id].points);
}

void ThiefMovement::die() {
	thiefState->setState(ThiefState::DEAD);
	straightMovement->stop();
	// se cambia a muerto (se pone rojo el sprite y se tumba el sprite)
	transform->setMovState(dead);
	// corregir la posición de muerte
	straightMovement->setActive(false);
	Vector pos = transform->getPos();
	transform->setPos(Vector(pos.getX(), pos.getY() + transform->getW() / 2));
}

void ThiefMovement::escape() {
	thiefState->setState(ThiefState::ESCAPE);
	straightMovement->goBack();
	straightMovement->changeSpeed(escapeSpeed);
}

void ThiefMovement::update() {
	switch (thiefState->getState()) {
	case ThiefState::OBJECTIVE_SECRET:
	case ThiefState::OBJECTIVE_FREEZER:
		if (straightMovement->hasFinishedPath()) {
			thiefState->hasReachObjective();
		}
		break;

	case ThiefState::ESCAPE:
		if (straightMovement->hasFinishedPath()) {
			parent->setAlive(false);
		}
		break;
	}
}