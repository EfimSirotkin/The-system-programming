#pragma once
#include "CpuInfo.h"
#include "DiskInfo.h"
#include "MemoryInfo.h"
#include "SystemInfo.h"
#include "VideoInfo.h"
#include "Time.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class File
{
public:
		void saveInFile(CpuInfo &CI);
private:
		ofstream on;
};