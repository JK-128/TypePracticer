#include "ListLoading.h"
#include "Utilities.h"
#include <time.h>

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

		/*
		std::string attempt;

		std::cout << ">> ";
		std::getline(std::cin, attempt);


		*/

		input = -1;

		std::string attempt = "";
		while (input != 32 && input != 47 && input != 27 && input != 13)
		{
			input = _getch();

			if(input != 32 && input != 13 && input != 47)
				attempt.push_back((char)input);
		}
		std::cout << "Attempt: [" << attempt << "]\n";

		if (attempt == data.words[index])
			std::cout << "\nCorrect!\n\n";
		else
			std::cout << "\nIncorrect\n\n";

		//input = _getch();

	}
}
// Try _getch() in a loop to get each character as it is typed. Then exit the loop after the space key had been pressed.
// Hopefully this method will 1. work and 2. be easily expandible for more than one word.

// TO DO: Figure out how to take in input via typing words that match the chosen random word.
// TO DO: String the above along to test for 100 words, then allow for a variable target.
// TO DO: Put in performance trackers (time, mistakes, etc).
// TO DO: Bring in something like SFML or even OpenGL to make it actually look nice.