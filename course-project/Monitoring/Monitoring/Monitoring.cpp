// Monitoring.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "CPULoadRetriever.h"

#define MEASUREMENT_INTERVAL 1000

using namespace std;

int main(int argc, char* argv[]) {
	CPULoadRetriever cpuLoadRetriever;
	do {
		cpuLoadRetriever.RetrieveCPULoad();
		double tempCPULoad = cpuLoadRetriever.GetCPULoad();
		for (int i = 0; i < tempCPULoad; ++i)
			cout << "=";
		cout << tempCPULoad << "%" << endl;
		Sleep(MEASUREMENT_INTERVAL);
		system("cls");
	} while (true);
	system("pause");
	return 0;
}


