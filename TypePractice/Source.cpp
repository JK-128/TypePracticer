#include "Game.h"
#include "Graphics/Window.h"
#include <thread>

void gameLoop(Game* game);

int main()
{
	Game game;

	game.setup("Word Lists/lowercaseAll.txt", "Word Lists/rowClassified.txt");

	Window window(640, 480, "Typing Practice");

	std::thread gameThread(gameLoop, &game);

	while (window.exists()) 
	{
		window.draw();
	}
}

void gameLoop(Game* game)
{
	while (!game->shouldExit())
	{
		game->nextSet();
	}
}

//TO DO: Develop these graphics (90% portable from previous projects).
//       Make any necessary changes/improvements.
//       Merge branch.
//       Done.