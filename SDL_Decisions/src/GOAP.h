#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum ourBoolean {isTrue, isFalse, dontCare};

class Action;//així després no es queixa que "no existeix".

class WorldState {
	
public:	
	vector<ourBoolean> allVariables;

	WorldState();
	WorldState(ourBoolean agent_viu, ourBoolean agent_te_arma, ourBoolean arma_carregada, ourBoolean agent_te_bomba, ourBoolean enemic_visible, ourBoolean enemic_alineat, ourBoolean enemic_aprop, ourBoolean enemic_viu);
	bool operator==(WorldState otherState); //ORDRE IMPORTA, pq el de la dreta si es dontCare també conta com a igual
	WorldState operator+(WorldState otherState); //ORDRE DE LA OPERACIO IMPORTA, el de la dreta sobreescriu al de l'esquerra a no ser que sigui dontCare
	bool CanApplyAction(Action a);		
		
};

class Action {
public:
	WorldState preCondition;
	WorldState effect;

	Action(WorldState preCon, WorldState eff);
};



