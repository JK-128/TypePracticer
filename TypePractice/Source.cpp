#include "ListLoading.h"

int main()
{
	std::vector<std::string> words = loadWords("Word Lists/lowercaseAll.txt");
	std::vector<int> values        = loadValues("Word Lists/rowClassified.txt");

	for (int i = 0; i < values.size(); i++)
		if (values[i] == 1)
			std::cout << i << " | " << words[i] << "\n";

	while (1) {}
}

/*	STEPS:
* -----------
*  1. Get a list of every word in the English language.
*  2. Iterate through and assign each word a number, 0 for home row, 1 for above and 2 for below.
*  3. When the program runs, choose random words from list up to the selected difficulty (0 - 2).
*/