#pragma once
#include "Core/Definitions.h"
#include "Core/ListLoading.h"
#include "Core/Timing.h"
#include "Core/Utilities.h"
#include "Graphics/TextRenderer.h"
#include "Graphics/Window.h"

struct Attempt
{
	std::string input;

	int code = -1;
	int mistakes = -1;

	timedata duration;
};

class Game
{
private:
	int m_sentenceLength = 3;
	int m_level;

	std::string m_sentence;

	ValuesData m_data;
	Attempt m_attempt;
	TextRenderer m_tr;
	
	Window* m_window;

	bool m_finished = true;

public:
	void setup(std::string wordsPath, std::string valuesPath);
	void setNextSentence();
	void passWindow(Window* window);
	void update();
	void handleInput();

	void attempt();
	void showAttemptStats();
	void updateDifficulty();
	void updateSentenceLength();
	void nextSet();


	bool shouldExit();
};