#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <limits>
#include "matrix.h"

double correct_input_double()
{
	double input = -1;
	bool valid = false;
	do {
		std::cin >> input;
		if (std::cin.good()) {
			valid = true;
		}
		else {
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Invalid input, re-enter." << std::endl;
		}
	} while (!valid);

	return input;
}

int correct_input_int()
{
	int input = -1;
	bool valid = false;
	do {
		std::cin >> input;
		if (std::cin.good() && input > 0) {
			valid = true;
		}
		else {
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Invalid input, re-enter." << std::endl;
		}
	} while (!valid);

	return input;
}

std::string input_mx()
{
	std::stringstream stream;
	std::string string;

	std::cout << "Enter size of matrix:";
	int size_matrix = correct_input_int();
	size_matrix = std::pow(size_matrix, 2);
	for (int i = 0; i < size_matrix; ++i) {
		stream << correct_input_double() << " ";
	}
	string = stream.str();
	return string;
}

int main()
{
	std::cout << "Enter count matrix:";
	int count_mx = correct_input_int();
	std::vector<std::string> ms_str(count_mx);
	for (int i = 0; i < count_mx; ++i) {
		ms_str[i] = input_mx();
	}
	HANDLE* hHandles = (HANDLE*)malloc(count_mx * sizeof(HANDLE));
	if(hHandles[0] = CreateEventA(NULL,TRUE,FALSE, "firstEventHandle")){
		std::cout << "CustomEvent is created successfully!"<< std::endl;
	}
	else{
		std::cout << "Can't create the event" + GetLastError();
	}
	std::vector<STARTUPINFO> stvec(count_mx);
	std::vector<PROCESS_INFORMATION> procvec(count_mx);

	for (int i = 0; i < count_mx; ++i) {
		ZeroMemory(&stvec[i], sizeof(stvec[i]));
		stvec[i].cb = sizeof(stvec[i]);
		ZeroMemory(&procvec[i], sizeof(procvec[i]));
	}

	for (int i = 0; i < count_mx; ++i) {
		ms_str[i] = "firstProcess.exe " + ms_str[i];
		char *str = (char*)ms_str[i].c_str();
		if (!CreateProcess(NULL, (LPWSTR)str, NULL, NULL, FALSE, 0, NULL, NULL, &stvec[i], &procvec[i]))
			printf("Creating process failure\n");
	}

	HANDLE* hProcesses =(HANDLE*)malloc(count_mx*sizeof(HANDLE));
	for(int i = 0; i < count_mx; ++i) {
		hProcesses[i] = procvec[i].hProcess;
	}

	WaitForMultipleObjects(count_mx, hProcesses, TRUE, INFINITE);

	for (int i = 0; i < count_mx; ++i) {
		CloseHandle(procvec[i].hProcess);
		CloseHandle(procvec[i].hThread);
	}
	free(hProcesses);
	return 0;
}