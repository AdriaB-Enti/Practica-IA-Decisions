#pragma once
#include <iostream>
#include <SDL.h>


class Agent;

class State {
	
public:	
	virtual void Enter(){}
	virtual void Update(float deltaTime, Agent* agent){}
	virtual void Exit(){}
};

class HomeState : public State {
public:
	void Enter(){}
	void Update(float deltaTime, Agent* agent);
	void Exit(){}
	
};