#include "ListLoading.h"
#include <algorithm>
#include <conio.h>
#include <time.h>

void sortValues(std::vector<std::pair<int, int>>* values, bool print = true);
int  selectWord(std::vector<std::pair<int, int>>* values, int difficulty = -1);

int main()
{
	srand(time(NULL));

	std::vector<std::string> words          = loadWords("Word Lists/lowercaseAll.txt");
	std::vector<std::pair<int, int>> values = loadValues("Word Lists/rowClassified.txt");

	sortValues(&values);

	int input  = 0;
	while (input != 27) 
	{
		int index = selectWord(&values, -1);

		std::cout << "The word is: " << words[index] << "\n";

		input = _getch();
	}
}

void sortValues(std::vector<std::pair<int, int>>* values, bool print)
{
	std::sort(values->begin(), values->end());

	int topIndex = -1;
	int bottomIndex = -1;

	for (int i = 0; i < values->size(); i++)
	{
		if (values->at(i).first == 1 && topIndex == -1)
			topIndex = i;

		else if (values->at(i).first == 2 && bottomIndex == -1)
			bottomIndex = i;

		if (topIndex != -1 && bottomIndex != -1)
			break;
	}

	if(print)
		std::cout << "Easy:   " << topIndex << "\nMedium: " << bottomIndex - topIndex << "\nHard:   " << values->size() - bottomIndex << "\nTotal:  " << values->size() << "\n\n\n";
}

int selectWord(std::vector<std::pair<int, int>>* values, int difficulty)
{
	static int previousDifficulty = -2;

	int size = values->size();

	if (difficulty != -1)
	{
		for(int i = 0; i < values->size(); i++)
			if (values->at(i).first > difficulty)
			{
				size = i;
				break;
			}
	}

	if (difficulty != previousDifficulty)
	{
		std::cout << "Selecting from a pool of: " << size << " words.\n\n";

		previousDifficulty = difficulty;
	}

	int selection = rand() % size;
	
	return values->at(selection).second;
}