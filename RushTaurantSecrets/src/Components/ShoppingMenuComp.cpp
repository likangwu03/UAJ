#include "ShoppingMenuComp.h"
#include "../Structure/Scene.h"
#include "../Scenes/HUD/UIMarket.h"
#include "../Structure/GameManager.h"
#include "../Scenes/GameScenes/SuperMarket.h"
#include "../Utilities/checkML.h"

ShoppingMenuComp::ShoppingMenuComp(GameObject* parent) :Component(parent, id),
sdl(SDLUtils::instance()), ih(InputHandler::instance()),
priceTex(nullptr), numberTex(nullptr), totalPriceTex(nullptr), ingTex(nullptr), ing(_ecs::NONE_ING),
menuSound(&sdl->soundEffects().at("OPEN_SHOPMENU")),
selectNum(&sdl->soundEffects().at("SELECT_NUM")),
addIng (&sdl->soundEffects().at("ADD_ING")),
confirmSound(&sdl->soundEffects().at("ADD_ING"))
{
	menuSound->setVolume(7);
	addIng->setVolume(100);
	menu = &((*sdl).images().at("SHOP_MENU"));
	font = new Font("assets/Fonts/8-bit Madness.ttf", 40);
	parent->setActive<ShoppingMenuComp>(false);
}

void ShoppingMenuComp::initComponent() {
	basket = parent->getScene()->getGameObject(hdr_SM_INVENTORY)->getComponent<BasketMarketComponent>();
	playerTransform = GameManager::get()->getSupermarket()->getGameObject(hdr_PLAYER)->getComponent<Transform>();
	showControl = new ShowControlAuto(parent,{{ControlsType::key_LEFT,ControlsType::play_LS,ControlsType::xbox_LS,Vector(-5,-5),40,40} ,{ControlsType::key_RIGHT,ControlsType::play_RS,ControlsType::xbox_RS,Vector(60,-5),40,40} ,{ControlsType::key_ENTER,ControlsType::play_Cross,ControlsType::xbox_A,Vector(145,-5),40,40}}, playerTransform);
}

ShoppingMenuComp::~ShoppingMenuComp() {
	delete font;
	if (numberTex != nullptr)
		delete numberTex;
	if (priceTex != nullptr)
		delete priceTex;
	if (totalPriceTex != nullptr)
		delete totalPriceTex;
}
void ShoppingMenuComp::handleEvents() {
	if (basket->getBasketON())return;
	if (ih->joysticksInitialised()) {
		if (ih->getXBox()){
			if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_BACK)) decreaseN();
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_GUIDE)) increaseN();
		}
		else if (!ih->getXBox()) {
			if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) decreaseN();
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) increaseN();
		}	
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B && ing != NONE_ING)) {
			addIng->setVolume(GameManager::instance()->getSoundEffectsVolume());
			addIng->play();
			basket->addToBasket(ing, number, totalPrice);
			closeMenu();
		}
	}
	else if (ih->isKeyDown(SDLK_LEFT)) decreaseN(); //aumentar cantidad
	else if (ih->isKeyDown(SDLK_RIGHT)) increaseN(); //disminuir cantidad
	else if (ih->isKeyDown(SDLK_RETURN) && ing != NONE_ING) { //añadir a la cesta
		basket->addToBasket(ing, number, totalPrice);
		confirmSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		confirmSound->play();
		closeMenu();
	}

}
void ShoppingMenuComp::render() {

	Vector menuPos = { playerTransform->getPos().getX() + playerTransform->getW() / 4 - MENU_WIDTH / 2,
						playerTransform->getPos().getY() + PLAYER_OFFSETY - MENU_HEIGHT };
	menu->render(build_sdlrect(menuPos.getX(), menuPos.getY(), MENU_WIDTH, MENU_HEIGHT));
	SDL_Rect quantRect = { menuPos.getX() + NUM_OFFSETX , menuPos.getY() + NUM_OFFSETY, numberTex->width(), numberTex->height() };
	if (number < 10) quantRect.x += numberTex->width() / 2;
	numberTex->render(quantRect);
	priceTex->render(build_sdlrect(menuPos.getX() + PRICE_OFFSETX, menuPos.getY() + PRICE_OFFSETY, priceTex->width(), priceTex->height()));
	totalPriceTex->render(build_sdlrect(menuPos.getX() + TOT_OFFSETX, menuPos.getY() + TOT_OFFSETY, totalPriceTex->width(), totalPriceTex->height()));
	ingTex->render(build_sdlrect(menuPos.getX() + ING_OFFSETX, menuPos.getY() + ING_OFFSETY, ING_WIDTH, ING_HEIGHT));

}
void  ShoppingMenuComp::increaseN() {
	if (number >= 99)return;
	++number;

	selectNum->setVolume(GameManager::instance()->getSoundEffectsVolume());
	selectNum->play();
	changePrice();
}
void  ShoppingMenuComp::decreaseN() {
	if (number <= 0)return;
	--number;

	selectNum->setVolume(GameManager::instance()->getSoundEffectsVolume());
	selectNum->play();
	changePrice();
}
void  ShoppingMenuComp::openMenu(_ecs::_ingredients_id _id) {
	if (basket->getBasketON())return;
	if (!active) {
		parent->setActive<ShoppingMenuComp>(true);
		ing = _id;
		number = 1;
		price = _ecs::MarketIngs[ing - FLOUR].price;
		totalPrice = number * price;
		numberTex = new Texture(sdl->renderer(), to_string(number), *font, build_sdlcolor(0xf3e5c2ff));
		priceTex = new Texture(sdl->renderer(), to_string(price), *font, build_sdlcolor(0x504631ff));
		ingTex = &((*sdl).images().at(to_string(ing)));
		changePrice();
		menuSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		menuSound->play();
		showControl->setActive(true);
	}
	else closeMenu();
}
void  ShoppingMenuComp::closeMenu() {
	if (active) {
		delete priceTex;
		priceTex = nullptr;
		delete numberTex;
		numberTex = nullptr;
		delete totalPriceTex;
		totalPriceTex = nullptr;
		parent->setActive<ShoppingMenuComp>(false);
		showControl->setActive(false);
	}
}
void  ShoppingMenuComp::changePrice() {
	totalPrice = number * price;
	delete numberTex;
	delete totalPriceTex;
	numberTex = new Texture(sdl->renderer(), to_string(number), *font, build_sdlcolor(0xf3e5c2ff));
	totalPriceTex = new Texture(sdl->renderer(), to_string(totalPrice), *font, build_sdlcolor(0x504631ff));
}