#include "Game.h"

int main()
{
	Game game;

	game.setup("Word Lists/lowercaseAll.txt", "Word Lists/rowClassified.txt");

	while (!game.shouldExit()) 
	{
		game.nextSet();
	}
}


// TO DO: Clean everything up and improve before the refactor.
// TO DO: Split everything into functions in preparation for addition of graphics so 
//        logic and function calls are the same, just function bodies need to be changed.
// TO DO: Bring in something like SFML or even OpenGL to make it actually look nice.