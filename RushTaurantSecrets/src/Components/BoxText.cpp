#include "BoxText.h"

void BoxText::enlargeBox() {
	// se aumenta el tamaño de al caja
	box.actWidth += box.proportionWidthHeight * increment;
	box.actHeight += increment;
	transform->setW(box.actWidth);
	transform->setH(box.actHeight);
	// se recoloca para que crezca desde el centro
	transform->setPos(Vector(box.centerPos.getX() - box.actWidth / 2,
		box.centerPos.getY() - box.actHeight / 2));
}

void BoxText::enlargeComplement(Complement& comp, Vector offset) {
	// se aumenta el tamaño
	comp.size.actWidth += (comp.size.proportionWidthHeight * increment) / comp.proportionBoxComplementH;
	comp.size.actHeight += increment / comp.proportionBoxComplementH;
	// se coloca en el centro
	// se hace cada iteración porque la posición
	// cambia en función de la caja y la caja se esta moviendo
	// hasta terminar de crecer
	comp.size.centerPos = transform->getPos() + offset;
	// se recoloca para que crezca desde el centro
	comp.pos = Vector(comp.size.centerPos.getX() - comp.size.actWidth / 2,
		comp.size.centerPos.getY() - comp.size.actHeight / 2);
}

void BoxText::initSize(Size& size, float width, float height) {
	size = { 0, 0, 0, 0, Vector::zero, 0 };

	size.desiredWidth = width;
	size.desiredHeight = height;
	size.proportionWidthHeight = size.desiredWidth / size.desiredHeight;
}

void BoxText::initComplement(Complement& complement, float width, float height) {
	complement.pos = Vector::zero;
	complement.proportionBoxComplementH = 0;

	initSize(complement.size, width, height);
	// proporción caja - complemento respecto a la altura
	complement.proportionBoxComplementH = box.desiredHeight / complement.size.desiredHeight;
}

BoxText::BoxText(GameObject* parent, Texture* portraitBorder, Texture* portrait, Vector offsetSize, int widthLetter, int heightLetter, Font* font, string name) :
	Component(parent, id), portraitBorderTexture(portraitBorder), portraitTexture(portrait),
	elapsedTime(0), timer(0.001), increment(17) {

	text = parent->getComponent<Text>();
	transform = parent->getComponent<Transform>();
	showControl = parent->getComponent<ShowControlComp>();

	// tamaño borde
	float wBorder = portraitBorderTexture->fwidth() - 15;
	float hBorder = portraitBorderTexture->fheight() - 15;
	// tamaño retrato
	float w = wBorder - 42;
	float h = hBorder - 42;

	// tamaños deseados de la caja
	initSize(box, text->getWidthTextBox() * offsetSize.getX(), text->getNumLines() * offsetSize.getY() + hBorder + 3 * heightLetter);
	// posición central de la caja
	// se hace para que el objeto crezca desde el centro
	// se coloca en su centro y se va aumentando y recolocando
	// hasta que alcanza el tamaño deseado
	box.centerPos = Vector(transform->getPos().getX() + box.desiredWidth / 2,
		transform->getPos().getY() + box.desiredHeight / 2);

	// tamaños deseados de la tecla
	initComplement(key, showControl->getTexture(0)->fwidth() * 5 / 1.4, showControl->getTexture(0)->fheight() * 5 / 1.4);
	showControl->changeHeight(key.size.actHeight, 0);

	// borde
	initComplement(this->portraitBorder, wBorder, hBorder);

	// retrato
	initComplement(this->portrait, w, h);

	// nombre
	initComplement(this->name, name.size() * widthLetter, heightLetter);
	nameTexture = new Texture(SDLUtils::instance()->renderer(), name, *font, build_sdlcolor(0x000000FF));
}

BoxText::BoxText(GameObject* parent, Texture* portraitBorder, Texture* portrait, Vector offsetSize) :
	Component(parent, id), portraitBorderTexture(portraitBorder), portraitTexture(portrait),
	elapsedTime(0), timer(0.001), increment(17), nameTexture(nullptr), name() {

	text = parent->getComponent<Text>();
	transform = parent->getComponent<Transform>();
	showControl = parent->getComponent<ShowControlComp>();

	// tamaño borde
	float wBorder = portraitBorderTexture->fwidth() - 15;
	float hBorder = portraitBorderTexture->fheight() - 15;
	// tamaño retrato
	float w = wBorder - 42;
	float h = hBorder - 42;

	// tamaños deseados de la caja
	initSize(box, text->getWidthTextBox() * offsetSize.getX(), text->getNumLines() * offsetSize.getY() + hBorder);
	// posición central de la caja
	// se hace para que el objeto crezca desde el centro
	// se coloca en su centro y se va aumentando y recolocando
	// hasta que alcanza el tamaño deseado
	box.centerPos = Vector(transform->getPos().getX() + box.desiredWidth / 2,
		transform->getPos().getY() + box.desiredHeight / 2);

	// tamaños deseados de la tecla
	initComplement(key, showControl->getTexture(0)->fwidth() * 5 / 1.4, showControl->getTexture(0)->fheight() * 5 / 1.4);
	showControl->changeHeight(key.size.actHeight, 0);

	// borde
	initComplement(this->portraitBorder, wBorder, hBorder);

	// retrato
	initComplement(this->portrait, w, h);
}

void BoxText::update() {
	if (!hasGrown()) {
		elapsedTime += deltaTime;
		if (elapsedTime > timer) {
			elapsedTime = 0;

			enlargeBox();

			enlargeComplement(key, Vector(3.3 * box.actWidth / 4, box.actHeight / 1.2));
			showControl->changeHeight(key.size.actHeight, 0);

			enlargeComplement(portraitBorder, Vector(box.actWidth / 10, box.actHeight / 2));

			enlargeComplement(portrait, Vector(box.actWidth / 10, box.actHeight / 2));

			if (nameTexture != nullptr) {
				// se coloca inicialmente en la posición del retrato
				enlargeComplement(name, Vector(box.actWidth / 10, box.actHeight / 2));
				// se sitúa justo debajo del retrato
				name.pos.setY(name.pos.getY() + 1.7 * portrait.size.actHeight / 2);
			}
		}
	}
}

void BoxText::render() {
	SDL_Rect dest;
	// render del marco
	dest.x = portraitBorder.pos.getX();
	dest.y = portraitBorder.pos.getY();
	dest.w = portraitBorder.size.actWidth;
	dest.h = portraitBorder.size.actHeight;
	portraitBorderTexture->render(dest);

	// render de la imagen
	dest.x = portrait.pos.getX();
	dest.y = portrait.pos.getY();
	dest.w = portrait.size.actWidth;
	dest.h = portrait.size.actHeight;
	portraitTexture->render(dest);

	if (nameTexture != nullptr) {
		// render del nombre
		dest.x = name.pos.getX();
		dest.y = name.pos.getY();
		dest.w = name.size.actWidth;
		dest.h = name.size.actHeight;
		nameTexture->render(dest);
	}

	dest.x = key.pos.getX();
	dest.y = key.pos.getY();
	dest.w = key.size.actWidth;
	dest.h = key.size.actHeight;
	for (auto c : *(showControl->getControls())) {
		c.texture->renderFrame(dest, c.col, c.row, 0);
	}
	// usando esto la animación del botón SPACE va mal
	// showControl->render(key.pos);
}