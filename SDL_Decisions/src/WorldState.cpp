#include "WorldState.h"

WorldState::WorldState() {
	for (int i = 0; i < 8; i++) {
		allVariables.push_back(dontCare);
	}
	id = -1;
}
WorldState::WorldState(ourBoolean agent_viu, ourBoolean agent_te_arma, ourBoolean arma_carregada, ourBoolean agent_te_bomba, ourBoolean enemic_visible, ourBoolean enemic_alineat, ourBoolean enemic_aprop, ourBoolean enemic_viu) {
	allVariables.push_back(agent_viu);
	allVariables.push_back(agent_te_arma);
	allVariables.push_back(arma_carregada);
	allVariables.push_back(agent_te_bomba);
	allVariables.push_back(enemic_visible);
	allVariables.push_back(enemic_alineat);
	allVariables.push_back(enemic_aprop);
	allVariables.push_back(enemic_viu);
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
bool WorldState::operator!=(WorldState otherState) const {
	for (int i = 0; i < allVariables.size(); i++) {
		if (allVariables[i] != otherState.allVariables[i])
			return true;
	}
	return false;
}

WorldState WorldState::ApplyAction (Action action) {
	WorldState res;	
	
	for (int i = 0; i < action.effect.allVariables.size(); i++) {
		if (action.effect.allVariables[i] == isTrue)
			res.allVariables[i] = isTrue;
		else if (action.effect.allVariables[i] == isFalse)
			res.allVariables[i] = isFalse;
		else
			res.allVariables[i] = allVariables[i];			
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

void WorldState::print() {
	vector<string> valueNames = { "Player alive: ", "Has weapon: ", "Loaded weapon: ", "Has bomb: ", "Enemy in sight: ", "Enemy in line: ", "Enemy is close: ", "Enemy alive: " };
	for (int i = 0; i < allVariables.size(); i++) {
		cout << valueNames[i];
		if (allVariables[i] == 0)
			cout << "true,";
		else if (allVariables[i] == 1)
			cout << "false,";
		else
			cout << "don't care,";
	}
	cout << endl;
}

Action::Action(string _name, WorldState preCon, WorldState eff, int _cost) {
	preCondition = preCon;
	effect = eff;
	cost = _cost;
	name = _name;
}
void Action::printName() {
	cout << "Player does action  : " << name << endl;
}




