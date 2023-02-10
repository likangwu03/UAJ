#pragma once
#include "../scenes/UI.h"

// UI del supermercado -- hereda de la clase UI principal
class UIMarket : public UI
{
private:
	// iconos exclusivos de esta UI
	// TO-DO: cesta

public:
	UIMarket() : UI() {}
};

