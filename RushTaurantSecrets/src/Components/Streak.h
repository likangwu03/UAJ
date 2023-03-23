#pragma once

#include "../Structure/Component.h"
#include "../Utilities/Texture.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/checkML.h"
#include "../Managers/ClientsManager.h"
#include <iostream>
#include <array>

using namespace std;

struct colors {
	unsigned long fg;
	unsigned long bg;
};

struct numbersTexture {
	Texture* numberBg;
	Texture* numberFg;
	Texture* xBg;
	Texture* xFg;
};

struct measures {
	Vector posBg;
	Vector posFg;
	float proportion;
	float width;
	float height;
	float originalWidth;
	float originalHeight;
};

class Streak : public Component {
private:

	// primero fg, luego bg
	colors colors[MAX_PAY]{
		{0xF51400FF, 0xF7584AFF},	// rojo
		{0xF57914FF, 0xF7A25EFF},	// naranja
		{0xF0AE0AFF, 0xF2C552FF},	// amarillo
		{0x1FF03EFF, 0x68F27DFF},	// verde
		{0x2692F0FF, 0x6FB5F2FF},	// azul
		{0x3726F0FF, 0x7A6FF2FF},	// azul oscuro
		{0xC61FF0FF, 0xD768F2FF}	// violeta
	};

	array<numbersTexture, MAX_PAY> numbers;
	int streak;
	int actNumber;
	SDLUtils* sdl;
	float elapsedTime;
	float timer;
	measures number;
	measures letterX;
	float increase;	// cómo de grande es un número respecto del otro
	float size;	// tamaño general
	float moneyStreak;

	SDL_Rect createRect(float x, float y, float width, float height) {
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		dest.w = width;
		dest.h = height;
		return dest;
	}

	void initData(Vector pos) {
		// TODOS LOS DATOS SON PARAMETRIZABLES
		// iniciar datos relativos a la letraX
		letterX.posBg = Vector(pos.getX(), pos.getY());
		letterX.originalWidth = 20.0;
		letterX.originalHeight = 35.0;
		letterX.proportion = letterX.originalWidth / letterX.originalHeight;

		// iniciar datos relativos al número
		// mismo que la letraX,
		// excepto la coordena X de la posición del fondo que varía con el ancho de la letraX
		// ajusta a ojo, no es del todo exacto
		number.posBg.setY(letterX.posBg.getY() - 20 / size);
		number.originalWidth = 50;
		number.originalHeight = 100;
		number.proportion = number.originalWidth / number.originalHeight;
	}

	// actualizar el tamaño de las texturas y la posición de las texturas de la parte de arriba
	void updateDataAux(Vector shadowPos, measures& data) {
		// el tamaño cambia en función del número que se esté renderizando
		// inicialmente cambia de 1 en 1, es por eso que existe la variable increase
		// para que no crezca tan lento
		data.width = (data.originalWidth + data.proportion * actNumber * increase) / size;
		data.height = (data.originalHeight + actNumber * increase) / size;
		// se cambia la posición del fg para que haga sombra con el bg
		// el cálculo después de shadowPos es para el largo de la sombra sea proporcional
		// al tamaño y no se quede demasiado pequeño
		data.posFg.setX(data.posBg.getX() + (shadowPos.getX() * data.proportion * (actNumber / increase + 1)));
		data.posFg.setY(data.posBg.getY() + (shadowPos.getY() * (actNumber / increase + 1)));
	}

	void updateData() {
		updateDataAux(Vector(-3, -3), letterX);
		// ajusto a ojo, no es del todo exacto
		// no se tiene en cuenta comó van creciendo los números
		number.posBg.setX(letterX.posBg.getX() + letterX.width + 20 / size);
		updateDataAux(Vector(-7, -3), number);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_STREAK;

	Streak(GameObject* parent, float moneyStreak, Vector pos, float timer, float increase, float size, Font* font, int streak = 0) :
		Component(parent, id), moneyStreak(moneyStreak), actNumber(0), sdl(SDLUtils::instance()), elapsedTime(0), timer(timer), increase(increase), size(size), streak(streak) {

		number = { Vector::zero, Vector::zero, 0, 0, 0 };
		letterX = { Vector::zero, Vector::zero, 0, 0, 0 };

		// se crean todas las texturas
		for (int i = 0; i < numbers.size(); ++i) {
			numbers[i].numberBg = new Texture(sdl->renderer(), to_string(i + 1), *font, build_sdlcolor(colors[i].bg));
			numbers[i].numberFg = new Texture(sdl->renderer(), to_string(i + 1), *font, build_sdlcolor(colors[i].fg));
			numbers[i].xBg = new Texture(sdl->renderer(), "x", *font, build_sdlcolor(colors[i].bg));
			numbers[i].xFg = new Texture(sdl->renderer(), "x", *font, build_sdlcolor(colors[i].fg));
		}

		initData(pos);

		updateData();
	}

	virtual ~Streak() {
		for (auto number : numbers) {
			delete number.numberBg;
			number.numberBg = nullptr;

			delete number.numberFg;
			number.numberFg = nullptr;

			delete number.xBg;
			number.xBg = nullptr;

			delete number.xFg;
			number.xFg = nullptr;
		}
	}

	inline void setStreak(int streak) {
		actNumber = 0;
		this->streak = streak;
		updateData();
	}

	inline float getMoneyStreak() {
		return moneyStreak;
	}

	virtual void update() {
		if (actNumber < streak) {
			elapsedTime += deltaTime;
			if (elapsedTime > timer) {
				elapsedTime = 0;

				++actNumber;

				updateData();
			}
		}
	}

	virtual void render() {
		if (actNumber < streak) {
			// renderizado del fondo de la letraX
			// se centra la textura para que vaya creciendo desde el centro
			numbers[actNumber].xBg->render(createRect(
				letterX.posBg.getX() - letterX.width / 2,
				letterX.posBg.getY() - letterX.height / 2,
				letterX.width, letterX.height));
			// renderizado de la parte de arriba de la letraX
			numbers[actNumber].xFg->render(createRect(
				letterX.posFg.getX() - letterX.width / 2,
				letterX.posFg.getY() - letterX.height / 2,
				letterX.width, letterX.height));
			// renderizado del fondo del número
			numbers[actNumber].numberBg->render(createRect(
				number.posBg.getX() - number.width / 2,
				number.posBg.getY() - number.height / 2,
				number.width, number.height));
			// renderizado de la parte de arriba del número
			numbers[actNumber].numberFg->render(createRect(
				number.posFg.getX() - number.width / 2,
				number.posFg.getY() - number.height / 2,
				number.width, number.height));
		}
	}
};