#pragma once
#include "State.h"
#include "Agent.h"

#define MAXMONEYPOCKETS 100

//enum Agent::stateEnum;

void HomeState::Update(float deltaTime, Agent* agent) 
{
 //std::cout << agent->GetPlayerNeeds().rest << std::endl;
}

void MineState::Update(float deltaTime, Agent* agent) {
	//augmentar els diners en les butxaques, la set i el cansament
	agent->addAgentStatus(AgentStatus{ deltaTime * 10, deltaTime*(-5), deltaTime * 10, 0 });
	if (agent->GetPlayerNeeds().gold > MAXMONEYPOCKETS)
	{
		agent->changeState(Agent::stateEnum::Bank);
	}
	//TODO: mirar si te prou sed i ha d'anar a beure
}

void BankState::Update(float deltaTime, Agent* agent) {

	agent->addAgentStatus(AgentStatus{ deltaTime * 10, deltaTime*(-5), 0, deltaTime * (-10) });

	if (agent->GetPlayerNeeds().gold > MAXMONEYPOCKETS)
	{
		agent->changeState(Agent::stateEnum::Mine);
	}
}