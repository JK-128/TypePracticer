#include "ListLoading.h"
#include "Utilities.h"
#include "Timing.h"

struct Attempt
{
	std::string input;

	int code;
	int mistakes = -1;
	
	timedata duration;
};

Attempt userAttempt(std::string word);

int main()
{
	srand((uint16_t)time(NULL));

	int sentenceLength = 3;

	ValuesData data = loadData("Word Lists/lowercaseAll.txt", "Word Lists/rowClassified.txt");

	sortValues(&data.values, data.levelCount, true);

	int input =  keyLevel;
	int level = data.levelCount - 1;

	while (input != keyExit) 
	{
		if (input == keyLevel)
		{
			input = setDifficulty(data.levelCount);

			if (input != keyExit)
			{
				std::cout << "\n";
				level = (char)input - keyOffset;
			}
		}
		else if (input == keyLength)
		{
			std::cout << "Set sentence length: ";

			input = _getch();

			if (input - keyOffset > 0 && input - keyOffset < 10)
				sentenceLength = input - keyOffset;

			std::cout << "New sentence length: " << sentenceLength << "\n\n";
		}

		std::vector<int> indexes;
		std::string sentence = "";

		for (int i = 0; i < sentenceLength; i++)
		{
			indexes.push_back(selectWord(&data.values, level));

			if (i != 0)
				sentence += " ";

			sentence += data.words[indexes[i]];
		}

		std::cout << sentence << "\n";

		Attempt attempt = userAttempt(sentence);

		input = attempt.code;

		if (attempt.mistakes != -1)
		{
			std::cout << "Completed in: " << getTimePretty(attempt.duration) << "\n";
			std::cout << "With " << attempt.mistakes << " mistakes.\n";
			std::cout << "WPM: " << getWPM(attempt.duration, sentenceLength) << "\n\n";
		}
	}
}

Attempt userAttempt(std::string word)
{
	Attempt attempt;

	int count    = 0;
	int input    = 0;
	int mistakes = 0;
	int letters  = 0;

	std::vector<int> mistakeIndexes;

	//Gathers a value for the time the attempt begins.
	timedata preAttempt = getCurrentTime();

	bool hasTyped = false;
	while (input != keyLevel && input != keyExit && input != keyNext && input != keyLength)
	{
		input = _getch();

		if (input != keyNext && input != keyLevel && input != keyLength)
		{
			if (!hasTyped)
			{
				//Updates the start time based on the first keystroke.
				preAttempt = getCurrentTime();
				hasTyped = true;
			}

			attempt.input.push_back((char)input);

			if (word.at(count) == (char)input)
				std::cout << word.at(count);
			else
			{
				std::cout << "_";
				mistakes++;
				mistakeIndexes.push_back(count);
			}

			letters++;
		}

		count++;

		if (count >= word.length())
			count = (int)word.length() - 1;
	}
	attempt.code = input;

	//Gathers mistakes for typing too much/little
	if (word.length() != attempt.input.length())
		mistakes += abs((int)word.length() - (int)attempt.input.length());

	if (hasTyped)
	{
		attempt.mistakes = mistakes;

		if (mistakes > 0)
		{
			std::cout << "\n\n[";
			for (int i = 0; i < mistakeIndexes.size(); i++)
				std::cout << word[mistakeIndexes[i]];

			std::cout << "]\n";
		}

		int accuracy = int((1.0f - ((float)mistakes / (float)letters)) * 100.0f);

		std::cout << "\n" << accuracy << "% accuracy.\n\n";
	}

	timedata duration = getTimeDifference(preAttempt);
	
	attempt.duration = duration;

	return attempt;
}

// TO DO: Clean everything up and improve before the refactor.
// TO DO: Split everything into functions in preparation for addition of graphics so 
//        logic and function calls are the same, just function bodies need to be changed.
// TO DO: Bring in something like SFML or even OpenGL to make it actually look nice.