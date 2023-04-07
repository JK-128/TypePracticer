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

	std::vector<int> m_mistakes;
	std::vector<int> m_spaces;
	std::vector<int> m_breaks;

	std::vector<std::string> m_sentenceRender;

	ValuesData m_data;
	Attempt m_attempt;

	TextRenderer m_tr;

	timedata m_clock;

	Window* m_window;

	bool m_finished = true;
	bool m_hasTyped = false;

	float m_textScale  =  1.0f;
	float m_textOffset = 10.0f;

public:
	int getInput();

	float getAccuracy();
	
	void setup(std::string wordsPath, std::string valuesPath);
	void setNextSentence();
	void passWindow(Window* window);
	void update();
	void handleInput();
	void attempt();
	void printSentence(glm::vec4 color);

	void printText(std::string text, glm::vec4 color = glm::vec4(1.0f), bool setSpaces = false);

	float getLetterX(int index);

	void showAttemptStats();
	void updateDifficulty();
	void updateSentenceLength();
	void nextSet();


	bool shouldExit();
};