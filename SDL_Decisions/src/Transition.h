#pragma once
#include "State.h"
#include <stdio.h>

enum evento{enoughGold, tired, wantMoreMemes};
void EnoughGold();

class Transition {
	void(*CheckCondition)();
	State currState;
	State nextState;

	Transition(/*State _currState, State _nextState,*/ void(*conditionFunc)());
	State GetCurrState();
	State GetNextState();	
};

//en el update del agent
//mirem si agent.currState es igual al de la transicio
//cridem CheckEvent i si es true -> posem agent.currState igual al next del Transition

