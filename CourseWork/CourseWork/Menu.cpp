#include "Menu.h"

void Menu::showMenu()
{
		cout << "Please, choose from below: " << endl << endl;
		cout << "----------------------" << endl;
		cout << "|m: Monitor resources|" << endl;
		cout << "----------------------" << endl << endl;
		cout << "------------------------------------" << endl;
		cout << "|1: CPU  [central processing unit]  |" << endl;
		cout << "|2: GPU  [graphical processing unit]|" << endl;
		cout << "|3: RAM  [random access memory]     |" << endl;
		cout << "|4: HDD  [hard disk drive]          |" << endl;
		cout << "|5: SYS  [system]                   |" << endl;
		cout << "------------------------------------" << endl << endl;

		cout << "-----------------" << endl;
		cout << "|s: Save to file|" << endl;
		cout << "-----------------" << endl << endl;

		cout << "-----------" << endl;
		cout << "|Esc: Exit|" << endl;
		cout << "-----------" << endl;
}

void Menu::getChoice(CpuInfo &cpuInfo)
{
		switch (_getch())
		{
		case '1': 
			cpuInfo.printCpuInfo();
			break;

		case '2':
			VideoInfo gpuInfo;
			gpuInfo.printVideoInfo();
			break;

		case '3':
			MemoryInfo ramInfo;
			ramInfo.printMemoryInfo();
			break;

		case '4':
			DiskInfo diskInfo;
			diskInfo.printDiskInfo();
			break;
		case '5':
			SystemInfo systemInfo;
			systemInfo.printSystemInfo();
			break;
		case 27: 
			exit(EXIT_SUCCESS);
			break;
		case 'm': 
			UsageMonitoring usageMonitoring;
			usageMonitoring.printUsage();
			break;
		case 's': 
			File fileSaver;
			fileSaver.saveInFile(cpuInfo);
			break;
		}
}