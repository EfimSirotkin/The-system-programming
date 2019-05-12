#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "CPULoadRetriever.h"
#include <conio.h>
using namespace std;

typedef int(*DLL_LIB_FUNC)(double& value);
HINSTANCE cpuLoadLib;
TCHAR cpuLibName[] = TEXT("CPULoadLibrary.dll");

DLL_LIB_FUNC getCPULoad;

CPULoadRetriever::CPULoadRetriever() {

	cpuLoadLib = LoadLibrary(cpuLibName);
	if (cpuLibName == NULL) {
		std::cout << "Couldn't load the library !" << cpuLibName << std::endl;
		_getch();
		return;
	}
	else {
		std::cout << "*cpuDLL connected*" << std::endl;
	}
	getCPULoad = (DLL_LIB_FUNC)GetProcAddress(cpuLoadLib, "getCPULoad");
	cpuLoad = 0;
}
CPULoadRetriever::~CPULoadRetriever() {
	FreeLibrary(cpuLoadLib);
}

void CPULoadRetriever::RetrieveCPULoad() {

	double tempLoad;
	bool isValid = getCPULoad(tempLoad);
	if (isValid)
		cpuLoad = tempLoad;

}
double CPULoadRetriever::GetCPULoad() {
	return cpuLoad;
}