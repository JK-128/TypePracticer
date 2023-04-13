#include "Game.h"

void Game::setup(std::string wordsPath, std::string valuesPath)
{
	srand((uint16_t)time(NULL));

	m_data = loadData(wordsPath, valuesPath);

	sortValues(&m_data.values, m_data.levelCount, true);

	m_level = m_data.levelCount - 1;

	m_attempt.code = keyLevel;
}

void Game::setNextSentence()
{
	std::vector<int> indexes;
	std::string sentence = "";
	int index;

	for (int i = 0; i < m_sentenceLength; i++)
	{
		index = selectWord(&m_data.values, m_level);

		indexes.push_back(index);

		if (i != 0) sentence += " ";

		sentence += m_data.words[indexes[i]];
	}

	m_sentence = sentence;
}

//
//{
	/*
	Attempt attempt;

	std::vector<int> mistakeIndexes;
	
	timedata preAttempt = getCurrentTime();

	int count    = 0;
	int input    = 0;
	int mistakes = 0;
	int letters  = 0;

	bool hasTyped = false;

	while (input != keyLevel && input != keyExit && input != keyNext && input != keyLength)
	{
		input = _getch();

		if (input != keyNext && input != keyLevel && input != keyLength)
		{
			if (!hasTyped)
			{
				preAttempt = getCurrentTime();
				hasTyped = true;
			}

			attempt.input.push_back((char)input);

			if (m_sentence.at(count) == (char)input)
				std::cout << m_sentence.at(count);
			else
			{
				std::cout << "_";
				mistakes++;
				mistakeIndexes.push_back(count);
			}

			letters++;
		}

		count++;

		if (count >= m_sentence.length())
			count = (int)m_sentence.length() - 1;
	}
	attempt.code = input;

	int lengthDiff = abs((int)m_sentence.length() - (int)attempt.input.length());
	
	if (lengthDiff != 0)
		mistakes += lengthDiff;

	if (hasTyped)
	{
		attempt.mistakes = mistakes;

		if (mistakes > 0)
		{
			std::cout << "\n\n[";

			for (int i = 0; i < mistakeIndexes.size(); i++)
				std::cout << m_sentence[mistakeIndexes[i]];

			std::cout << "]\n";
		}

		int accuracy = int((1.0f - ((float)mistakes / (float)letters)) * 100.0f);
		
		std::cout << "\n" << accuracy << "% accuracy.\n\n";
	}

	timedata duration = getTimeDifference(preAttempt);
	
	attempt.duration = duration;

	m_attempt = attempt;
	*/
//}

void Game::showAttemptStats()
{
	if (m_attempt.mistakes == -1)
		return;

	std::string attemptDuration = getTimePretty(m_attempt.duration);

	float attemptWPM = getWPM(m_attempt.duration, m_sentenceLength);

	std::cout << "Completed in: " << attemptDuration << "\n";
	std::cout << "With: " << m_attempt.mistakes << " mistakes.\n";
	std::cout << "WPM:  " << attemptWPM << "\n\n";
}

void Game::updateDifficulty()
{
	m_attempt.code = 1;// setDifficulty(m_data.levelCount);

	if (m_attempt.code != keyExit)
	{
		std::cout << "\n";
		m_level = (char)m_attempt.code - keyOffset;
	}
}

void Game::updateSentenceLength()
{
	std::cout << "Set sentence length: ";

	int input = _getch();

	if ((input - keyOffset) > 0 && (input - keyOffset) < 10)
		m_sentenceLength = input - keyOffset;

	std::cout << "New sentence length: " << m_sentenceLength << "\n\n";
}

void Game::passWindow(Window* window)
{
	m_window = window;
}

