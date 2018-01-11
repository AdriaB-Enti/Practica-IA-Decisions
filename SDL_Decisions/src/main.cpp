#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "ScenePlanning.h"

#include "State.h"
#include "Transition.h"
#include "GOAP.h"

#define FRAMES_PER_SEC 30

using namespace std;

bool prova() {
	std::cout << "hola" << std::endl;
	return true;
}
void PassPtr(bool(*pt2Func)())
{
	(*pt2Func)();
}
int main(int argc, char ** argv)
{
	//PROVEES
	//PassPtr(prova);	
	WorldState w1(isTrue, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare);
	WorldState w2(isFalse, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare, dontCare);
	bool prova = w1 == w2;
	cout << prova << endl;
	//ENDPROVEES

	bool quit = false;
	SDL_Event event;
	int this_tick = 0;
	int next_tick = 1000/FRAMES_PER_SEC;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new ScenePlanning;
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		this_tick = SDL_GetTicks();
		if (this_tick < next_tick)
		{
			SDL_Delay(next_tick - this_tick);
		}
		next_tick = this_tick + (1000 / FRAMES_PER_SEC);

		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1)
			{
				delete(curr_scene);
				curr_scene = new ScenePlanning;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2)
			{
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3)
			{
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}



