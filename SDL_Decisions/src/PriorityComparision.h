#pragma once
#include "WorldState.h"

class PriorityComparision {
public:
	bool operator ()(const WorldState& a, const WorldState& b) const {
		if (a.priority < b.priority || a.priority == b.priority) //els nodes amb prioritats m�s properes a 0 s�n els que volem que estiguin primer a la cua
			return false;
		return true;
	}
};