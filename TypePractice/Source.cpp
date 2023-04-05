#include "Game.h"
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/TextRenderer.h"
//#include <thread>

int main()
{
	Window window(640, 480, "Typing Practice");

	windowWidth  = 640;
	windowHeight = 480;

	Game game;

	game.passWindow(&window);

	std::string wordsPath  = "Word Lists/lowercaseAll.txt";
	std::string valuesPath = "Word Lists/rowClassified.txt";

	game.setup(wordsPath, valuesPath);

	while (window.exists())
	{
		window.clear();
		
		game.update();

		window.swap();
		window.poll();

		if (game.shouldExit())
			window.close();
	}
}