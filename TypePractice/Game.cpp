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

	std::cout << sentence << "\n";
}

void Game::attempt()
{
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
}

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
	m_attempt.code = setDifficulty(m_data.levelCount);

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

void Game::nextSet()
{
	if (m_attempt.code == keyLevel)
		updateDifficulty();

	if (m_attempt.code == keyLength)
		updateSentenceLength();

	if (m_attempt.code != keyExit)
	{
		setNextSentence();
		attempt();
		showAttemptStats();
	}
}

bool Game::shouldExit()
{
	return(m_attempt.code == keyExit);
}

void gameLoop(Game* game, std::string wordsPath, std::string valuesPath)
{
	game->setup(wordsPath, valuesPath);

	while (!game->shouldExit())
	{
		game->nextSet();
	}
}