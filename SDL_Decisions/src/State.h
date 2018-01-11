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

class MineState : public State {
public:
	MineState(){};
	void Enter(){}
	void Update(float deltaTime, Agent* agent);
	void Exit() {}
};

class BankState : public State {
public:
	BankState(){};
	void Enter(){}
	void Update(float deltaTime, Agent* agent);
	void Exit() {}
};

class HomeState : public State {
public:
	HomeState(){};
	void Enter(){}
	void Update(float deltaTime, Agent* agent);
	void Exit(){}
	
};
