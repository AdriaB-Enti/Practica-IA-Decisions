#include "Transition.h"

void EnoughGold() {
	std::cout << "hola" << std::endl;
}

Transition::Transition(/*State _currState, State _nextState,*/ bool(*pt2Func)()) {
	CheckCondition = pt2Func;
}