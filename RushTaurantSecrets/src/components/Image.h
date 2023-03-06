#pragma once

#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h";
using namespace std;
class Image : public Component {
private:
	// componente transform para consultar las características físicas del gameobject
	Transform* transform = nullptr;
	Texture* texture = nullptr;
	SDLUtils* sdl;
	Vector pos;
	float w, h;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_IMAGE;

	// REVISAR RELACIÓN CON TRANSFORM
	Image(GameObject* parent, Texture* texture, Vector _pos = { -1,-1 },float _w=-1,float _h=-1) : Component(parent, id), texture(texture), sdl(SDLUtils::instance()) {
		// importante que se añada el Transform antes de Image porque sino no se va a encontrar la ref
		// se guarda la referencia al Transform de la entidad
		transform = parent->getComponent<Transform>();
		// se produce un error si no se encuentra
		assert(texture != nullptr);
		if (_pos == Vector(-1, -1))
			pos = transform->getPos();
		else pos = _pos;
		if (_w == -1 || _h == -1) { 
			h = transform->getH();
			w = transform->getW();
		}
		else {
			h = _h; w = _w;
		}

	}
	Image(GameObject* parent, string s, Vector _pos = { -1,-1 }, float _w = -1, float _h = -1) : Component(parent, id), sdl(SDLUtils::instance()) {
		transform = parent->getComponent<Transform>();
		texture = &((*sdl).images().at(s));
		if (_pos == Vector(-1, -1))
			pos = transform->getPos();
		else pos = _pos;
		if (_w == -1 || _h == -1) {
			h = transform->getH();
			w = transform->getW();
		}
		else {
			h = _h; w = _w;
		}
		assert(texture != nullptr);

	}

	void setTexture(Texture* t) { texture = t; }
	void setTexture(string s) { texture = &((*sdl).images().at(s)); }
	void setPos(Vector _pos) { pos = _pos;}
	void setW(float _w) { w = _w; }
	void setH(float _h) { h = _h; }

	virtual void render() {
		SDL_Rect dest;
		dest.x = transform->getPos().getX();
		dest.y = transform->getPos().getY();
		dest.w = w;
		dest.h = h;
		// renderiza la textura
		texture->render(dest, transform->getRot());
	}
};