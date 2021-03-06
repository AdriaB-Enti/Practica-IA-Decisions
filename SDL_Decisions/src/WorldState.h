#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Action;//aix� despr�s no es queixa que "no existeix".
enum ourBoolean { isTrue, isFalse, dontCare };

class WorldState {
	
public:	
	vector<ourBoolean> allVariables;
	int priority;
	int id;
	
	WorldState();
	WorldState(ourBoolean agent_viu, ourBoolean agent_te_arma, ourBoolean arma_carregada, ourBoolean agent_te_bomba, ourBoolean enemic_visible, ourBoolean enemic_alineat, ourBoolean enemic_aprop, ourBoolean enemic_viu);
	bool GoalReached(WorldState goal); //ORDRE IMPORTA, pq el de la dreta si es dontCare tamb� conta com a igual
	WorldState ApplyAction(Action action); //ORDRE DE LA OPERACIO IMPORTA, el de la dreta sobreescriu al de l'esquerra a no ser que sigui dontCare	
	bool CanApplyAction(Action a); //Comprova si aquest estat compleix les precondicions per al compliment de l'acci�
	int HeuristicTo(WorldState goal); //retornara el nombre de variables diferents d'aquest estat respecte a un altre, sense tenir en compte dontCare de l'objectiu
	bool operator==(WorldState otherState) const;
	bool operator!=(WorldState otherState) const;
	void print();
	
};

class Action {
public:
	WorldState preCondition;
	WorldState effect;
	int cost;
	string name;

	Action() {};
	Action(string _name, WorldState preCon, WorldState eff, int _cost);
	void printName();
};







