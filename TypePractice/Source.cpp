#define GAME_ACTIVE   1
#define WINDOW_ACTIVE 1

#include "Game.h"
#include "Graphics/Window.h"
#include <thread>

int main()
{
	Game game;

	std::string wordsPath  = "Word Lists/lowercaseAll.txt";
	std::string valuesPath = "Word Lists/rowClassified.txt";

	std::thread gameThread;
	if (GAME_ACTIVE)
		gameThread = std::thread(gameLoop, &game, wordsPath, valuesPath);

	bool gameRunning = true;

	if (WINDOW_ACTIVE)
	{
		Window window(640, 480, "Typing Practice");

		while (window.exists())
		{
			window.draw();

			gameRunning = game.shouldExit();

			if (!gameRunning)
				window.close();
		}
	}

	if(GAME_ACTIVE)
		gameThread.join();
}

/*	Port over shader code.
*	Port over text rendering code.
*	Integrate with the 'game' so far.
*/