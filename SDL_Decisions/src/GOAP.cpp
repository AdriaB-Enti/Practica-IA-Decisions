#include "GOAP.h"

Action::Action(WorldState wS1, WorldState wS2) {
	preCondition = wS1;
	effect = wS2;
}

WorldState::WorldState() {
	//Agent_viu = dontCare;	
}
WorldState::WorldState(ourBoolean agent_viu/*, ourBoolean agent_te_arma, ourBoolean arma_carregada, ourBoolean agent_te_bomba, ourBoolean enemic_visible, ourBoolean enemic_alineat, ourBoolean enemic_aprop, ourBoolean enemic_viu*/) {
	//Agent_viu = _agent_viu;
	allVariables.push_back(agent_viu);
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


