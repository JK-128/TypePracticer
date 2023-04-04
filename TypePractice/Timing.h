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

void printTime(timedata td)
{
	std::cout << td.hour << ":" << td.minute << ":" << td.second << "." << td.mSecond << "\n";
}

void printTimePretty(timedata td)
{
	std::cout << "Completed in: ";
	//Print out the time data using words.
	if (td.hour != 0)
		std::cout << td.hour << "Hours, ";
	if (td.minute != 0)
		std::cout << td.minute << " minutes, and ";
	if (td.second != 0)
	{
		std::cout << td.second << "." << td.mSecond << " seconds.\n";
	}
	else
		std::cout << td.mSecond << " MS.\n";
}

float getWPM(timedata duration, int wordCount)
{
	//First step, convert duration (most likely seconds and milliseconds) to minutes.
	float minutes = 0;

	minutes += (float)duration.hour * 60.0f;
	minutes += (float)duration.minute;
	minutes += (float)duration.second / 60.0f;
	minutes += (float)duration.mSecond / 60000.0f;

	return (float)wordCount / minutes;
}

timedata getCurrentTime()
{
	timedata td;

	auto timeSinceEpoch   = std::chrono::system_clock::now().time_since_epoch();
	auto timeMillisecond  = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
	int  millisecondCount = (int)timeMillisecond.count();

	std::string timeStr = std::to_string(millisecondCount);
	std::string msStr   = timeStr.substr(timeStr.size() - 3, 3);

	struct tm timeinfo;
	std::time_t result = std::time(nullptr);

	localtime_s(&timeinfo, &result);

	td.hour    = timeinfo.tm_hour;
	td.minute  = timeinfo.tm_min;
	td.second  = timeinfo.tm_sec;
	td.mSecond = std::stoi(msStr);
	td.clock   = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	return td;
}

timedata getTimeDifference(timedata td1)
{
	timedata td2 = getCurrentTime();
	timedata tdR;

	long long diffNS = td2.clock - td1.clock;
	long long diffMS = diffNS / 1000000;
	long long diffS  = diffNS / 1000000000;
	long long diffM  = diffNS / 100000000000;
	long long diffH  = diffNS / 10000000000000;

	if (diffMS >= 1000)
	{
		std::string diffMSStr = std::to_string(diffMS);
		
		diffMSStr.erase(diffMSStr.begin());

		diffMS = std::stoll(diffMSStr);
	}

	tdR.hour    = diffH;
	tdR.minute  = diffM;
	tdR.second  = diffS;
	tdR.mSecond = diffMS;
	tdR.clock   = -1;

	return tdR;
}