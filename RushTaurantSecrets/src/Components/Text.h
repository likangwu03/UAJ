#pragma once

#include "../Structure/Component.h"
#include "../Structure/GameObject.h"
#include "../Utilities/Vector.h"
#include "../Utilities/checkML.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/Texture.h"
#include "../Utilities/InputHandler.h"
#include "Transform.h"
#include <string>
#include <sstream>	// se usa para poder convertir string en stringstream
#include <vector>
#include <deque>

using namespace std;

struct Letter {
	Texture* texture;
	Vector pos;
};

class BoxText;

class Text : public Component {
private:
	enum State {Writing, Written};

	static bool hasFinished;

	Font* font;
	BoxText* boxText;
	Transform* transform;
	SDLUtils* sdl;
	InputHandler* ih;

	State state;

	float elapsedTime;
	float timer;

	deque<string> texts;
	list<string> words;	// vector con todas las palabras
	vector<Letter> letterTextures;
	int widthLetter;
	int heightLetter;
	Vector pos;	// posición del texto
	int widthTextBox;	// ancho del cuadro de texto
	int numLines;	// número de líneas del texto

	std::list<string>::iterator actWord;	// número de palabra actual
	int offset;	// separación entre las líneas del texto
	int actLetter;	// número de letra actual
	int cont;	// separar letras
	int actLine;	// separar líneas
	int space;	// espacio

	bool showAllText;	// mostrar todo el texto de una sola vez
	bool nextText;	// mostrar el siguiente texto

	SoundEffect* nextTextSound;
	SoundEffect* nextLetterSound;

	void createLetter(string l);

	void nextWord();

	void nextLine();

	int wrapText(list<string>& words);

	void separateText(string text);

	void printLetter();

	void init(string text);

	void releaseLetters();

	void newText(string newText);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TEXT;

	Text(GameObject* parent, deque<string> texts, int widthLetter, int heightLetter, float letterFrequency, Font* font, int widthTextBox, float offsetPosX = 0);

	virtual ~Text();

	inline int getNumLines() const {
		return numLines;
	}

	inline int getWidthTextBox() const {
		return widthTextBox;
	}

	inline static bool isTextFinished() {
		return hasFinished;
	}

	inline void addText(string text) {
		texts.push_back(text);
	}

	virtual void initBoxText();

	virtual void update();

	virtual void render();

	virtual void handleEvents();
};