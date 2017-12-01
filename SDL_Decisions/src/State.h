#pragma once
#include <iostream>
#include <SDL.h>

class State
{
public:
	State() {};
	virtual ~State() {};
	virtual void Enter();
	virtual void Update(float dtime);
	virtual void Exit();
};