#include "SystemInfo.h"

void SystemInfo::getSystemInfo()
{
		DWORD chBuff = BUFSIZE;
		char tempString[BUFSIZE];
		if (GetComputerNameA(tempString, &chBuff))
				strcpy(computerName, tempString);
		if (GetUserNameA(tempString, &chBuff))
				strcpy(userName, tempString);
		if (GetSystemDirectoryA(tempString, MAX_PATH + 1))
				strcpy(systemDirectory, tempString);
		if (GetWindowsDirectoryA(tempString, MAX_PATH + 1))
				strcpy(windowsDirectory, tempString);
		if (GetTempPathA(MAX_PATH + 1, tempString))
				strcpy(tempDirectory, tempString);
}

void SystemInfo::printSystemInfo()
{
		system("cls");
		getSystemInfo();
		cout << "\tSystem's information" << endl << endl;
		cout << "Name: " << computerName << endl;
		cout << "User: " << userName << endl;
		cout << "System folder: " << systemDirectory << endl;
		cout << "Windows folder: " << windowsDirectory << endl;
		cout << "Temp folder: " << tempDirectory << endl;
		system("pause");
}

void SystemInfo::printToFile(ofstream &on)
{
		getSystemInfo();
		on << "========================================" << endl;
		on << "\tSystem's information" << endl << endl;
		on << "Name: " << computerName << endl;
		on << "User: " << userName << endl;
		on << "System folder: " << systemDirectory << endl;
		on << "Windows folder: " << windowsDirectory << endl;
		on << "Temp folder: " << tempDirectory << endl;
}