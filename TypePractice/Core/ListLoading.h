#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct ValuesData
{
	int levelCount = 0;

	std::vector<std::pair<int, int>> values;
	std::vector<std::string> words;
};

std::vector<std::string> loadWords(std::string path);

std::vector<std::pair<int, int>> loadValues(std::string path);

int loadDifficulty(std::string path);

ValuesData loadData(std::string wordsPath, std::string valuesPath);