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

class BoxText : public Component {
private:
	Text* text;
	Transform* transform;
	Texture* texture;
	float elapsedTime;
	float timer;
	float increment;
	Size box;
	Size key;
	Vector keyPos;
	float proportionBoxKeyH;

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

	void enlargeKey() {
		// se aumenta el tamaño de la tecla
		key.actWidth += (key.proportionWidthHeight * increment) / proportionBoxKeyH;
		key.actHeight += increment / proportionBoxKeyH;
		// se coloca en el centro
		// se hace cada iteración porque la posición de la tecla
		// cambia en función de la caja y la caja se está moviendo
		// hasta terminar de crecer
		key.centerPos = Vector((transform->getPos().getX() + 3.3 * box.actWidth / 4),
			(transform->getPos().getY() + box.actHeight / 1.2));
		// se recoloca para que crezca desde el centro
		keyPos = Vector(key.centerPos.getX() - key.actWidth / 2,
			key.centerPos.getY() - key.actHeight / 2);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BOX_TEXT;

	BoxText(GameObject* parent, Texture* texture) :
		Component(parent, id), texture(texture), elapsedTime(0), timer(0.001), increment(5) {
		text = parent->getComponent<Text>();
		transform = parent->getComponent<Transform>();
		box = { 0, 0, 0, 0, Vector::zero, 0 };
		key = { 0, 0, 0, 0, Vector::zero, 0 };

		// tamaños deseados de la caja
		box.desiredWidth = text->getWidthTextBox() * 1.2;
		box.desiredHeight = text->getNumLines() * 90;
		box.proportionWidthHeight = box.desiredWidth / box.desiredHeight;
		// posición central de la caja
		// se hace para que el objeto crezca desde el centro
		// se coloca en su centro y se va aumentando y recolocando
		// hasta que alcanza el tamaño deseado
		box.centerPos = Vector(transform->getPos().getX() + box.desiredWidth / 2,
			transform->getPos().getY() + box.desiredHeight / 2);

		// tamaños deseados de la tecla
		key.desiredWidth = 160 / 1.4;
		key.desiredHeight = 80 / 1.4;
		key.proportionWidthHeight = key.desiredWidth / key.desiredHeight;

		// propórción caja - letra respecto a la altura
		proportionBoxKeyH = box.desiredHeight / key.desiredHeight;
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

				enlargeKey();
			}
		}
	}

	virtual void render() {
		// render de la tecla
		SDL_Rect dest;
		dest.x = keyPos.getX();
		dest.y = keyPos.getY();
		dest.w = key.actWidth;
		dest.h = key.actHeight;
		texture->renderFrame(dest, 2, 2, 0);
	}
};