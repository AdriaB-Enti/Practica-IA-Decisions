#pragma once
#include "State.h"

enum evento{enoughGold, tired, wantMoreMemes};

class Transition {
	evento eventType;
	State currState;
	State nextState;

	Transition(State _currState, State _nextState, evento __eventType) {};
	State GetCurrState();
	State GetNextState();
	bool CheckEvent();
};

//en el update del agent
//mirem si agent.currState es igual al de la transicio
//cridem CheckEvent i si es true -> posem agent.currState igual al next del Transition