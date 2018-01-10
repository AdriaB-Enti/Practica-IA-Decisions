#pragma once

enum ourBoolean {isTrue, isFalse, dontCare};
struct WorldState {
	ourBoolean Agent_viu;
	/*ourBoolean Agent_te_arma;
	ourBoolean Arma_carregada;
	ourBoolean Agent_te_bomba;
	ourBoolean Enemic_visible;
	ourBoolean Enemic_alineat;
	ourBoolean Enemic_aprop;
	ourBoolean Enemic_viu;*/
};

bool EqualWorldState (WorldState wS1, WorldState wS2);

