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
#include <time.h>

const int MAX_MATRIX_SIZE = 8;

HANDLE hSemaphoreWrite;
CHAR lpSemaphoreName[] = "SemaphoreName";

HANDLE hEnableWritingEvent;
CHAR lpEnableWritingEventName[] = "EnableWritingEvent";

HANDLE hWritingTerminatedEvent;
CHAR lpWritingTerminatedEventName[] = "WritingTermination";

int get_matrix_size_from_string(const std::string mx_str)
{
	int counter = 0;
	if (!mx_str.empty())
		for (size_t i = 0; mx_str[i]; ++i)
		{
			if ((mx_str[i] == ' ' && mx_str[i + 1] != ' '))
				counter++;
		}
	return counter;
}

std::vector<std::vector<double>> get_matrix_from_string(int size, const std::string mx_str)
{
	std::vector<std::vector<double>> mx(sqrt(size), std::vector<double>(sqrt(size)));
	std::stringstream ss(mx_str);
	for (int i = 0; i < sqrt(size); ++i)
	{
		for (int j = 0; j < sqrt(size); ++j)
		{
			ss >> mx[i][j];
		}
	}
	return mx;
}

void threadProc(void *lpParam)
{
	DWORD waitResult;

	waitResult = WaitForSingleObject(hSemaphoreWrite, INFINITE);

	if (waitResult != WAIT_OBJECT_0)
		printf("Waiting...\n");

	std::string mx_str = *(std::string *)lpParam;
	int size = get_matrix_size_from_string(mx_str);
	std::string msg;
	Matrix mx = get_matrix_from_string(size, mx_str);
	try
	{
		mx.get_inverse_matrix();
	}
	catch (std::exception &e)
	{
		msg = e.what();
	}
	ReleaseSemaphore(hSemaphoreWrite, 1, NULL);

	WaitForSingleObject(hEnableWritingEvent, INFINITE);
	std::cout << "*Success*" << std::endl;
	mx.print_matrix(msg);

	SetEvent(hWritingTerminatedEvent);
	ExitThread(NO_ERROR);
}

double correct_input_double()
{
	double input = -1;
	bool valid = false;
	do
	{
		std::cin >> input;
		if (std::cin.good())
		{
			valid = true;
		}
		else
		{
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
	do
	{
		std::cin >> input;
		if (std::cin.good() && input > 0)
		{
			valid = true;
		}
		else
		{
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
	for (int i = 0; i < size_matrix; ++i)
	{
		stream << correct_input_double() << " ";
	}
	string = stream.str();
	return string;
}
std::string generate_random_mx(int range)
{
	std::stringstream stream;
	std::string string;
	int size_matrix = 0;

	size_matrix = rand() % MAX_MATRIX_SIZE + 1;
	size_matrix = std::pow(size_matrix, 2);

	for (int i = 0; i < size_matrix; ++i)
		stream << rand() % range << " ";

	string = stream.str();
	return string;
}

std::vector<std::vector<double>> wrap_str(int argc, char *argv[])
{
	std::vector<std::vector<double>> mx(sqrt(argc - 1), std::vector<double>(sqrt(argc - 1)));
	for (int i = 0; i < sqrt(argc - 1); ++i)
	{
		for (int j = 0; j < sqrt(argc - 1); ++j)
		{
			std::stringstream ss;
			ss.str(argv[(int)sqrt(argc - 1) * i + j + 1]);
			ss >> mx[i][j];
		}
	}
	return mx;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	DWORD waitResult;

	hEnableWritingEvent = CreateEvent(NULL, FALSE, FALSE, (LPCSTR)lpEnableWritingEventName);

	if (hEnableWritingEvent == NULL)
	{
		printf("Can't create an enable event, %d", GetLastError());
		return 1;
	}

	hWritingTerminatedEvent = CreateEvent(NULL, FALSE, FALSE, (LPCSTR)lpWritingTerminatedEventName);

	if (hWritingTerminatedEvent == NULL)
	{
		printf("Can't create a termination, %d", GetLastError());
		return 1;
	}

	std::cout << "Enter count matrix:";
	int count_mx = correct_input_int();

	HANDLE hThreads[count_mx];
	LPDWORD threadID[count_mx];

	std::vector<std::string> ms_str(count_mx);
	int range;
	std::cout << "Enter value range for elements: ";
	range = correct_input_int();
	for (int i = 0; i < count_mx; ++i)
	{
		ms_str[i] = generate_random_mx(range);
	}
	printf("-------\n");

	int semaphore_count = 0;

	if (count_mx > 1)
		semaphore_count = count_mx / 2;
	else
		semaphore_count = 1;

	hSemaphoreWrite = CreateSemaphoreA(NULL, semaphore_count, semaphore_count, lpSemaphoreName);

	if (hSemaphoreWrite == NULL)
	{
		printf("Semaphore creation failure, %d", GetLastError());
	}

	for (int i = 0; i < count_mx; ++i)
	{
		if ((hThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadProc, &ms_str[i], 0, NULL)) == NULL)
			std::cout << "Creating thread " << i << "failure " << std::endl;
	}

	for (int i = 0; i < count_mx; ++i)
	{
		SetEvent(hEnableWritingEvent);
		WaitForSingleObject(hWritingTerminatedEvent, INFINITE);
	}

	WaitForMultipleObjects(count_mx, hThreads, TRUE, INFINITE);

	for (int i = 0; i < count_mx; ++i)
		CloseHandle(hThreads[i]);

	return 0;
}