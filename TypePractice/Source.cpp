#define GAME_ACTIVE   0
#define WINDOW_ACTIVE 1

#include "Game.h"
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/TextRenderer.h"
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

		windowWidth  = 640;
		windowHeight = 480;

		Shader shaderTest("Shaders/textVert.glsl", "Shaders/textFrag.glsl");

		TextRenderer tr;

		while (window.exists())
		{
			window.clear();

			tr.renderText("TEST0123456789", 0.5f, 0.5f);

			window.swap();
			window.poll();

			gameRunning = game.shouldExit();

			if (!gameRunning && GAME_ACTIVE)
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