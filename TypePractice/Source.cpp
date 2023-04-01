#include "ListLoading.h"
#include "Utilities.h"
#include <time.h>

int main()
{
	srand(time(NULL));

	std::vector<std::string> words          = loadWords("Word Lists/lowercaseAll.txt");
	std::vector<std::pair<int, int>> values = loadValues("Word Lists/rowClassified.txt");

	sortValues(&values, true);

	int input =  0;
	int level = -1;

	while (input != 27) 
	{
		int index = selectWord(&values, level);

		std::cout << "The word is: " << words[index] << "\n";

		input = _getch();

		if (input == 32)
		{
			input = setDifficulty();

			if (input != 27)
				level = (char)input - 48;
		}
	}
}