#include <iostream>
#include "Game.h"

int main()
{
	//Initialize game engine
	Game* pgame = new Game;

	//Game loop
	while (pgame->running() || pgame->reset)//checks whether window is open
	{
		if (pgame->reset)
		{
			delete pgame;
			pgame = new Game;
			pgame->reset = false;
		}
		//Update
		pgame->update();
		//Rendering
		pgame->render();
	}
	//end
	//release memory of pointer pgame
	delete pgame;
	return 0;
}
