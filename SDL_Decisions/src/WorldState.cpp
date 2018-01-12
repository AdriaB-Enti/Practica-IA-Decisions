#include "WorldState.h"

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
bool WorldState::GoalReached(WorldState goal) {
	
	for (int i = 0; i < allVariables.size(); i++) {
		if (allVariables[i] != goal.allVariables[i] && goal.allVariables[i] != dontCare)
			return false;
	}
	return true;	
}
bool WorldState::operator==(WorldState otherState) const {
	for (int i = 0; i < allVariables.size(); i++) {
		if (allVariables[i] != otherState.allVariables[i])
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

Action::Action(WorldState preCon, WorldState eff) {
	preCondition = preCon;
	effect = eff;
}




