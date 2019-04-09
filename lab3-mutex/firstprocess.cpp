#include "matrix.h"
#include <sstream>
#include <thread>
#include <iostream>
#include <cmath>
#include <windows.h>

const int BUF_SIZE = 256;

HANDLE  hSemaphoreWrite;
CHAR lpSemaphoreName[] = "SemaphoreName";

CHAR lpFileShareName[] = "VerySpecialFileShareName";
HANDLE hFileMapping;
LPVOID lpFileMap;

HANDLE hEnableWritingEvent;
CHAR lpEnableWritingEventName[] = "EnableWritingEvent";

HANDLE hWritingTerminatedEvent;
CHAR lpWritingTerminatedEventName[] = "WritingTermination";

std::vector<std::vector<double>> wrap_str(int argc, char *argv[])
{
	std::vector<std::vector<double>> mx(sqrt(argc-1), std::vector<double>(sqrt(argc-1)));
	for (int i = 0; i < sqrt(argc-1); ++i) {
		for (int j = 0; j < sqrt(argc-1); ++j) {
			double sample = 0;
			std::stringstream ss;
			ss.str(argv[(int)sqrt(argc-1)*i + j+1]);
			ss >> mx[i][j];
		}
	}
	return mx;
}

int main(int argc, char *argv[])
{
	DWORD waitResult;

	hSemaphoreWrite = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, (LPCSTR)lpSemaphoreName);

	if(hSemaphoreWrite == NULL){
		printf("Can't open the semaphore , %d", GetLastError());
		ExitProcess(NO_ERROR);
	}

	hEnableWritingEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCSTR)lpEnableWritingEventName);

	if(hEnableWritingEvent == NULL){
		printf("Can't open an enable event, %d", GetLastError());
		CloseHandle(hSemaphoreWrite);
		return 1;
	}

	hWritingTerminatedEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCSTR)lpWritingTerminatedEventName);

	if(hWritingTerminatedEvent == NULL){
		printf("Can't open a termination event, %d", GetLastError());
		CloseHandle(hSemaphoreWrite);
		CloseHandle(hEnableWritingEvent);
		return 1;
	}

	waitResult = WaitForSingleObject(hSemaphoreWrite, INFINITE);

	if(waitResult != WAIT_OBJECT_0)
		printf("Waiting...\n");
	
	std::string msg;
	Matrix mx = wrap_str(argc, argv);
	try {
		mx.get_inverse_matrix();
	}
	catch (std::exception& e) {
		msg = e.what();
	}

	
	ReleaseSemaphore(hSemaphoreWrite, 1, NULL);
	
	WaitForSingleObject(hEnableWritingEvent, INFINITE);

	hFileMapping = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
									FALSE, (LPCSTR)lpFileShareName);

	
	lpFileMap = MapViewOfFile(hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE,
								0,0,0);

	strncat((char*)lpFileMap, mx.get_matrix_as_string(msg).c_str(), BUF_SIZE);
	strncat((char*)lpFileMap, "SUCCESS\n\n", BUF_SIZE);

	SetEvent(hWritingTerminatedEvent);
	
	CloseHandle(hEnableWritingEvent);
	CloseHandle(hWritingTerminatedEvent);
	CloseHandle(hSemaphoreWrite);
	
	UnmapViewOfFile(lpFileMap);
	CloseHandle(hFileMapping);
	return 0;
}