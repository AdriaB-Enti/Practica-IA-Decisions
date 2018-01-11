#pragma once

enum ourBoolean {isTrue, isFalse, dontCare};

class Action;//així després no es queixa que "no existeix".

class WorldState {
public:
	ourBoolean Agent_viu;
	/*ourBoolean Agent_te_arma;
	ourBoolean Arma_carregada;
	ourBoolean Agent_te_bomba;
	ourBoolean Enemic_visible;
	ourBoolean Enemic_alineat;
	ourBoolean Enemic_aprop;
	ourBoolean Enemic_viu;*/

	bool EqualWorldState(WorldState wS1, WorldState wS2);
	WorldState ApplyAction(Action a);
};


class Action {
	WorldState preCondition;
	WorldState effect;
	Action(WorldState wS1, WorldState wS2);
	void Update(float deltaTime);
};


