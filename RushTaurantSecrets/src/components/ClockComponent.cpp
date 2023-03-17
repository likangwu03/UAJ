#include "ClockComponent.h"

ClockComponent::ClockComponent(GameObject* parent, Scene* _scene) : Component(parent, id), scene(_scene) {
	lastTime = sdl->currRealTime();
	numFullClock = 0;

	// reloj (momento del día)
	createIcon("CLOCK", Vector(sdl->width() - ICONX - ICONSIZE * 2, ICONY), ICONSIZE * 2, ICONSIZE * 2, 0, grp_ICONS, hdr_CLOCK);

	// aguja del reloj
	arrow = createIcon("ARROW", Vector(sdl->width() - ICONX - ICONSIZE - 8, ICONY), ICONSIZE / 3, ICONSIZE, 0, grp_ICONS, hdr_ARROW);
}

// devuelve cuántas vueltas ha dado reloj cuando se llama al método
int ClockComponent::getNumFullClock() {
	return numFullClock;
}

void ClockComponent::updateClock() {
	timeT = sdl->currRealTime();
	if (timeT - lastTime >= TIME_CLOCK_REFRESH) {
		time += 1;
		auto transformArrow = arrow->getComponent<Transform>();
		transformArrow->setRot(transformArrow->getRot() + ANGLE_UPDATE);
		Vector posA;
		if (transformArrow->getRot() <= ANGLE)
			posA = transformArrow->getPos() + Vector(1, 1);
		else if (transformArrow->getRot() <= ANGLE * 2)
			posA = transformArrow->getPos() + Vector(-1, 1);
		else if (transformArrow->getRot() <= ANGLE * 3)
			posA = transformArrow->getPos() + Vector(-1, -1);
		else
			posA = transformArrow->getPos() + Vector(1, -1);
		transformArrow->setPos(posA);
		lastTime = timeT;
		timeT = 0;

		if (transformArrow->getRot() == 0) numFullClock++;
	}
}

GameObject* ClockComponent::createIcon(string textureName, Vector position, float width, float height, float rotation,
	_ecs::_grp_id grp, _ecs::_hdr_id handler) {

	return dataIcon(&((*sdl).images().at(textureName)), position, width, height, rotation, grp, handler);
}

GameObject* ClockComponent::dataIcon(Texture* texture, Vector position, float width, float height, float rotation,
	_ecs::_grp_id grp = _ecs::grp_GENERAL, _ecs::_hdr_id handler = _ecs::hdr_INVALID) {

	GameObject* gameObject = new GameObject(scene, grp, handler);
	new Transform(gameObject, position, Vector(0, 0), width, height, rotation);
	new Image(gameObject, texture);

	return gameObject;
}

void ClockComponent::update() {
	Component::update();
	updateClock();
}

void ClockComponent::render() {
	Component::render();
}