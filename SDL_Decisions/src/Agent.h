#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include "SteeringBehavior.h"
#include "State.h"

struct AgentStatus {
	float thirst;		//set -> quan és 0 no té set
	float rest;			//Descans -> quan està a 0 és quan està cansat
	float gold;			//diners a les butxaques
	float moneyInBank;
};


class Agent
{
	friend class SteeringBehavior;

private:
	SteeringBehavior *steering_behavior;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Color color;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	//PRACTICA3

	//Aquí posem tots els Estats
	HomeState homeState = HomeState();
	BankState bankState = BankState();

	State * currentState = &homeState; //inicialitzem a home
	AgentStatus playerNeeds{ 0,100,0,0 };

public:
	enum stateEnum
	{
		Home,
		Bank,
		Mine,
		Drink
	};
	~Agent();
	SteeringBehavior *Behavior();
	Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setMass(float mass);
	void addAgentStatus(AgentStatus newStatus);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void update(Vector2D steering_force, float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	AgentStatus GetPlayerNeeds();
	void changeState(stateEnum newState);
};
