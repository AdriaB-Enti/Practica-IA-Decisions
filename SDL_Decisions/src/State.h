#pragma once
#include <iostream>
#include <SDL.h>


class Agent;

class State {
public:	
	virtual void Enter(Agent* agent){}
	virtual void Update(float deltaTime, Agent* agent){}
	virtual void Exit(){}
};

class MineState : public State {
public:
	MineState(){};
	void Enter(Agent* agent);
	void Update(float deltaTime, Agent* agent);
	void Exit();
};

class BankState : public State {
public:
	BankState(){};
	void Enter(Agent* agent);
	void Update(float deltaTime, Agent* agent);
	void Exit();
};

class HomeState : public State {
public:
	HomeState() {};
	void Enter(Agent* agent);
	void Update(float deltaTime, Agent* agent);
	void Exit();
};
class SaloonState : public State {
public:
	SaloonState() {};
	void Enter(Agent* agent);
	void Update(float deltaTime, Agent* agent);
	void Exit();
};
class StartState : public State {
public:
	StartState() {};
	void Enter(Agent* agent) {};
	void Update(float deltaTime, Agent* agent);
	void Exit() {};
};
