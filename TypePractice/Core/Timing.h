#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <time.h>

typedef struct
{
	int hour;
	int minute;
	int second;
	int mSecond;
	long long clock;

} timedata;

void printTime(timedata td);

std::string getTimePretty(timedata td);
std::string getTime(timedata td);

float getWPM(timedata duration, int wordCount);

timedata getCurrentTime();

timedata getTimeDifference(timedata td1);