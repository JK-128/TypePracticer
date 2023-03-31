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

std::vector<int> loadValues(std::string path)
{
	std::vector<int> values;
	std::string value;

	std::ifstream file(path);

	while (std::getline(file, value))
	{
		if (value.size() > 0)
			values.push_back(std::stoi(value));
	}

	file.close();

	return values;
}