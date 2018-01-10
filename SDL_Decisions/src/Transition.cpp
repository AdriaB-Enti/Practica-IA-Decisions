#include "Transition.h"

void EnoughGold() {
	std::cout << "hola" << std::endl;
}

Transition::Transition(/*State _currState, State _nextState,*/ void(*conditionFunc)()) {
	CheckCondition = conditionFunc;
}