void Game::update()
{
	if (m_attempt.code == keyNext)
		m_finished = true;

	if (m_finished)
	{
		m_mistakes.clear();
		m_sentenceRender.clear();
		m_attempt.input.clear();

		m_attempt.mistakes = 0;

		m_finished = false;
		m_hasTyped = false;

		setNextSentence();
	}

	attempt();

	printText(m_sentence, glm::vec4(1.0f), true);
	printText(m_attempt.input, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	if (m_hasTyped)
	{
		timedata diff = getTimeDifference(m_clock);
		std::string diffStr = getTime(diff);

		float accuracy = getAccuracy();

		if (m_attempt.input[m_attempt.input.size() - 1] == ' ')
			m_wordsPerMinute = getWPM(diff, m_attempt.input.size());

		std::string accString = std::to_string(accuracy);

		m_tr.renderText(diffStr, 10.0f, 450.0f);
		m_tr.renderText(trimFloat(accString) + "%", 200.0f, 450.0f);
	}

	if (m_mistakes.size() > 0)
	{
		std::string mistakesString = "";

		for (int i = 0; i < m_sentence.length(); i++)
		{
			bool isMistake = false;

			for (int j = 0; j < m_mistakes.size(); j++)
			{
				if (m_mistakes[j] == i)
				{
					mistakesString += m_sentence[i];
					isMistake = true;
					break;
				}
			}

			if (!isMistake)
				mistakesString += " ";
		}
		printText(mistakesString, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

float Game::getAccuracy()
{
	int mistakes = m_attempt.mistakes;

	if (mistakes == 0)
		return 100.0f;

	float percent = 100.0f - (((float)mistakes / (float)m_attempt.input.length()) * 100.0f);

	return percent;
}

void Game::attempt()
{
	int key = getInput();

	if (key == -1)
		return;

	if (key == keyExit)
	{
		m_attempt.code = keyExit;
		return;
	}
	else if (key == keyNext)
	{
		m_finished = true;
		return;
	}

	if (!m_hasTyped)
	{
		m_hasTyped = true;
		m_clock = getCurrentTime();
	}

	if (key != GLFW_KEY_SPACE)
		key += 32;

	int size = m_attempt.input.size();

	if (size >= m_sentence.length())
	{
		size = -1;
		m_attempt.mistakes++;
	}

	if (size != -1)
		if (key != m_sentence[size])
		{
			m_attempt.mistakes++;
			key = keyError;
			m_mistakes.push_back(size);
		}

	m_attempt.input.push_back((char)key);
}

int Game::getInput()
{
	if (keyActions.size() < 1)
		return -1;

	int key = keyActions[0];

	keyActions.erase(keyActions.begin());

	return key;
}

bool Game::shouldExit()
{
	return(m_attempt.code == keyExit);
}

void Game::printText(std::string text, glm::vec4 color, bool setSpaces)
{
	int difference = m_sentence.length() - text.length();
	for (int i = 0; i < difference; i++)
		text += '#';

	if (setSpaces)
	{
		m_spaces.clear();
		m_breaks.clear();

		m_breaks.push_back(0);

		for (int i = 0; i < text.length(); i++)
			if (text[i] == ' ')
				m_spaces.push_back(i + 1);

		int lastBreak = 0;
		for (int i = 0; i < m_spaces.size(); i++)
			if (m_spaces[i] - lastBreak > 25)
			{
				m_breaks.push_back(m_spaces[i]);
				lastBreak = m_spaces[i];
			}

		m_breaks.push_back(text.length());
	}

	for (int i = 1; i < m_breaks.size(); i++)
	{
		std::string newLine = text.substr(m_breaks[i - 1], m_breaks[i] - m_breaks[i - 1]);
		m_sentenceRender.push_back(newLine);
	}

	printSentence(color);
	m_sentenceRender.clear();
}

void Game::printSentence(glm::vec4 color)
{
	for (int i = 0; i < m_sentenceRender.size(); i++)
	{
		m_tr.renderText(m_sentenceRender[i], m_textOffset, 400.0f - (50.0f * i), m_textScale, color);
	}
}

float Game::getLetterX(int index)
{
	return m_textScale * (16.0f * index);
}