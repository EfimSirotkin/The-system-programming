#include "UsageMonitoring.h"

void UsageMonitoring::printUsage()
{
	system("cls");
	CpuInfo cpuInfo;
	MemoryInfo ramUsage;
	VideoInfo videoUsage;
	Time curTime;
	int CpuUsage;
	while (true)
	{
		videoUsage.RetrieveGpuUsage();
		curTime.getLocalTime();
		strftime(curTime.Hours, sizeof(curTime.Hours) / sizeof(curTime.Hours[0]), "%H", curTime.localTime);
		strftime(curTime.Minutes, sizeof(curTime.Minutes) / sizeof(curTime.Minutes[0]), "%M", curTime.localTime);
		strftime(curTime.Seconds, sizeof(curTime.Seconds) / sizeof(curTime.Seconds[0]), "%S", curTime.localTime);
		CpuUsage = cpuInfo.getCpuUsage();
		system("cls");
		cout << curTime.Hours << ":" << curTime.Minutes << ":" << curTime.Seconds << endl;
		cout << "[CPU usage]: " << CpuUsage << "%" << endl;
		ramUsage.setupMemoryInfo();
		cout << "[GPU usage]: " << (int)videoUsage.getGpuUsage() << "%" << endl;
		cout << "[RAM usage]: " << ramUsage.getRamUsage() << "%" << endl << endl;
		cout << "Esc to exit";
		if (_kbhit())
		{
			char c = _getche();
			if (c == 27) return;
		}
	}
	system("pause");
}