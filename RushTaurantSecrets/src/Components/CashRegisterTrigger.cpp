#include "CashRegisterTrigger.h"
#include "../Structure/GameManager.h"
#include "../Managers/Reputation.h"
#include "../Utilities/SoundEffect.h"
#include "../Utilities/checkML.h"
#include "../Structure/Game.h"

CashRegisterTrigger::CashRegisterTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_), money(GameManager::get()->getMoney()),
	cM(ClientsManager::get()), highlight(parent->getComponent<Image>()),
	addSound(&sdlutils().soundEffects().at("GAIN_REPUTATION")),
	tipSound(&sdlutils().soundEffects().at("TIP")),
	cashSound1(&sdlutils().soundEffects().at("CASH_REGISTER1")),
	cashSound2(&(sdlutils().soundEffects().at("CASH_REGISTER2"))) {
	cashSound1->setVolume(10);
	cashSound2->setVolume(7);
	highlight->setActive(false);
	list = cM->getPayQueue();
	streak = GameManager::get()->getRestaurant()->getUI()->getGameObject(_ecs::hdr_STREAK)->getComponent<Streak>();

	tipped = false;
	font = new Font(FONT_PATH, FONTSIZE);
	tipTexture = bgTexture = nullptr;

}

CashRegisterTrigger::~CashRegisterTrigger() {
	delete font;
	if (tipTexture != nullptr) delete tipTexture;
	if (bgTexture != nullptr) delete bgTexture;

}

void CashRegisterTrigger::isOverlapping() {
	if (other_->getComponent<Transform>()->getOrientation() != south) {
		highlight->setActive(false); return;
	};
	highlight->setActive(true);
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada

	charge();

}

void CashRegisterTrigger::charge() {
	if (cM->canCollect()) {
		int totalPayment = 0;

		// SONIDO CAJA REGISTRADORA
		cashSound1->setVolume(GameManager::instance()->getSoundEffectsVolume());
		cashSound2->setVolume(GameManager::instance()->getSoundEffectsVolume());
		if (sdlutils().rand().nextInt(0, 2) == 0) cashSound1->play(0);
		else cashSound2->play(0);

		// AÑADIR DINERO Y REPUTACIÓN
		for (auto it : *list) {
			_ecs::_dish_id id = it->getComponent<ClientState>()->getOrderedDish();
			int price = _ecs::Dishes[id].price;
			totalPayment += price;
			money->addMoney(price);
			GameManager::get()->getReputation()->addReputatiton(it->getComponent<ClientState>()->getHappiness() / 100);
			addSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
			addSound->play(0);
		}

		// PROPINAS
		int tip = 0;
		int rep = GameManager::get()->getReputation()->getReputation() / 20;
		if (rep >= sdlutils().rand().nextInt(0, 5)) {
			tip = totalPayment / 10;
			money->addMoney(tip);
			tipSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
			tipSound->play(0);
#ifdef _DEBUG
			cout << "You got " << totalPayment / 10 << " coins from tips" << endl;
#endif
			delete tipTexture;
			tipTexture = new Texture(sdlutils().renderer(), "+" + to_string(tip), *font, build_sdlcolor(0x129008FF));
			bgTexture = new Texture(sdlutils().renderer(), "+" + to_string(tip), *font, build_sdlcolor(0x054400FF));
			currRect = bgRect = INITRECT;
			currRect.w = bgRect.w = tipTexture->width();
			currRect.h = bgRect.h = tipTexture->height();
			bgRect.x += OUT_OFFSET;
			bgRect.y += OUT_OFFSET;
			tipped = true;
		}


		// RACHA
		money->addMoney(streak->getMoneyStreak() * list->size());
		streak->setStreak(list->size());

		// CLIENTES ABANDONAN CAJA
		cM->collectAndLeave();


		Message m;
		m.id = Message::msg_CHARGE;
		m.charge.money = money->getMoney();
		m.charge.rep = GameManager::get()->getReputation()->getReputation();
		m.charge.tip = tip;
		Game::get()->getCoopHandler()->send(m);

	}
}

void CashRegisterTrigger::charge(float rep, int m,int tip) {

	cashSound1->setVolume(GameManager::instance()->getSoundEffectsVolume());
	cashSound2->setVolume(GameManager::instance()->getSoundEffectsVolume());
	if (sdlutils().rand().nextInt(0, 2) == 0) cashSound1->play(0);
	else cashSound2->play(0);

	for (auto it : *list) {
		addSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		addSound->play(0);
	}

	// PROPINAS
	if (tip > 0) {
		tipSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		tipSound->play(0);
		delete tipTexture;
		tipTexture = new Texture(sdlutils().renderer(), "+" + to_string(tip), *font, build_sdlcolor(0x129008FF));
		bgTexture = new Texture(sdlutils().renderer(), "+" + to_string(tip), *font, build_sdlcolor(0x054400FF));
		currRect = bgRect = INITRECT;
		currRect.w = bgRect.w = tipTexture->width();
		currRect.h = bgRect.h = tipTexture->height();
		bgRect.x += OUT_OFFSET;
		bgRect.y += OUT_OFFSET;
		tipped = true;
	}
	GameManager::get()->getReputation()->addReputatiton(rep- GameManager::get()->getReputation()->getReputation());
	money->addMoney(m-money->getMoney());

	streak->setStreak(list->size());
	// CLIENTES ABANDONAN CAJA
	cM->collectAndLeave();
}
void CashRegisterTrigger::onTriggerExit() {
	highlight->setActive(false);
}


void CashRegisterTrigger::render() {
	if (tipped) {
		if (currRect.y <= ENDY) tipped = false;
		else {
			currRect.y -= MOVEMENT;
			bgRect.y -= MOVEMENT;
			bgTexture->render(bgRect);
			tipTexture->render(currRect);
		}
	}

}

void CashRegisterTrigger::receive(const Message& message) {
	if (message.id == Message::msg_CHARGE) {
		charge(message.charge.rep, message.charge.money, message.charge.tip);
	}
}