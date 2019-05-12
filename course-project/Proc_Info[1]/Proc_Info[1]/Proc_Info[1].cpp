// Proc_Info[1].cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WIN32_WINNT 0x0600
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <Windows.h>
#include <powrprof.h>
#include <powerbase.h>
#include <vector>
#pragma comment(lib, "PowrProf.lib")

#define MEASUREMENT_INTERVAL 1000


FILETIME prevSysIdle, prevSysKernel, prevSysUser;

ULONGLONG SubtractTimes(const FILETIME one, const FILETIME two)
{
	LARGE_INTEGER a, b;
	a.LowPart = one.dwLowDateTime;
	a.HighPart = one.dwHighDateTime;

	b.LowPart = two.dwLowDateTime;
	b.HighPart = two.dwHighDateTime;

	return a.QuadPart - b.QuadPart;
}


int getUsage(double &val)
{
	FILETIME sysIdle, sysKernel, sysUser;
	// sysKernel include IdleTime
	if (GetSystemTimes(&sysIdle, &sysKernel, &sysUser) == 0) // GetSystemTimes func FAILED return value is zero;
		return 0;

	if (prevSysIdle.dwLowDateTime != 0 && prevSysIdle.dwHighDateTime != 0)
	{
		ULONGLONG sysIdleDiff, sysKernelDiff, sysUserDiff;
		sysIdleDiff = SubtractTimes(sysIdle, prevSysIdle);
		sysKernelDiff = SubtractTimes(sysKernel, prevSysKernel);
		sysUserDiff = SubtractTimes(sysUser, prevSysUser);

		ULONGLONG sysTotal = sysKernelDiff + sysUserDiff;
		ULONGLONG kernelTotal = sysKernelDiff - sysIdleDiff; // kernelTime - IdleTime = kernelTime, because sysKernel include IdleTime

		if (sysTotal > 0) // sometimes kernelTime > idleTime
			val = (double)(((kernelTotal + sysUserDiff) * 100.0) / sysTotal);
	}

	prevSysIdle = sysIdle;
	prevSysKernel = sysKernel;
	prevSysUser = sysUser;

	return 1;
}


using namespace std;


int main(int argc, char* argv[])	{

	
	do {
		double value;
		int isValid = getUsage(value);

		if (isValid) {
			for (int i = 0; i < value; ++i)
				cout << "=";
			cout << "|" << value << "%" << endl;
		}
		Sleep(MEASUREMENT_INTERVAL);
		system("cls");
	} while (true);


	system("pause");

	return 0;  
}

