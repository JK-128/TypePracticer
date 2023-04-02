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

		int index = selectWord(&data.values, level);

		std::cout << "The word is: " << data.words[index] << "\n";

		input = userAttempt(data.words[index]).code;
	}
}

Attempt userAttempt(std::string word)
{
	Attempt attempt;

	int count = 0;
	int input = 0;

	while (input != 32 && input != 47 && input != 27 && input != 13)
	{
		input = _getch();

		if (input != 32 && input != 13 && input != 47)
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