// CPULoadLibrary.cpp : Определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <Windows.h>

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


extern "C" __declspec(dllexport) int getCPULoad(double &val)
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



