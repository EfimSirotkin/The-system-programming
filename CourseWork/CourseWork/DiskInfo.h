#pragma once
#include <iostream>
#include <Windows.h>
#include "ComputerPart.h"

class DiskInfo : ComputerPart
{
public:
		void printDiskInfo();
		void printToFile(ofstream &on);
};