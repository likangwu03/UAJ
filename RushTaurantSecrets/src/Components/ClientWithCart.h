#pragma once
#include "../Structure/Component.h"
#include "../Components/Transform.h"
#include "../Structure/GameObject.h"
#include "../Utilities/SDLUtils.h"
#include "../Components/StraightMovement.h"
#include "../Utilities/checkML.h"

class ClientWithCart : public Component {
private:
	struct Animation {
		Texture* texture;
		int row;
		int actCol;
		int initCol;
		int endCol;
		float elapsedTime;
		float frameRate;
	};

	const float FRAME_RATE = 7;

	SDLUtils* sdl;

	Transform* transform;
	StraightMovement* straightMovement;
	Animation client;

	Animation cart;
	Vector offset;
	float nearEast;
	float nearWest;
	float nearNorth;
	float nearSouth;
	float widthCart;
	float heightCart;
	GOOrientation oldOrientation;
	bool changeToIdle;
	bool changeToPhone;

	inline void setAnim(Animation& anim, int row, int initCol, int endCol);

	inline void renderAnim(Animation anim, Vector pos, int width, int height);

	void updateAnim(Animation& anim);

	void changeDirection();

	void setDirection(GOOrientation orientation);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENT_CART;

	ClientWithCart(GameObject* parent, string sprite);

	virtual void update();

	virtual void render();
	
};