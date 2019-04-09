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

const int BUF_SIZE = 256;

HANDLE  hSemaphoreSynchronize;
CHAR lpSemaphoreName[] = "SemaphoreName";

CHAR lpFileShareName[] = "VerySpecialFileShareName";

HANDLE hMapFile;
LPCTSTR lpFileMap;

HANDLE hEnableWritingEvent;
CHAR lpEnableWritingEventName[] = "EnableWritingEvent";

HANDLE hWritingTerminatedEvent;
CHAR lpWritingTerminatedEventName[] = "WritingTermination";

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


int main(int argc, char* argv[])
{
	DWORD waitResult;
	int semaphore_count = 0;
	
	hEnableWritingEvent = CreateEvent(NULL, FALSE, TRUE, (LPCSTR)lpEnableWritingEventName);

	if(hEnableWritingEvent == NULL) {
		printf("Can't create an enable event, %d", GetLastError());
		return 1;
	}
	hWritingTerminatedEvent = CreateEvent(NULL, FALSE, FALSE, (LPCSTR)lpWritingTerminatedEventName);

	if(hEnableWritingEvent == NULL) {
		printf("Can't create a termination, %d", GetLastError());
		return 1;
	}

	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,
								NULL,
								PAGE_READWRITE,
								0,
								BUF_SIZE,
								(LPCSTR)lpFileShareName);

	if(hMapFile == NULL){
		printf("Can't create a file mapping object (%d).\n"), GetLastError();
		return 1;
	}

	lpFileMap = (LPTSTR)MapViewOfFile(hMapFile,
								FILE_MAP_ALL_ACCESS,
								0,0, BUF_SIZE);

	if(lpFileMap == NULL){
		printf("Could not map view of file (%d).\n", GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}

	std::cout << "Enter count matrix:";
	int count_mx = correct_input_int();

	std::vector<std::string> ms_str(count_mx);
	for (int i = 0; i < count_mx; ++i) {
		ms_str[i] = input_mx();
	}
	printf("-------\n");
	std::vector<STARTUPINFO> stvec(count_mx);
	std::vector<PROCESS_INFORMATION> procvec(count_mx);

	for (int i = 0; i < count_mx; ++i) {
		ZeroMemory(&stvec[i], sizeof(stvec[i]));
		stvec[i].cb = sizeof(stvec[i]);
		ZeroMemory(&procvec[i], sizeof(procvec[i]));
	}

	if(count_mx>1) 
		semaphore_count = count_mx/2;
	else
		semaphore_count = 1;
	//semaphore_count = count_mx;

	hSemaphoreSynchronize = CreateSemaphoreA(NULL, count_mx, count_mx, lpSemaphoreName);

	if(hSemaphoreSynchronize == NULL){
		printf("Semaphore creation failure, %d", GetLastError());
	}

	
	for (int i = 0; i < count_mx; ++i) {

		ms_str[i] = "FirstProcess.exe " + ms_str[i];
		char *str = (char*)ms_str[i].c_str();

		if (!CreateProcess(NULL, (LPSTR)str, NULL, NULL, FALSE, 0, NULL, NULL, &stvec[i], &procvec[i]))
			printf("Creating process failure\n");

	}

	for(int i = 0; i< count_mx; ++i){
		WaitForSingleObject(hWritingTerminatedEvent, INFINITE);
		SetEvent(hEnableWritingEvent);
	}

	printf("%s", (char*)lpFileMap);
	HANDLE hProcesses[count_mx];
	   for(int i = 0; i < count_mx; ++i) {
	   	hProcesses[i] = procvec[i].hProcess;
	   }
	  WaitForMultipleObjects(count_mx, hProcesses, TRUE, INFINITE);

	   for (int i = 0; i < count_mx; ++i) {
	   	CloseHandle(procvec[i].hProcess);
	   	CloseHandle(procvec[i].hThread);
	   }

	return 0;
}