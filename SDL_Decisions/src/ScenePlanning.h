#pragma once
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Path.h"
#include "Graph.h"


class ScenePlanning :
	public Scene
{
public:
	ScenePlanning();
	~ScenePlanning();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D currentTarget;
	int currentTargetIndex;
	Path path;
	int num_cell_x;
	int num_cell_y;
	bool draw_grid;
	std::vector<SDL_Rect> maze_rects;
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	void initMaze();
	bool loadTextures(char* filename_bg, char* filename_coin);
	std::vector< std::vector<int> > terrain;
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	//	   STATES
	//		[0]
	//		[1]
	//	[2]	[3]	[4]
	std::vector <Vector2D> states = {Vector2D(19,3),Vector2D(19,10),Vector2D(6,19),Vector2D(19,19),Vector2D(33,19) };
	Vector2D money;
	void setPathTo(short newDestination);
	void setDestinationTo(Agent::stateEnum destination);
	void isAgentInDestination(Agent* agent);

	void createGraph();
	Graph graph;

};
