#include "SceneGOAP.h"

using namespace std;

SceneGOAP::SceneGOAP()
{
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze();
	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);


	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3))
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));

	// PathFollowing next Target
	currentTarget = Vector2D(0, 0);
	currentTargetIndex = -1;

	GOAPlan();

}

SceneGOAP::~SceneGOAP()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneGOAP::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	/*switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (isValidCell(cell))
			{
				if (path.points.size() > 0)
					if (path.points[path.points.size() - 1] == cell2pix(cell))
						break;

				path.points.push_back(cell2pix(cell));
			}
		}
		break;
	default:
		break;
	}
	if ((currentTargetIndex == -1) && (path.points.size()>0))
		currentTargetIndex = 0;

	if (currentTargetIndex >= 0)
	{
		float dist = Vector2D::Distance(agents[0]->getPosition(), path.points[currentTargetIndex]);
		if (dist < path.ARRIVAL_DISTANCE)
		{
			if (currentTargetIndex == path.points.size() - 1)
			{
				if (dist < 3)
				{
					path.points.clear();
					currentTargetIndex = -1;
					agents[0]->setVelocity(Vector2D(0, 0));
					// if we have arrived to the coin, replace it ina random cell!
					if (pix2cell(agents[0]->getPosition()) == coinPosition)
					{
						coinPosition = Vector2D(-1, -1);
						while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition()))<3))
							coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
					}
				}
				else
				{
					Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], currentTarget, path.ARRIVAL_DISTANCE, dtime);
					agents[0]->update(steering_force, dtime, event);
				}
				return;
			}
			currentTargetIndex++;
		}

		currentTarget = path.points[currentTargetIndex];
		Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], currentTarget, dtime);
		agents[0]->update(steering_force, dtime, event);
	}
	else
	{
		agents[0]->update(Vector2D(0, 0), dtime, event);
	}*/
}

void SceneGOAP::draw()
{
	drawMaze();
	drawCoin();


	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	draw_circle(TheApp::Instance()->getRenderer(), (int)currentTarget.x, (int)currentTarget.y, 15, 255, 0, 0, 255);

	agents[0]->draw();
}

const char* SceneGOAP::getTitle()
{
	return "SDL Steering Behaviors :: PathFinding1 Demo";
}

void SceneGOAP::drawMaze()
{
	if (draw_grid)
	{

		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
		for (unsigned int i = 0; i < maze_rects.size(); i++)
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &maze_rects[i]);
	}
	else
	{
		//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
	}
}

void SceneGOAP::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void SceneGOAP::initMaze()
{

	// Initialize a list of Rectagles describing the maze geometry (useful for collision avoidance)
	SDL_Rect rect = { 0, 0, 1280, 32 };
	maze_rects.push_back(rect);
	rect = { 128, 160, 1152, 32 };
	maze_rects.push_back(rect);
	rect = { 0, 736, 1280, 32 };
	maze_rects.push_back(rect);

	rect = { 0,32,32,736 };
	maze_rects.push_back(rect);
	rect = { 1248,32,32,736 };
	maze_rects.push_back(rect);

	rect = { 416,512,32,268 };
	maze_rects.push_back(rect);
	rect = { 832,512,32,268 };
	maze_rects.push_back(rect);

	rect = { 32,480,128,32 };
	maze_rects.push_back(rect);
	rect = { 288,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 704,480,288,32 };
	maze_rects.push_back(rect);
	rect = { 1120,480,128,32 };
	maze_rects.push_back(rect);

	// Initialize the terrain matrix (for each cell a zero value indicates it's a wall)

	// (1st) initialize all cells to 1 by default
	for (int i = 0; i < num_cell_x; i++)
	{
		vector<int> terrain_col(num_cell_y, 1);
		terrain.push_back(terrain_col);
	}
	// (2nd) set to zero all cells that belong to a wall
	int offset = CELL_SIZE / 2;
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{
			Vector2D cell_center((float)(i*CELL_SIZE + offset), (float)(j*CELL_SIZE + offset));
			for (unsigned int b = 0; b < maze_rects.size(); b++)
			{
				if (Vector2DUtils::IsInsideRect(cell_center, (float)maze_rects[b].x, (float)maze_rects[b].y, (float)maze_rects[b].w, (float)maze_rects[b].h))
				{
					terrain[i][j] = 0;
					break;
				}
			}

		}
	}

}

