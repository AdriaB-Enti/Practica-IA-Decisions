#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Action;//així després no es queixa que "no existeix".
enum ourBoolean { isTrue, isFalse, dontCare };

class WorldState {
	
public:	
	vector<ourBoolean> allVariables;
	int priority;

	WorldState();
	WorldState(ourBoolean agent_viu, ourBoolean agent_te_arma, ourBoolean arma_carregada, ourBoolean agent_te_bomba, ourBoolean enemic_visible, ourBoolean enemic_alineat, ourBoolean enemic_aprop, ourBoolean enemic_viu);
	bool operator==(WorldState otherState); //ORDRE IMPORTA, pq el de la dreta si es dontCare també conta com a igual
	WorldState operator+(WorldState otherState); //ORDRE DE LA OPERACIO IMPORTA, el de la dreta sobreescriu al de l'esquerra a no ser que sigui dontCare
	bool CanApplyAction(Action a); //Comprova si aquest estat compleix les precondicions per al compliment de l'acció
	int HeuristicTo(WorldState goal); //retornara el nombre de variables diferents d'aquest estat respecte a un altre, sense tenir en compte dontCare de l'objectiu
	

};

class Action {
public:
	WorldState preCondition;
	WorldState effect;

	Action(WorldState preCon, WorldState eff);
};







