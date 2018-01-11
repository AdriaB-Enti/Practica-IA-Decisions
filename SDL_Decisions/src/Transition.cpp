#include "Transition.h"

void EnoughGold() {
	std::cout << "hola" << std::endl;
}

//TODO: canviar els numeros hardcoded per constants
bool pocketsFull(int gold) {
	if (gold > 100)
		return true;
	else
		return false;
}

bool wealthyEnough(int bankMoney) {
	if (bankMoney > 300)
		return true;
	else
		return false;
}



Transition::Transition(/*State _currState, State _nextState,*/ bool(*pt2Func)()) {
	CheckCondition = pt2Func;
}

namespace transitionCheck {

}