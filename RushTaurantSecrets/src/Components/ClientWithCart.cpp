#include "ClientWithCart.h"
#include "../Utilities/checkML.h"

 void ClientWithCart::setAnim(Animation& anim, int row, int initCol, int endCol) {
	anim.row = row;
	anim.initCol = initCol;
	anim.endCol = endCol;
	anim.actCol = initCol;
	anim.elapsedTime = 0;
}

 void ClientWithCart::renderAnim(Animation anim, Vector pos, int width, int height) {
	 SDL_Rect dest;
	 dest.x = pos.getX();
	 dest.y = pos.getY();
	 dest.w = width * sdl->getResizeFactor();
	 dest.h = height * sdl->getResizeFactor();
	 anim.texture->renderFrame(dest, anim.actCol, anim.row, 0);
 }

 void ClientWithCart::updateAnim(Animation& anim) {
	 anim.elapsedTime += deltaTime / 10;
	 if (anim.elapsedTime > anim.frameRate) {
		 anim.elapsedTime = 0;

		 ++anim.actCol;
		 if (anim.actCol > anim.endCol) {
			 anim.actCol = anim.initCol;
		 }
	 }
 }

 void ClientWithCart::changeDirection() {
	 GOOrientation newOrientation = transform->getOrientation();
	 if (newOrientation != oldOrientation) {
		 setDirection(newOrientation);
		 oldOrientation = newOrientation;
	 }
 }

 void ClientWithCart::setDirection(GOOrientation orientation) {
	 switch (orientation) {
	 case east:
		 offset = Vector(transform->getW() + nearEast, transform->getH() / 5.5);
		 setAnim(cart, 0, 0, 2);
		 setAnim(client, 8, 0, 5);
		 break;

	 case west:
		 offset = Vector(-widthCart + nearWest, transform->getH() / 5.5);
		 setAnim(cart, 0, 6, 8);
		 setAnim(client, 8, 12, 17);
		 break;

	 case north:
		 offset = Vector(-transform->getW() / 3, -heightCart + nearNorth);
		 setAnim(cart, 0, 3, 5);
		 setAnim(client, 8, 6, 11);
		 break;

	 case south:
		 offset = Vector(-transform->getW() / 1.6, transform->getH() + nearSouth);
		 setAnim(cart, 0, 9, 11);
		 setAnim(client, 8, 18, 23);
		 break;
	 }
 }

 ClientWithCart::ClientWithCart(GameObject* parent, string sprite) : Component(parent, id), offset(),
	 nearEast(-23), nearWest(41), nearNorth(100), nearSouth(-60),
	 oldOrientation(none), changeToIdle(false), changeToPhone(false) {

	 sdl = SDLUtils::instance();

	 transform = parent->getComponent<Transform>();
	 straightMovement = parent->getComponent<StraightMovement>();
	 client = { nullptr, 0 ,0, 0, 0, 0, FRAME_RATE };
	 int aux = sdl->rand().nextInt(1, 15);
	 client.texture = &sdl->images().at(sprite);

	 cart = { nullptr, 0 ,0, 0, 0, 0, FRAME_RATE };
	 cart.elapsedTime = sdl->currRealTime();
	 cart.texture = &sdl->images().at("SHOPPING_CART");
	 widthCart = transform->getW() * 2;
	 heightCart = transform->getH();

	 oldOrientation = transform->getOrientation();
	 setDirection(oldOrientation);
 }

 void ClientWithCart::update() {
	 if (transform->getMovState() == pushing) {
		 // después de estar parado, si vuelve a caminar en la misma orientación
		 // hay que forzar a que se cambie la dirección
		 if (changeToIdle || changeToPhone) {
			 changeToIdle = changeToPhone = false;
			 setDirection(oldOrientation);
		 }
		 changeDirection();
	 }
	 else if (transform->getMovState() == idle) {
		 // se cambia solo una vez la animación a idle del personaje y se para el carrito
		 if (!changeToIdle) {
			 changeToIdle = true;
			 setAnim(cart, 0, cart.initCol, cart.initCol);
			 setAnim(client, 1, 18, 23);
		 }
	 }
	 else if (transform->getMovState() == phone) {
		 // se cambia solo una vez la animación a idle del personaje y se para el carrito
		 if (!changeToPhone) {
			 changeToPhone = true;
			 setAnim(cart, 0, cart.initCol, cart.initCol);
			 setAnim(client, 6, 3, 8);
		 }
	 }

	 updateAnim(cart);

	 updateAnim(client);
 }

 void ClientWithCart::render() {
	 if (oldOrientation == east || oldOrientation == west || oldOrientation == north) {
		 renderAnim(cart, transform->getPos() + offset, widthCart, heightCart);
		 renderAnim(client, transform->getPos(), transform->getW(), transform->getH());
	 }
	 else if (oldOrientation == south) {
		 renderAnim(client, transform->getPos(), transform->getW(), transform->getH());
		 renderAnim(cart, transform->getPos() + offset, widthCart, heightCart);
	 }
 }
