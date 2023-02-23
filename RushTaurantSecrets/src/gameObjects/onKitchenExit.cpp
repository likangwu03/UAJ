#include "onKitchenExit.h"

void onKitchenExit::onTriggerExit() {
	ing->removeAllIngredients(); //hay que modificar este método para que devuelva los ingredientes a su sitio y no solo los elimine del player
}
