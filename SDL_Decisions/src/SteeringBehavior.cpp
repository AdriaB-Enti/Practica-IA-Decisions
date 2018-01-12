#include "SteeringBehavior.h"

using namespace std;

SteeringBehavior::SteeringBehavior()
{
}

SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desired_velocity = target - agent->position;
	desired_velocity.Normalize();
	desired_velocity *= agent->max_velocity;

	Vector2D steering_force = desired_velocity - agent->velocity;
	steering_force /= agent->max_velocity;
	steering_force = steering_force * agent->max_force;

	return steering_force;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, int slow_radius, float dtime)
{
	float slow_factor = (target - agent->position).Length() / slow_radius;

	Vector2D desired_velocity = target - agent->position;
	desired_velocity.Normalize();
	if ((target - agent->position).Length() > slow_radius)
		desired_velocity *= agent->max_velocity;
	else
		desired_velocity *= agent->max_velocity * slow_factor;

	Vector2D steering_force = desired_velocity - agent->velocity;
	//steering_force /= agent->max_velocity;
	//steering_force = steering_force * agent->max_force;

	return steering_force;
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, int slow_radius, float dtime)
{
	return Arrive(agent, target->position, slow_radius, dtime);
}


std::vector<Vector2D> SteeringBehavior::SceneGreedyBFS(Graph graph, Vector2D firstPos, Vector2D goal) {

	vector<Vector2D> path;

	priority_queue<Node, vector<Node>, PriorityComparision> frontier;
	float priority;
	

	map<Vector2D, Vector2D> came_from;

	struct Node firstNode = { firstPos, 1 };
	frontier.emplace(firstNode);
	struct Node current;

	int totalExploredNodes = 0;
	int visitedNodes = 0;


	//Iterem la frontera
	while (!frontier.empty()) {
		current = frontier.top();
		frontier.pop();//el borrem ara perque si després afegim un amb més prioritat no borrarem el que toca

		for each (Connection c in graph.GetConnections(current.position)) // comprovem els seus veïns
		{
			totalExploredNodes++;

			if (!FindInMap(came_from, c.getToNode()) && c.getToNode() != firstPos) { //si no els haviem visitat els afegim a frontera

				visitedNodes++;
				//afegim nou cost
				
				priority = ManhattanDistance(c.getToNode(), goal);
				
				Node next = { c.getToNode(), priority };
				frontier.push(next);

				//afegim al came_from per recuperar despres el path
				came_from[c.getToNode()] = current.position;

				if (c.getToNode() == goal) {
					goto createpath;
				}
			}

		}

	}

createpath:
	//Creem el camí
	Vector2D posInPath;

	posInPath = goal;
	path.push_back(posInPath);
	while (posInPath != firstPos) {
		posInPath = ReturnMapValue(came_from, posInPath);
		path.insert(path.begin(), posInPath);
	}
	//cout << "NODES EXPLORATS: " << totalExploredNodes << ", NODES VISITATS : " << visitedNodes << endl;
	return path;
}


float SteeringBehavior::ManhattanDistance(Vector2D start, Vector2D goal) {

	//Com que el cost minim entre nodes es 1 hem de passar aquestes distances a posicio en la grid per a que pugui coincidir
	Vector2D startCell = Vector2D((float)((int)start.x / CELL_SIZE), (float)((int)start.y / CELL_SIZE));
	Vector2D goalCell = Vector2D((float)((int)goal.x / CELL_SIZE), (float)((int)goal.y / CELL_SIZE));
	//cout << "START CELL : " << startCell.x << "," << startCell.y << ", END CELL: " << goalCell.x << "," << goalCell.y << endl;

	float dx = abs(startCell.x - goalCell.x);
	float dy = abs(startCell.y - goalCell.y);
	return dx + dy; //No multipliquem per res perque el cos minim entre dos nodes es 1
}

/**/

bool SteeringBehavior::FindInMap(std::map<Vector2D, Vector2D> m, Vector2D objective) {
	// Creem iterador
	std::map<Vector2D, Vector2D>::iterator it = m.begin();

	// Iterate over the map using Iterator till end.
	while (it != m.end())
	{
		if (it->first == objective) {
			return true;
		}
		it++;
	}
	return false;
}

bool SteeringBehavior::FindInMap(std::map<Vector2D, float> m, Vector2D objective) {
	// Creem iterador
	std::map<Vector2D, float>::iterator it = m.begin();

	// Iterate over the map using Iterator till end.
	while (it != m.end())
	{
		if (it->first == objective) {
			return true;
		}
		it++;
	}
	return false;
}

Vector2D SteeringBehavior::ReturnMapValue(std::map<Vector2D, Vector2D> m, Vector2D objective) {
	std::map<Vector2D, Vector2D>::iterator it = m.begin();

	// Iterate over the map using Iterator till end.
	while (it != m.end())
	{
		if (it->first == objective) {
			return it->second;
		}
		it++;
	}	
}

float SteeringBehavior::ReturnMapValue(std::map<Vector2D, float> m, Vector2D objective) {
	std::map<Vector2D, float>::iterator it = m.begin();

	// Iterate over the map using Iterator till end.
	while (it != m.end())
	{
		if (it->first == objective) {
			return it->second;
		}
		it++;
	}
}
