#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ComputerPart.h"
#define WAIT_TIME 1000

using namespace std;

class CpuInfo : public ComputerPart
{
public:
		int getCpuUsage();
		void printCpuInfo();
		void getCpuInfo();
		void printToFile(ofstream &on);
		ULONGLONG FT2ULL(FILETIME &ft);
private:
		string name;
		string manufacturer;
		string role;
		string status;
		int numberOfCores;
		int maxClockSpeed;
		int L2;
		int L3;
		SYSTEM_INFO SysInfo;
};