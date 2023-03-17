#include "BoxText.h"

void BoxText::createLetter(string l) {
	Letter letter;
	letter.texture = new Texture(sdl->renderer(), l, *font, build_sdlcolor(0x000000FF));
	letter.pos = Vector(pos.getX() + widthLetter * cont + space, pos.getY() + (heightLetter + offset) * actLine);
	letterTextures.push_back(letter);

	++actLetter;
	++cont;
}

void BoxText::nextWord() {
	// se pasa a la siguiente palabra a la primera letra
	++actWord;
	actLetter = 0;
}

void BoxText::nextLine() {
	space = 0;
	++actLine;
	cont = 0;
}

int BoxText::wrapText(list<string>& words) {
	int numLines = 1;
	int widthLine = 0;

	for (auto it = words.begin(); it != words.end(); ++it) {
		if ((*it) == "\n") {
			++numLines;
			widthLine = 0;
		}
		else {
			// se suma 1 porque después de cada palabra hay un espacio en blanco
			widthLine += (it->size() + 1) * widthLetter;
			if (widthLine > widthTextBox) {
				// se quita el último espacio en blanco
				widthLine -= widthLetter;
				// se vuelve a realizar la comprobación
				if (widthLine > widthTextBox) {
					++numLines;
					widthLine = (it->size() + 1) * widthLetter;

					words.insert(it, "\n");
				}
			}
		}
	}
	return numLines;
}

void BoxText::separateText(string text) {
	words.clear();

	string aux;
	stringstream input(text);
	// se separan las palabran y se guardan en un vector
	while (getline(input, aux, ' ')) {
		words.push_back(aux);
	}

	actWord = words.begin();
}

void BoxText::printLetter() {
	// salto de línea
	if ((*actWord) == "\n") {
		nextLine();
		nextWord();
	}

	string letter = string(1, (*actWord)[actLetter]);
	createLetter(letter);

	// final de la palabra
	if (actLetter >= (*actWord).size()) {
		nextWord();
		space += widthLetter;
	}
}

void BoxText::init(string text) {
	actLetter = 0;
	cont = 0;
	actLine = 0;
	space = 0;

	separateText(text);

	letterTextures.clear();
	// se puede llegar a reservar más memoria de la necesaria si hay saltos de línea 
	letterTextures.reserve(text.size());

	numLines = wrapText(words);
}

void BoxText::releaseLetters() {
	for (auto letter : letterTextures) {
		delete letter.texture;
		letter.texture = nullptr;
	}
}

BoxText::BoxText(GameObject* parent, deque<string> texts, int widthLetter, int heightLetter, Vector pos, float letterFrequency, string fontPath, int size, int widthTextBox) :
	Component(parent, id), texts(texts), elapsedTime(0), widthLetter(widthLetter), heightLetter(heightLetter), pos(pos),
	timer(letterFrequency), widthTextBox(widthTextBox), offset(20), showAllText(false), nextText(false), state(Writing) {

	sdl = SDLUtils::instance();
	ih = InputHandler::instance();
	font = new Font(fontPath, size);

	init(this->texts.front());
	this->texts.pop_front();
}

BoxText::~BoxText() {
	delete font;
	font = nullptr;

	releaseLetters();
}

void BoxText::update() {
	if (actWord != words.end()) {
		state = Writing;
		if (showAllText) {
			while (actWord != words.end()) {
				printLetter();
			}
			showAllText = false;
		}
		else {
			elapsedTime += deltaTime;
			if (elapsedTime > timer) {
				elapsedTime = 0;

				printLetter();
			}
		}
	}
	else {
		state = Written;
		if (nextText && !texts.empty()) {
			newText(texts.front());
			texts.pop_front();

			nextText = false;
		}
	}
}

void BoxText::render() {
	for (int i = 0; i < letterTextures.size(); ++i) {
		SDL_Rect dest;
		dest.x = letterTextures[i].pos.getX();
		dest.y = letterTextures[i].pos.getY();
		dest.w = widthLetter;
		dest.h = heightLetter;

		letterTextures[i].texture->render(dest);
	}
}

void BoxText::handleEvents() {
	if (ih->isKeyDown(SDLK_SPACE)) {
		switch (state) {
		case Writing:
			showAllText = true;
			break;
		case Written:
			nextText = true;
			break;
		}
	}
}