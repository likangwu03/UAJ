#include "CharacterAnimator.h"

#include "../Utilities/checkML.h"

void CharacterAnimator::init() {
	// inicialmente un personaje reproduce la animación idle hacia abajo
	// orientación anterior y actual
	parentOrientation = plTf->getOrientation();
	currOrientation = none;
	// mov anterior y actual
	parentMov = plTf->getMovState();
	currMov = noMov;
};


void CharacterAnimator::update() {
	bool movHaveChanged = false;
	// se guarda inicialmente la nueva orientación ya que
	// para sentarse se tienen que seleccionar filas distintas dependiendo de la dirección
	parentOrientation = plTf->getOrientation();

	// se comprueba si ha cambiado el estado de movimiento en el que se encontraba
	parentMov = plTf->getMovState();
	if (currMov != parentMov) {
		// se pone derecho el sprite en en el que se haya cogido otro frame
		angle = 0;

		// si ha cambiado, se selecciona el nuevo estado
		// y luego, se eligen los frames oportunos
		currMov = parentMov;
		movHaveChanged = true;

		if (currMov == idle) {
			animationParameters.currAnim = 1;
		}
		else if (currMov == walking) {
			animationParameters.currAnim = 2;
		}
		else if (currMov == sleeping) {
			animationParameters.currAnim = 3;
		}
		else if (currMov == pushing) {
			animationParameters.currAnim = 8;
		}
		else if (currMov == cart) {
			animationParameters.currAnim = 0;
		}
		else if (currMov == sitting) {
			if (parentOrientation == west || parentOrientation == east) {
				animationParameters.currAnim = 4;
			}
			else if (parentOrientation == north || parentOrientation == south) {
				animationParameters.currAnim = 1;
			}
		}
		else if (currMov == dead) {
			animationParameters.currAnim = 19;
			// se cambia el ángulo para que se tumbe el sprite
			angle = 90;
		}
	}

	// si no ha cambiado, se comprueba si la dirección ha cambiado
	// si es asi se cogen los frames oportunos
	if (currOrientation != parentOrientation || movHaveChanged) {

		currOrientation = parentOrientation;

		if (currOrientation == east) {
			// muerto
			if (currMov == dead) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// carro de la compra
			else if (currMov == cart) {
				setCurrentAnim(0, 3, animationParameters.currAnim);
			}
			// idle, corriendo, durmiendo, empujando y sentado
			else {
				setCurrentAnim(0, 6, animationParameters.currAnim);
			}
		}
		else if (currOrientation == north) {
			// muerto
			if (currMov == dead) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// durmiendo
			else if (currMov == sleeping) {
				setCurrentAnim(0, 6, animationParameters.currAnim);
			}
			// carro de la compra
			else if (currMov == cart) {
				setCurrentAnim(3, 6, animationParameters.currAnim);
			}
			// idle, corriendo, empujando y sentado
			else {
				setCurrentAnim(6, 12, animationParameters.currAnim);
			}
		}
		else if (currOrientation == west) {
			// sentado
			if (currMov == sitting) {
				setCurrentAnim(6, 12, animationParameters.currAnim);
			}
			// muerto
			else if (currMov == dead) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// durmiendo
			else if (currMov == sleeping) {
				setCurrentAnim(0, 6, animationParameters.currAnim);
			}
			// carro de la compra
			else if (currMov == cart) {
				setCurrentAnim(6, 9, animationParameters.currAnim);
			}
			// idle, corriendo, empujando
			else {
				setCurrentAnim(12, 18, animationParameters.currAnim);
			}
		}
		else if (plTf->getOrientation() == south) {
			// muerto
			if (currMov == dead) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// durmiendo
			else if (currMov == sleeping) {
				setCurrentAnim(0, 6, animationParameters.currAnim);
			}
			// carro de la compra
			else if (currMov == cart) {
				setCurrentAnim(9, 12, animationParameters.currAnim);
			}
			// idle, corriendo, empujando y sentado
			else {
				setCurrentAnim(18, 24, animationParameters.currAnim);
			}
		}
	}
	Animator::update();
}