#pragma once
#include "Definitions.h"
#include <algorithm>
#include <vector>
#include <conio.h>
#include <iostream>

void sortValues(std::vector<std::pair<int, int>>* values, int levels, bool print = false);

int selectWord(std::vector<std::pair<int, int>>* values, int difficulty);

int setDifficulty(int levels);

std::string trimFloat(std::string input);