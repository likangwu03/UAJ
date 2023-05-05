#include "ThievesManager.h"
#include "DayManager.h"
#include "../Structure/Game.h"

#include "../Utilities/checkML.h"


void ThievesManager::createThief(int sprite, int pos) {
	string spriteStr = "Thief_" + to_string(sprite);

	// posición de cada ladrón respecto de la puerta
	Vector aux = _ecs::DOOR;
	aux.setY(_ecs::DOOR.getY() - pos);

	new Thief(scene, RelativeToGlobal::pointPantry(aux), spriteStr, generalSpeed, escapeSpeed, canGetFreezer, pos);

	warningSound->play(-1);
	played = true;

}

void ThievesManager::addFrequently() {
	if (thiefs->size() <= 0 && GameManager::get()->getDayManager()->getDay() > 1 && clock->getRotation() >= INITDELAY) {
		if (played) {
			played = false;
			warningSound->haltChannel();
		}
		elapsedTime += deltaTime;
		if (elapsedTime > timer * 1000) {
			elapsedTime = 0;
			timer = sdl->rand().nextInt(minFrec, maxFrec);
			allFalse();
			int auxNum = sdl->rand().nextInt(2, numThiefs + 1);
			Message m(Message::msg_THIEF_SPAWN);
			m.thief_spawn.number = auxNum;
			for (int i = 0; i < auxNum; ++i) {
				uint8_t sprite = sdl->rand().nextInt(1, 9), pos = randomPos();
				createThief(sprite, pos);
				m.thief_spawn.skins.push_back(sprite);
				m.thief_spawn.positions.push_back(pos);
			}
			Game::get()->getCoopHandler()->send(m);
		}
	}
}

int ThievesManager::randomPos() {
	// posición random
	int pos = sdl->rand().nextInt(0, _ecs::MAX_THIEFS);
	// se comprueba si esa posición est?ocupada y si lo est? se coge la siguiente
	while (selectedPosition[pos]) {
		pos = (pos + 1) % _ecs::MAX_THIEFS;
	}
	selectedPosition[pos] = true;

	return pos;
}

ThievesManager::ThievesManager(GameObject* parent, float generalSpeed, float escapeSpeed, bool canGetFreezer, int numThiefs, float min, float max) :
	Manager(parent), sdl(SDLUtils::instance()), warningSound(&sdl->soundEffects().at("ALERT")), played(false),
	generalSpeed(generalSpeed), escapeSpeed(escapeSpeed), canGetFreezer(canGetFreezer), thiefInteractWith(nullptr),
	minFrec(0), maxFrec(5), numThiefs(numThiefs), elapsedTime(0), selectedPosition() {
	scene = parent->getScene();
	thiefs = scene->getGroup(_ecs::grp_THIEFS);
	timer = sdl->rand().nextInt(minFrec, maxFrec);
	warningSound->setVolume(30);
}

vector<GameObject*> ThievesManager::canInteractWith() {
	vector<GameObject*> thievesCanInteract;
	thievesCanInteract.reserve(_ecs::MAX_THIEFS);

	// vector con los ladrones con los que puede interactuar
	// son los que están de camino al congelador o a la fórmula secreta
	// y con los que est?haciendo overlap
	for (auto thief : *thiefs) {
		ThiefState* thiefState = thief->getComponent<ThiefState>();
		ThiefTrigger* thiefTrigger = thief->getComponent<ThiefTrigger>();
		ThiefState::States currentState = thiefState->getState();
		if ((currentState == ThiefState::OBJECTIVE_FREEZER || currentState == ThiefState::OBJECTIVE_SECRET)
			&& thiefTrigger->IsOverLap()) {
			thievesCanInteract.push_back(thief);
		}
	}

	return thievesCanInteract;
}

void ThievesManager::update() {
	addFrequently();
}

void ThievesManager::haltSound() {
	warningSound->haltChannel();
}

void ThievesManager::pauseSound() {
	warningSound->pauseChannel();
}

void ThievesManager::resumeSound() {
	warningSound->resumeChannel();
}

void ThievesManager::nextDay() {
	clock = ClockComponent::get();

	haltSound();
	for (auto t : *thiefs) {
		t->setAlive(false);
	}

	minFrec = GameManager::get()->getDayManager()->getMinThiefFrequency();
	maxFrec = GameManager::get()->getDayManager()->getMaxThiefFrequency();
}

void ThievesManager::receive(const Message& message) {
	if(message.id == Message::msg_THIEF_SPAWN) {
		for(int i = 0; i < message.thief_spawn.number; i++) {
			createThief(message.thief_spawn.skins[i], message.thief_spawn.positions[i]);
		}
	} else if(message.id == Message::msg_THIEF_INTERACT) {
		thiefs->operator[](message.thief_interact.id)->getComponent<ThiefTrigger>()->escapeOrDie(message.thief_interact.escape);
	}
}

void ThievesManager::send(GameObject* thief, Message& m) {
	int i = 0; bool found = false;
	// Finds thief
	for(auto t : *thiefs) {
		if(t == thief) {
			found = true; break;
		}
		else i++;
	}
	if(found) {
		m.thief_interact.id = i;
		Game::get()->getCoopHandler()->send(m);
	}
}