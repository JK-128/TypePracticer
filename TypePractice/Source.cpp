#define GAME_ACTIVE 1
#define WINDOW_ACTIVE 1

#include "Game.h"
#include "Graphics/Window.h"
#include <thread>

int main()
{
	Game game;

	std::thread gameThread;
	if (GAME_ACTIVE)
		gameThread = std::thread(gameLoop, &game);

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