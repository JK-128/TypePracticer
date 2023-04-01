#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> loadWords(std::string path)
{
	std::vector<std::string> words;
	std::string word;

	std::ifstream file(path);

	while (std::getline(file, word))
	{
		if (word.size() > 0)
			words.push_back(word);
	}

	file.close();

	return words;
}

std::vector<std::pair<int, int>> loadValues(std::string path)
{
	std::vector<std::pair<int, int>> values;
	std::string value;

	std::ifstream file(path);

	int index = 0;
	while (std::getline(file, value))
	{
		int valueInt = std::stoi(value);

		values.push_back(std::make_pair(valueInt, index));

		index++;
	}

	file.close();

	return values;
}