bool SceneGOAP::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D SceneGOAP::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D SceneGOAP::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool SceneGOAP::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.x >= terrain.size()) || (cell.y >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.x][(unsigned int)cell.y] == 0);
}

//PRACTICA
struct WorldStateComparator
{
	bool operator()(const WorldState &left, const WorldState &right) const
	{
		/*for (int i = 0; i < 8; i++) {
			
			if ( left.allVariables[0] < right.allVariables[0])
				return true;
		}
			
		return false;*/
		return (left.id < right.id);
	}
};
int GetValueInMap(map<WorldState, int, WorldStateComparator> m, WorldState key) {

	map <WorldState, int>::iterator it = m.begin();
	while (it != m.end())
	{
		if (it->first == key)
			return it->second;			
		it++;
	}
	return 0;
}
WorldState GetValueInMap(map<WorldState, WorldState, WorldStateComparator> m, WorldState key) {

	map <WorldState, WorldState>::iterator it = m.begin();
	while (it != m.end())
	{
		if (it->first == key)
			return it->second;
		it++;
	}
	
}
Action GetValueInMap(map<WorldState, Action, WorldStateComparator> m, WorldState key) {

	map <WorldState, Action>::iterator it = m.begin();
	while (it != m.end())
	{
		if (it->first == key)
			return it->second;
		it++;
	}

}
bool FindKeyInMap(map<WorldState, int, WorldStateComparator> m, WorldState key) {

	map <WorldState, int>::iterator it = m.begin();
	while (it != m.end())
	{
		if (it->first == key)
			return true;
		it++;
	}
	return false;
}
void SceneGOAP::GOAPlan() {

	//DEFINIM TOTES LES ACCIONS
	//scout necesita : player viu -> enemic a la vista
	Action scout("scout",WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), 
		WorldState(dontCare, dontCare, dontCare, dontCare, isTrue, dontCare, dontCare, dontCare), 10);
	//searchWeapon necessita : player viu -> té arma
	Action searchWeapon("search weapon", WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare),
		WorldState(dontCare, isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), 20);
	//craftBomb necessita : player viu -> té bomba
	Action craftBomb("craft bomb", WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare), 
		WorldState(dontCare, dontCare, dontCare, isTrue, dontCare, dontCare, dontCare, dontCare), 1);
	//chaseEnemy necessita : player viu, enemy viu -> enemy close
	Action chaseEnemy("chase enemy", WorldState(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isTrue),
		WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isTrue, dontCare), 10);
	//aim necessita : has Weapon, player viu, enemy viu, enemy visible -> enemy in line
	Action aim("aim", WorldState(isTrue, isTrue, dontCare, dontCare, isTrue, dontCare, dontCare, isTrue),
		WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, isTrue, dontCare, dontCare), 7);
	//shoot necessita : has Weapon, player viu, enemy viu, weapon loaded, enemy in line -> enemy dead
	Action shoot("shoot", WorldState(isTrue, isTrue, isTrue, dontCare, isTrue, isTrue, dontCare, isTrue),
		WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isFalse), 30);
	//reload necessita : player viu, tenir arma -> arma carregada
	Action reload("reload", WorldState(isTrue, isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare),
		WorldState(dontCare, dontCare, isTrue, dontCare, dontCare, dontCare, dontCare, dontCare), 5);
	//use bomb necessita : player viu, has bomb,enemy visible,enemy close, enemy viu -> enemy dead
	Action useBomb("use bomb", WorldState(isTrue, dontCare, dontCare, isTrue, isTrue, dontCare, isTrue, isTrue),
		WorldState(dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, isFalse), 50);

	vector <Action> allPossibleActions;
	allPossibleActions.push_back(scout);
	allPossibleActions.push_back(searchWeapon);
	allPossibleActions.push_back(craftBomb);
	allPossibleActions.push_back(chaseEnemy);
	allPossibleActions.push_back(aim);
	allPossibleActions.push_back(shoot);
	allPossibleActions.push_back(reload);
	allPossibleActions.push_back(useBomb);

	int idCounter = 0;//per poder ordenar el mapa utilitzem ids per els diferents estats
	
	//Definim el primer estat en que nomes estàs viu i no tens res més
	WorldState firstState(isTrue, isFalse, isFalse, isFalse, isFalse, isFalse, isFalse, isTrue);//com que no l'hem tocat, la prioritat sera 0
	firstState.id = idCounter++;
	
	//Creem un estat goal random
	int hasWeapon = rand() % 3; int loadedWeapon = rand() % 3; int hasBomb = rand() % 3; int visibleEnemy = rand() % 3; int linedEnemy = rand() % 3; int closeEnemy = rand() % 3; int deadEnemy = rand() % 3;
	WorldState goal(isTrue, isTrue, (ourBoolean)loadedWeapon, isTrue, (ourBoolean)visibleEnemy, (ourBoolean)linedEnemy, (ourBoolean)closeEnemy, (ourBoolean)deadEnemy);	
	cout << "GOAL STATE : "; goal.print(); cout << endl;
	
	//La cua ordenara segons el valor prioritat de la classe worldState amb el PriorityComparision que hem fet
	priority_queue<WorldState, vector<WorldState>, PriorityComparision> frontier;	
	frontier.emplace(firstState); 
	
	//Declarem els tres mapes utilitzant el nostre comparador que ens el demana per ordenar les claus
	map<WorldState, WorldState, WorldStateComparator> came_from;

	map<WorldState, Action, WorldStateComparator> detonator;

	map <WorldState, int, WorldStateComparator> cost_so_far;	
	cost_so_far[firstState] = 0;
	int newCost;

	WorldState current;
	
	//Proves mapa	
	/*WorldState prova(dontCare, dontCare, dontCare, dontCare, isTrue, dontCare, dontCare, dontCare);
	prova.id = 1;
	cost_so_far[prova] = 20; 

	cost_so_far[firstState] = 15;//per canviar el valor amb la mateixa clau s'ha de fer aixi
								 
	cout << "COST SO FAR ARRAY" << endl;
	map <WorldState, int>::iterator it = cost_so_far.begin();
	while (it != cost_so_far.end())
	{
		cout << it->second << endl;
		it++;
	}*/
	 

	while (!frontier.empty()) {

		//Agafem l'estat amb més prioritat de la frontera
		current = frontier.top();
		frontier.pop();		
		
		//Creem els estats veïns que poguem	
		for (int i = 0; i < allPossibleActions.size(); i++) {
			if (current.CanApplyAction(allPossibleActions[i])) {
				
				//Creem el nou estat aplicant l'accio que toqui
				WorldState newState = current.ApplyAction(allPossibleActions[i]);				
				//cout << newState.allVariables[0] << "," << newState.allVariables[1] << "," << newState.allVariables[2] << "," << newState.allVariables[3] << "," << newState.allVariables[4] << "," << newState.allVariables[5] << "," << newState.allVariables[6] << "," << newState.allVariables[7] << endl;
				
				//Calculem nou cost
				newCost = GetValueInMap(cost_so_far, current) + allPossibleActions[i].cost;
				//si és el primer cop que el visitem o hem trobat un cost més petit l'afegim al map
				if (!FindKeyInMap(cost_so_far, newState) || newCost < GetValueInMap(cost_so_far, newState)){
					
					//Creem nou id perque el map pugui ordenar-lo com a clau
					newState.id = idCounter++;

					//Afegim al mapa de cost acumulat de cada estat
					cost_so_far[newState] = newCost;

					//calculem prioritat i afegim a la frontera
					newState.priority = newCost + newState.HeuristicTo(goal);					
					frontier.push(newState);
					
					//Afegim al came from per recuperar despres per quins estats hem passat
					came_from[newState] = current;

					//Setegem quin és l'acció que ha provocat aquest estat
					detonator[newState] = allPossibleActions[i];

					//Si hem arrivat al estat que volem sortim
					if (newState.GoalReached(goal)) {
						cout << "Goal reached!" << endl;
						goto createPlan;
					}

				}
			}			
		}		
	}

	createPlan:
	
	//Primer agafem l'últim estat, pq si té don't care el que hem triat sera diferent del últim real
	map <WorldState, WorldState>::iterator it = came_from.end();
	it--;
	WorldState lastState = it->first;	

	//Anem imprimint tots els estats que hem anat passant i les accions que els han provocat
	while (lastState != firstState) {
		lastState.print();
		Action temp = GetValueInMap(detonator, lastState);
		temp.printName();
		lastState = GetValueInMap(came_from, lastState);
	}
	cout << "FIRST STATE : ";
	firstState.print();
	cout << endl;	

}