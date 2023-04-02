#pragma once
#include "Definitions.h"
#include <algorithm>
#include <vector>
#include <conio.h>

void sortValues(std::vector<std::pair<int, int>>* values, int levels, bool print = false)
{
	std::sort(values->begin(), values->end());

	std::vector<int> boundaries;

	boundaries.push_back(0);

	int previous = values->at(0).first;

	for(int i = 1; i < values->size(); i++)
	{
		if (values->at(i).first != previous)
		{
			boundaries.push_back(i);
			previous = values->at(i).first;
		}
		if (boundaries.size() == levels)
			break;
	}

	boundaries.push_back((int)values->size());

	if (print)
		for (int i = 1; i < boundaries.size(); i++)
			std::cout << "Level " << i << ": " << boundaries[i] - boundaries[i - 1] << "\n";
}

int selectWord(std::vector<std::pair<int, int>>* values, int difficulty)
{
	static int previousDifficulty = -2;

	int size = (int)values->size();

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
		std::cout << "\nSelecting from a pool of: [" << size << "] level [" << difficulty + 1 << "] words.\n\n";

		previousDifficulty = difficulty;
	}

	int selection = rand() % size;

	return values->at(selection).second;
}

int setDifficulty(int levels)
{
	int input = 0;

	while (true)
	{
		std::cout << "\nEnter a new difficulty level (1 - " << levels << "): ";

		input = _getch();

		for (int i = 1; i < levels + 1; i++)
			if (input == (i + keyOffset))
				return input - 1;

		std::cout << "Invalid selection.\n";
	}
}