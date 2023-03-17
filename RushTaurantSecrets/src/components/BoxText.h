#pragma once

#include "../structure/Component.h"
#include "../utilities/Vector.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include <string>
#include <sstream>	// se usa para poder convertir string en stringstreams
#include <vector>
#include <deque>

using namespace std;

struct Letter {
	Texture* texture;
	Vector pos;
};

class BoxText : public Component {
private:
	enum State {Writing, Written};
	State state;
	deque<string> texts;
	float elapsedTime;
	float timer;
	int widthLetter;
	int heightLetter;
	Font* font;
	Vector pos;	// posición del texto
	SDLUtils* sdl;
	InputHandler* ih;
	vector<Letter> letterTextures;
	list<string> words;	// vector con todas las palabras
	int widthTextBox;	// ancho del cuadro de texto
	int offset;	// separación entre las líneas del texto
	int numLines;	// número de líneas del texto

	std::list<string>::iterator actWord;	// número de palabra actual
	int actLetter;	// número de letra actual
	int cont;
	int actLine;
	int space;

	bool showAllText;
	bool nextText;

	void createLetter(string l);

	void nextWord();

	void nextLine();

	int wrapText(list<string>& words);

	void separateText(string text);

	void printLetter();

	void init(string text);

	void releaseLetters();

	inline void newText(string newText) {
		releaseLetters();
		init(newText);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TEXT;

	BoxText(GameObject* parent, deque<string> text, int widthLetter, int heightLetter, Vector pos, float letterFrequency, string fontPath, int size, int widthTextBox);

	virtual ~BoxText();

	inline int getNumLines() const {
		return numLines;
	}

	void addText(string text) {
		texts.push_back(text);
	}

	bool checkAllTextWritten() const {
		return texts.empty();
	}
	
	virtual void update();

	virtual void render();

	virtual void handleEvents();
};