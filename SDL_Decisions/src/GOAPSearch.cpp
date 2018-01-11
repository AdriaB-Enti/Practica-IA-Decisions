#include "GOAP.h"

//DEFINIM LES DIFERENTS ACCIONS I LES GUARDEM EN UN ARRAY

//scout necessita: player viu -> enemic visible (si no esta viu es igual abans de fer scout tampoc ho pots saber)
Action scout(WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), WorldState(dontCare, dontCare, dontCare, dontCare, isTrue, dontCare, dontCare, dontCare));
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
