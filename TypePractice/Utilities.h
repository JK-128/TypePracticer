#pragma once
#include <algorithm>
#include <vector>
#include <conio.h>

void sortValues(std::vector<std::pair<int, int>>* values, bool print = false)
{
	std::sort(values->begin(), values->end());

	int topIndex = -1;
	int botIndex = -1;

	for (int i = 0; i < values->size(); i++)
	{
		if (values->at(i).first == 1 && topIndex == -1)
			topIndex = i;
		
		else if (values->at(i).first == 2 && botIndex == -1)
			botIndex = i;

		if (topIndex != -1 && botIndex != -1)
			break;
	}

	if (print)
		std::cout << "Easy:   " << topIndex << "\nMedium: " << botIndex - topIndex << "\nHard:   " << values->size() - botIndex << "\nTotal:  " << values->size() << "\n\n\n";
}

int selectWord(std::vector<std::pair<int, int>>* values, int difficulty)
{
	static int previousDifficulty = -2;

	int size = values->size();

	if (difficulty != -1)
	{
		for (int i = 0; i < values->size(); i++)
			if (values->at(i).first > difficulty)
			{
				size = i;
				break;
			}
	}

	if (difficulty != previousDifficulty)
	{
		std::cout << "Selecting from a pool of: [" << size << "] level [" << difficulty << "] words.\n\n";

		previousDifficulty = difficulty;
	}

	int selection = rand() % size;

	return values->at(selection).second;
}

int setDifficulty()
{
	int input = 0;

	while (true)
	{
		std::cout << "\nEnter a new difficulty level (0, 1, 2): ";

		input = _getch();

		std::cout << (char)input << "\n\n";

		if (input == 48 || input == 49 || input == 50 || input == 27)
			return input;
		else
			std::cout << "Invalid selection.\n";
	}
}