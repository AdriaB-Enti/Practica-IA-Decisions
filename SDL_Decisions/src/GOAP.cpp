#include "GOAP.h"

bool EqualWorldState(WorldState wS1, WorldState wS2) {
	if ((wS1.Agent_viu == dontCare || wS2.Agent_viu == dontCare || wS1.Agent_viu == wS2.Agent_viu) /*&&
		(wS1.Agent_te_arma == dontCare || wS2.Agent_te_arma == dontCare || wS1.Agent_te_arma == wS2.Agent_te_arma) &&
		(wS1.Arma_carregada == dontCare || wS2.Arma_carregada == dontCare || wS1.Arma_carregada == wS2.Arma_carregada) &&
		(wS1.Agent_te_bomba == dontCare || wS2.Agent_te_bomba == dontCare || wS1.Agent_te_bomba == wS2.Agent_te_bomba) &&
		(wS1.Enemic_visible == dontCare || wS2.Enemic_visible == dontCare || wS1.Enemic_visible == wS2.Enemic_visible) &&
		(wS1.Enemic_alineat == dontCare || wS2.Enemic_alineat == dontCare || wS1.Enemic_alineat == wS2.Enemic_alineat) &&
		(wS1.Enemic_aprop == dontCare || wS2.Enemic_aprop == dontCare || wS1.Enemic_aprop == wS2.Enemic_aprop) &&
		(wS1.Enemic_viu == dontCare || wS2.Enemic_viu == dontCare || wS1.Enemic_viu == wS2.Enemic_viu)*/ )
		return true;
	
	return false;
}