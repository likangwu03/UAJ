#pragma once
#include "../scenes/UI.h"

// UI del restaurante -- hereda de la clase UI principal
class UIRestaurant : public UI
{
private:
	// iconos exclusivos de esta UI
	// TO-DO: reputación, objetivo diario, reloj, inventario

public:
	UIRestaurant() : UI() {}
};

