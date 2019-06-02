#pragma once
#include "UsageMonitoring.h"
#include "SystemInfo.h"
#include "MemoryInfo.h"
#include "VideoInfo.h"
#include "DiskInfo.h"
#include "CpuInfo.h"
#include "File.h"
#include <iostream>
#include <conio.h>

using namespace std;

class Menu
{
public:
		void showMenu();
		void getChoice(CpuInfo &);
};