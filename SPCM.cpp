// SPCM.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <vector>


#define THREAD_OBJECTS 4

using namespace std;

int main(int argc, char* argv[])
{
	system("chcp 1251");
	/*	Структура STARTUPINFO используется функцией CreateProcess
		для определения свойств главного окна,
		если новое окно создаётся для нового процесса.
		 Для консольных приложений эта информация относится к консольному окну
	*/

	/*
		Структура PROCESS_INFORMATION заполняется функцией CreateProcess
		информацией о новом созданном процессе и его главном потоке.
	*/


	STARTUPINFO ThreadStartupInfo[THREAD_OBJECTS];
	PROCESS_INFORMATION ThreadProcInfo[THREAD_OBJECTS];

	TCHAR CommandLine[] = TEXT("10 20 30 40 50 60 70 800 900 1000");

	for (auto& a : ThreadStartupInfo)
	{
		ZeroMemory(&a, sizeof(STARTUPINFO));
		a.cb = sizeof(STARTUPINFO);
	}
	for (auto& a : ThreadProcInfo)
		ZeroMemory(&a, sizeof(PROCESS_INFORMATION));
	
	for(int i=0; i< THREAD_OBJECTS; ++i)
	if (!CreateProcess(L"C:\\Users\\Светлячок\\source\\repos\\SPCM\\Debug\\FirstThread.exe",CommandLine, NULL, NULL, FALSE, 0, NULL, NULL,
					   &ThreadStartupInfo[i], &ThreadProcInfo[i]))
		printf("Creating the first process failure");

	for (const auto&a : ThreadProcInfo)
	{
		WaitForSingleObject(a.hProcess, INFINITE);
	}

	for (auto&a : ThreadProcInfo)
	{
		CloseHandle(a.hProcess);
		CloseHandle(a.hThread);
	}
	system("pause>nul");
	return 0;
}

