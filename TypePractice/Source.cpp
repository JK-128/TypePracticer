#include "ListLoading.h"
#include "Utilities.h"
#include <time.h>

struct Attempt
{
	std::string input;
	int code;
};

Attempt userAttempt(std::string word);

int main()
{
	srand(time(NULL));

	int sentenceLength = 3;

	ValuesData data = loadData("Word Lists/lowercaseAll.txt", "Word Lists/rowClassified.txt");

	sortValues(&data.values, data.levelCount, true);

	int input =  47;
	int level = data.levelCount - 1;

	while (input != 27) 
	{
		if (input == 47)
		{
			input = setDifficulty(data.levelCount);

			if (input != 27)
			{
				std::cout << "\n";
				level = (char)input - 48;
			}
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

		input = userAttempt(sentence).code;
		/*
		std::cout << "\n\n";
		
		for (int i = 0; i < sentenceLength; i++)
		{
			input = userAttempt(data.words[indexes[i]]).code;

			if (input == 27 || input == 47)
				break;
		}*/
	}
}

Attempt userAttempt(std::string word)
{
	Attempt attempt;

	int count = 0;
	int input = 0;

	while (input != 47 && input != 27 && input != 13)
	{
		input = _getch();

		if (input != 13 && input != 47)
		{
			attempt.input.push_back((char)input);

			if (word.at(count) == (char)input)
				std::cout << "O";
			else
				std::cout << "X";
		}

		count++;

		if (count >= word.length())
			count = word.length() - 1;
	}
	attempt.code = input;

	std::cout << "\nAttempt: [" << attempt.input << "]\n";

	if (attempt.input == word) 
		std::cout << "\ncorrect\n\n";
	else
		std::cout << "\nIncorrect\n\n";

	return attempt;
}

// TO DO: String the above along to test for 100 words, then allow for a variable target.
// TO DO: Put in performance trackers (time, mistakes, etc).
// TO DO: Bring in something like SFML or even OpenGL to make it actually look nice.