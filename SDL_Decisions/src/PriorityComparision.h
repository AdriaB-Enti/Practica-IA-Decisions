#pragma once
#include "WorldState.h"

class PriorityComparision {
public:
	bool operator ()(const WorldState& a, const WorldState& b) const {
		if (a.priority < b.priority || a.priority == b.priority) //els nodes amb prioritats més properes a 0 són els que volem que estiguin primer a la cua
			return false;
		return true;
	}
};