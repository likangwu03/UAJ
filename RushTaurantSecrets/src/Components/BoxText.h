#pragma once

#include "../Structure/Component.h"
#include "../Structure/GameObject.h"
#include "Text.h"
#include "../Utilities/checkML.h"
#include "ShowControlComp.h"
struct Size {
	float desiredWidth;	// ancho al que tiene que llegar el objeto
	float desiredHeight;	// alto al que tiene que llegar el objeto
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
	Texture* nameTexture;
	float elapsedTime;
	float timer;
	float increment;
	Size box;
	Complement key;
	Complement portraitBorder;
	Complement portrait;
	Complement name;
	ShowControlComp* showControl;

	void enlargeBox();

	void enlargeComplement(Complement& comp, Vector offset);

	void initSize(Size& size, float width, float height);

	void initComplement(Complement& complement, float width, float height);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BOX_TEXT;

	BoxText(GameObject* parent, Texture* portraitBorder, Texture* portrait, Vector offsetSize, int widthLetter, int heightLetter, Font* font, string name);

	BoxText(GameObject* parent, Texture* portraitBorder, Texture* portrait, Vector offsetSize);

	virtual ~BoxText() {
		if (nameTexture != nullptr) {
			delete nameTexture;
		}
	}

	inline float getBoxHeight() const {
		return box.desiredHeight;
	}

	inline bool hasGrown() {
		return box.actWidth >= box.desiredWidth && box.actHeight >= box.actHeight;
	}

	virtual void update();

	virtual void render();
};