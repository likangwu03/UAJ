#pragma once

#include "../Structure/Component.h"
#include "../Structure/GameObject.h"
#include "Text.h"
#include "../Utilities/checkML.h"

struct Size {
	float desiredWidth;	// ancho al que tiene que llegar el objeto
	float desiredHeight;	// alto al que tiene que llegar el objeot
	float actWidth;		// ancho actual
	float actHeight;	// alto actual
	Vector centerPos;	// posición centrada del objeto
	// proporción ancho - alto
	// es decir, cuanto tiene que crecer el ancho respecto al alto
	// para que llegan a su máximo a la vez
	float proportionWidthHeight;
};

struct Complement {
	Size size;
	Vector pos;
	float proportionBoxComplementH;
};

class BoxText : public Component {
private:
	Text* text;
	Transform* transform;
	Texture* keysTexture;
	Texture* portraitBorderTexture;
	Texture* portraitTexture;
	float elapsedTime;
	float timer;
	float increment;
	Size box;
	Complement key;
	Complement portraitBorder;
	Complement portrait;

	void enlargeBox() {
		// se aumenta el tamaño de al caja
		box.actWidth += box.proportionWidthHeight * increment;
		box.actHeight += increment;
		transform->setW(box.actWidth);
		transform->setH(box.actHeight);
		// se recoloca para que crezca desde el centro
		transform->setPos(Vector(box.centerPos.getX() - box.actWidth / 2,
			box.centerPos.getY() - box.actHeight / 2));
	}

	void enlargeComplement(Complement& comp, Vector offset) {
		// se aumenta el tamaño
		comp.size.actWidth += (comp.size.proportionWidthHeight * increment) / comp.proportionBoxComplementH;
		comp.size.actHeight += increment / comp.proportionBoxComplementH;
		// se coloca en el centro
		// se hace cada iteración porque la posición
		// cambia en función de la caja y la caja se está moviendo
		// hasta terminar de crecer
		comp.size.centerPos = transform->getPos() + offset;
		// se recoloca para que crezca desde el centro
		comp.pos = Vector(comp.size.centerPos.getX() - comp.size.actWidth / 2,
			comp.size.centerPos.getY() - comp.size.actHeight / 2);
	}

	void initSize(Size& size, float width, float height) {
		size = { 0, 0, 0, 0, Vector::zero, 0 };

		size.desiredWidth = width;
		size.desiredHeight = height;
		size.proportionWidthHeight = size.desiredWidth / size.desiredHeight;
	}

	void initComplement(Complement& complement, float width, float height) {
		complement.pos = Vector::zero;
		complement.proportionBoxComplementH = 0;

		initSize(complement.size, width, height);
		// proporción caja - complemento respecto a la altura
		complement.proportionBoxComplementH = box.desiredHeight / complement.size.desiredHeight;
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BOX_TEXT;

	BoxText(GameObject* parent, Texture* keys, Texture* portraitBorder, Texture* portrait, Vector offsetSize) :
		Component(parent, id), keysTexture(keys), portraitBorderTexture(portraitBorder), portraitTexture(portrait), elapsedTime(0), timer(0.001), increment(5) {
		text = parent->getComponent<Text>();
		transform = parent->getComponent<Transform>();

		// tamaños deseados de la caja
		initSize(box, text->getWidthTextBox() * offsetSize.getX(), text->getNumLines() * offsetSize.getY());
		// posición central de la caja
		// se hace para que el objeto crezca desde el centro
		// se coloca en su centro y se va aumentando y recolocando
		// hasta que alcanza el tamaño deseado
		box.centerPos = Vector(transform->getPos().getX() + box.desiredWidth / 2,
			transform->getPos().getY() + box.desiredHeight / 2);

		// tamaños deseados de la tecla
		initComplement(key, keys->fwidth() * 5 / 1.4, keys->fheight() * 5 / 1.4);

		// borde
		float wBorder = portraitBorderTexture->fwidth() - 15;
		float hBorder = portraitBorderTexture->fheight() - 15;
		float xBorder = transform->getPos().getX() + box.actWidth / 32;
		float yBorder = transform->getPos().getY() + box.actHeight / 2 - hBorder / 2;
		// retrato
		float w = wBorder - 42;
		float h = hBorder - 42;
		float x = xBorder + wBorder / 2 - w / 2;
		float y = yBorder + hBorder / 2 - h / 2;

		initComplement(this->portraitBorder, wBorder, hBorder);
		initComplement(this->portrait, w, h);
	}

	inline bool hasGrown() {
		return box.actWidth >= box.desiredWidth && box.actHeight >= box.actHeight;
	}

	virtual void update() {
		if (!hasGrown()) {
			elapsedTime += deltaTime;
			if (elapsedTime > timer) {
				elapsedTime = 0;

				enlargeBox();

				enlargeComplement(key, Vector(3.3 * box.actWidth / 4, box.actHeight / 1.2));

				enlargeComplement(portraitBorder, Vector(box.actWidth / 10, box.actHeight / 2));

				enlargeComplement(portrait, Vector(box.actWidth / 10, box.actHeight / 2));
			}
		}
	}

	virtual void render() {
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

		// render de la tecla
		dest.x = key.pos.getX();
		dest.y = key.pos.getY();
		dest.w = key.size.actWidth;
		dest.h = key.size.actHeight;
		keysTexture->renderFrame(dest, 2, 2, 0);
	}
};