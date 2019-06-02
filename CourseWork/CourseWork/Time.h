#pragma once
#include <ctime>

class Time
{
public:
		void getLocalTime();
		char Hours[10] = { 0 };
		char Minutes[10] = { 0 };
		char Seconds[10] = { 0 };
		tm * localTime;
};