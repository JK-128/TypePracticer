#include "ListLoading.h"
#include <algorithm>
#include <conio.h>
#include <time.h>

void sortValues(std::vector<std::pair<int, int>>* values, bool print = true);
int  selectWord(std::vector<std::pair<int, int>>* values);

int main()
{
	srand(time(NULL));

	std::vector<std::string> words          = loadWords("Word Lists/lowercaseAll.txt");
	std::vector<std::pair<int, int>> values = loadValues("Word Lists/rowClassified.txt");

	sortValues(&values);

	while (1) 
	{
		int index = rand() % values.size();

		std::cout << values[index].second << " | " << values[index].second << " | " << words[values[index].second] << "\n";

		_getch();
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