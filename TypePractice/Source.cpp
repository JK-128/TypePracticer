#include "ListLoading.h"
#include "Utilities.h"
#include <time.h>

int main()
{
	srand(time(NULL));

	ValuesData data = loadData("Word Lists/lowercaseAll.txt", "Word Lists/rowClassified.txt");

	sortValues(&data.values, data.levelCount, true);

	int input =  0;
	int level = data.levelCount - 1;

	while (input != 27) 
	{
		int index = selectWord(&data.values, level);

		std::cout << "The word is: " << data.words[index] << "\n";

		input = _getch();

		if (input == 32)
		{
			input = setDifficulty(data.levelCount);

			if (input != 27)
			{
				std::cout << "\n";
				level = (char)input - 48;
			}
		}
	}
}

// TO DO: Change the difficulty classifier script to include at the top of the file the number of difficulty levels.
// TO DO: Figure out how to take in input via typing words that match the chosen random word.
// TO DO: String the above along to test for 100 words, then allow for a variable target.
// TO DO: Put in performance trackers (time, mistakes, etc).
// TO DO: Bring in something like SFML or even OpenGL to make it actually look nice.