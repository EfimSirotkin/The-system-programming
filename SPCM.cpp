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
	/*ZeroMemory(&FirstThreadStartupInfo, sizeof(FirstThreadStartupInfo));
	ZeroMemory(&SecondThreadStartupInfo, sizeof(SecondThreadStartupInfo));
	ZeroMemory(&ThirdThreadStartupInfo, sizeof(ThirdThreadStartupInfo));
	ZeroMemory(&FourthThreadStartupInfo, sizeof(FourthThreadStartupInfo));*/


	/*FirstThreadStartupInfo.cb = sizeof(FirstThreadStartupInfo);
	SecondThreadStartupInfo.cb = sizeof(SecondThreadStartupInfo);
	ThirdThreadStartupInfo.cb = sizeof(ThirdThreadStartupInfo);
	FourthThreadStartupInfo.cb = sizeof(FourthThreadStartupInfo);


	ZeroMemory(&FirstThreadProcInfo, sizeof(FirstThreadProcInfo));
	ZeroMemory(&SecondThreadProcInfo, sizeof(SecondThreadProcInfo));
	ZeroMemory(&ThirdThreadProcInfo, sizeof(ThirdThreadProcInfo));
	ZeroMemory(&FourthThreadProcInfo, sizeof(FourthThreadProcInfo));*/
	
	for(int i=0; i< THREAD_OBJECTS; ++i)
	if (!CreateProcess(L"C:\\Users\\Светлячок\\source\\repos\\SPCM\\Debug\\FirstThread.exe",CommandLine, NULL, NULL, FALSE, 0, NULL, NULL,
					   &ThreadStartupInfo[i], &ThreadProcInfo[i]))
		printf("Creating the first process failure");
	
	/*if (!CreateProcess(L"C:\\Users\\Светлячок\\source\\repos\\SPCM\\Debug\\SecondThread.exe", CommandLine, NULL, NULL, FALSE, 0, NULL, NULL,
					   &SecondThreadStartupInfo, &SecondThreadProcInfo))
		printf("Creating the second process failure\n");
	
	if (!CreateProcess(L"C:\\Users\\Светлячок\\source\\repos\\SPCM\\Debug\\ThirdThread.exe", CommandLine, NULL, NULL, FALSE, 0, NULL, NULL,
					   &ThirdThreadStartupInfo, &ThirdThreadProcInfo))
		printf("Creating the third process failure\n");

	if (!CreateProcess(L"C:\\Users\\Светлячок\\source\\repos\\SPCM\\Debug\\FourthThread.exe", CommandLine, NULL, NULL, FALSE, 0, NULL, NULL,
					   &FourthThreadStartupInfo, &FourthThreadProcInfo))
		printf("Creating the fourth process failure\n");*/

	for (const auto&a : ThreadProcInfo)
	{
		WaitForSingleObject(a.hProcess, INFINITE);
	}
	//cout <<endl<< "FIRSTFSIRSTS";

	for (auto&a : ThreadProcInfo)
	{
		CloseHandle(a.hProcess);
		CloseHandle(a.hThread);
	}
	/*CloseHandle(FirstThreadProcInfo.hProcess);
	CloseHandle(FirstThreadProcInfo.hThread);
	
	CloseHandle(SecondThreadProcInfo.hProcess);
	CloseHandle(SecondThreadProcInfo.hThread);
	
	CloseHandle(ThirdThreadProcInfo.hProcess);
	CloseHandle(ThirdThreadProcInfo.hThread);
	
	CloseHandle(FourthThreadProcInfo.hProcess);
	CloseHandle(FourthThreadProcInfo.hThread);*/
	system("pause>nul");
	return 0;
}

