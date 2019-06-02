#include "MemoryInfo.h"
unsigned long MB = 1024 * 1024;

void MemoryInfo::setupMemoryInfo()
{
		GlobalMemoryStatus(&stat);
}

int MemoryInfo::getRamUsage()
{
		return stat.dwMemoryLoad;
}

void MemoryInfo::printMemoryInfo()
{
		system("cls");
		setupMemoryInfo();
		cout << "\tRAM's information" << endl << endl;
		cout << " Use of physical info: " << stat.dwMemoryLoad << "%" << endl;
		cout << " RAM initial capacity: " << stat.dwTotalPhys / MB << " MB" << endl;
		cout << " Free memory capacity: " << stat.dwAvailPhys / MB << " MB" << endl << endl;

		cout << " Full amount for after-load files: " << stat.dwTotalPageFile / MB << " MB" << endl;
		cout << " Free memory for after-load files: " << stat.dwAvailPageFile / MB << " MB" << endl << endl;
		system("pause");
}

void MemoryInfo::printToFile(ofstream &on)
{
		setupMemoryInfo();
		on << "\tRAM's information" << endl << endl;
		on << " Use of physical info: " << stat.dwMemoryLoad << "%" << endl;
		on << " RAM initial capacity: " << stat.dwTotalPhys / MB << " MB" << endl;
		on << " Free memory capacity: " << stat.dwAvailPhys / MB << " MB" << endl << endl;

		on << " Full amount for after-load files: " << stat.dwTotalPageFile / MB << " MB" << endl;
		on << " Free memory for after-load files: " << stat.dwAvailPageFile / MB << " MB" << endl << endl;
}