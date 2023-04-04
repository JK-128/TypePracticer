#include "Game.h"
#include "Graphics/Window.h"

int main()
{
	Game game;

	game.setup("Word Lists/lowercaseAll.txt", "Word Lists/rowClassified.txt");

	Window window(640, 480, "Typing Practice");

	while (!game.shouldExit()) 
	{
		game.nextSet();

		window.draw();
	}
}

//TO DO: Git branch to make a new branch to develop graphics with.
//       Develop these graphics (90% portable from previous projects).
//       Make any necessary changes/improvements.
//       Merge branch.
//       Done.