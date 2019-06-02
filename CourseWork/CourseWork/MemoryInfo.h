#pragma once
#include <Windows.h>
#include <iostream>
#include "ComputerPart.h"

using namespace std;

class MemoryInfo : public ComputerPart
{
public:
		void printMemoryInfo();
		void printToFile(ofstream & on);
		void setupMemoryInfo();
		int getRamUsage();
private:
		MEMORYSTATUS stat;
};