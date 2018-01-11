#include "GOAP.h"

Action::Action(WorldState preCon, WorldState eff) {
	preCondition = preCon;
	effect = eff;
}

WorldState::WorldState() {
	for (int i = 0; i < 8; i++) {
		allVariables.push_back(dontCare);
	}
}
WorldState::WorldState(ourBoolean agent_viu, ourBoolean agent_te_arma, ourBoolean arma_carregada, ourBoolean agent_te_bomba, ourBoolean enemic_visible, ourBoolean enemic_alineat, ourBoolean enemic_aprop, ourBoolean enemic_viu) {
	allVariables.push_back(agent_viu);
	allVariables.push_back(agent_te_arma);
	allVariables.push_back(arma_carregada);
	allVariables.push_back(agent_te_bomba);
	allVariables.push_back(enemic_visible);
	allVariables.push_back(enemic_alineat);
	allVariables.push_back(enemic_alineat);
	allVariables.push_back(enemic_aprop);
}
bool WorldState::operator==(WorldState otherState) {
	
	for (int i = 0; i < allVariables.size(); i++) {
		if (allVariables[i] != otherState.allVariables[i] && otherState.allVariables[i] != dontCare)
			return false;
	}
	return true;	
}

WorldState WorldState::operator+ (WorldState otherState) {
	WorldState res;	

	for (int i = 0; i < allVariables.size(); i++) {
		if (otherState.allVariables[i] == isTrue)
			res.allVariables.push_back(isTrue);
		else if (otherState.allVariables[i] == isFalse)
			res.allVariables.push_back(isFalse);
		else
			res.allVariables.push_back(allVariables[i]);
			
	}	
	
	return res;
}

bool WorldState::CanApplyAction (Action a){

	for (int i = 0; i < allVariables.size(); i++) {
		if (a.preCondition.allVariables[i] != dontCare && a.preCondition.allVariables[i] != allVariables[i])
			return false;
	}
	return true;	
}

int WorldState::HeuristicTo(WorldState goal) {
	int cost = 0;
	for (int i = 0; i < allVariables.size(); i++) {
		if (goal.allVariables[i] != dontCare && goal.allVariables[i] != allVariables[i])
			cost++;
	}
	return cost;
}

//DEFINIM LES DIFERENTS ACCIONS I LES GUARDEM EN UN ARRAY

//scout necessita: player viu -> enemic visible (si no esta viu es igual abans de fer scout tampoc ho pots saber)
Action scout (WorldState (isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), WorldState(dontCare, dontCare, dontCare, dontCare, isTrue, dontCare, dontCare, dontCare));
//buscar arma necessita: player viu -> tens arma
Action searchWeapon(WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), WorldState(dontCare, isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare));
//fabricar bomba necessita: player viu -> tens bomba
Action craftBomb(WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), WorldState(dontCare, dontCare, dontCare, isTrue, dontCare, dontCare, dontCare, dontCare));
//chase necessita: player viu, veure l'enemic, enemic viu -> estas a prop
Action chase(WorldState(isTrue, dontCare, dontCare, dontCare, isTrue, dontCare, dontCare, isTrue), WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isTrue, dontCare));
//aim necessita: player viu, tenir arma, veure l'enemic, enemic viu -> t'alinees a l'enemic
Action aim(WorldState(isTrue, isTrue, dontCare, dontCare, isTrue, dontCare, dontCare, isTrue), WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, isTrue, dontCare, dontCare));
//shoot necessita: player viu, tenir arma,arma carregada, veure l'enemic,enemic viu -> enemic ja no esta viu
Action shoot(WorldState(isTrue, isTrue, isTrue, dontCare, isTrue, isTrue, dontCare, isTrue), WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isFalse));
//shoot necessita: player viu, tenir bomba, enemic a prop, veure l'enemic,enemic viu -> enemic i player ja no estan vius
Action useBomb(WorldState(isTrue, dontCare, dontCare, isTrue, isTrue, dontCare, isTrue, isTrue), WorldState(isFalse, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isFalse));
//reload necessita: player viu, tenir arma -> arma es carrega
Action reload(WorldState(isTrue, isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), WorldState(dontCare, dontCare, isTrue, dontCare, dontCare, dontCare, dontCare, dontCare));
//flee necessita: player viu -> ja no estas  a prop
Action flee(WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isFalse, dontCare));

vector<Action> actions;

