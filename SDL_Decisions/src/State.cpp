#pragma once
#include "State.h"
#include "Agent.h"
#include "ScenePlanning.h"

#define MAXMONEYPOCKETS 100
#define MAXMONEYBANK	200
#define MAXREST			80
#define MAXTHIRST		80

float clamp(float toClamp, float maxi, float mini) {
	return max(mini, min(toClamp, maxi));
}

void MineState::Enter(Agent* agent) {
	std::cout << "entering minestate\n";
	agent->currentStateEnum = agent->stateEnum::Mine;
}

void MineState::Update(float deltaTime, Agent* agent) {
	//augmentar els diners en les butxaques, la set i el cansament
	agent->addAgentStatus(AgentStatus{ deltaTime * 10, deltaTime*(-5), deltaTime * 15, 0 });
	if (agent->GetPlayerNeeds().gold > MAXMONEYPOCKETS)
	{
		agent->printNeeds();
		agent->changeState(Agent::stateEnum::Bank);
	}
	if (agent->GetPlayerNeeds().thirst >= MAXTHIRST) {
		agent->printNeeds();
		agent->changeState(Agent::stateEnum::Drink);
	}
	//TODO: mirar si te prou set i ha d'anar a beure
}

void MineState::Exit() {
	std::cout << "Quitting minestate\n";
}

void BankState::Enter(Agent* agent) {
	std::cout << "Entering bankstate\n";
	agent->currentStateEnum = agent->stateEnum::Bank;
}

void BankState::Update(float deltaTime, Agent* agent) {
	
	agent->addAgentStatus(AgentStatus{ deltaTime * 10, deltaTime*(-5), deltaTime * (-20), deltaTime * 20 });

	//quan ja hem dipositat tots els diners al banc
	if (agent->GetPlayerNeeds().gold <= 0) {
		agent->printNeeds();
		if (agent->GetPlayerNeeds().moneyInBank > MAXMONEYBANK) {
			agent->changeState(Agent::stateEnum::Home);
		}
		else {
			agent->changeState(Agent::stateEnum::Mine);
		}
	}
}

void BankState::Exit() {
	std::cout << "Quitting bankstate\n";
}


void HomeState::Enter(Agent* agent) {
	std::cout << "Entering homestate\n";
	agent->currentStateEnum = agent->stateEnum::Home;
}

void HomeState::Update(float deltaTime, Agent* agent) {
	agent->addAgentStatus(AgentStatus{ deltaTime * 10, deltaTime*(15), 0, 0 });
	if (agent->GetPlayerNeeds().rest > MAXREST)
	{
		agent->printNeeds();
		agent->changeState(Agent::stateEnum::Mine);
	}
}

void HomeState::Exit() {
	std::cout << "Quitting homestate\n";
}


void SaloonState::Enter(Agent* agent) {
	std::cout << "Entering saloonstate\n";
	agent->currentStateEnum = agent->stateEnum::Drink;
}

void SaloonState::Update(float deltaTime, Agent* agent) {
	agent->addAgentStatus(AgentStatus{ deltaTime * (-20), deltaTime*(-5), 0, 0 });
	if (agent->GetPlayerNeeds().thirst < 0)
	{
		agent->printNeeds();
		agent->changeState(Agent::stateEnum::Mine);
	}
}

void SaloonState::Exit() {
	std::cout << "Quitting saloonstate\n";
}

//l'únic que fa StartState és canviar a l'estat MineState
void StartState::Update(float deltaTime, Agent * agent)
{
	agent->changeState(Agent::stateEnum::Mine);
}
