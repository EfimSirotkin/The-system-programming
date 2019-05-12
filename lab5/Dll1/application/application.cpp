// application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <thread>

typedef void(*DLL_LIB_FUNC)();
HINSTANCE customLib;

void ReadFiles();
void WriteToFile();

TCHAR libName[] = TEXT("DLL1.dll");

int main(int args, char* argv[]) {

	
	customLib = LoadLibrary(libName);

	if (customLib == NULL) {
		std::cout << "Couldn't load the library !"<< libName << std::endl;
		_getch();
		return 0;
	}
	else {
		std::cout << "*Dll connected*" << std::endl;
	}

	std::cout << "Processing files..." << std::endl;
	Sleep(1000);

	std::thread ReadThread(ReadFiles);
	std::thread WriteThread(WriteToFile);

	ReadThread.join();
	WriteThread.join();

	std::cout << "Success! Check it out!" << std::endl;
	system("result.txt");

	FreeLibrary(customLib);
	_getch();
	return 0;
}

void ReadFiles() {
	DLL_LIB_FUNC libRead = (DLL_LIB_FUNC)GetProcAddress(customLib, "ReadFiles");
	libRead();
	ExitThread(0);
}

void WriteToFile() {
	DLL_LIB_FUNC libWrite = (DLL_LIB_FUNC)GetProcAddress(customLib, "WriteToFile");
	libWrite();
	ExitThread(0);
}